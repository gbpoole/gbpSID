#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_exit(int status){
  int    i_args=0;
  int    n_days;
  int    n_hrs;
  int    n_mins; 
  int    n_secs;
  size_t max_RAM;
  size_t SID_max_RAM_local;
  int    i_rank;
  char   spacer[10];
  char   time_string[48];

  // Deal with I/O channels
  fflush(SID.fp_log);
  #ifdef USE_MPI
    MPI_Barrier(MPI_COMM_WORLD);
  #endif
  if(SID.fp_in!=stdin && SID.fp_in!=NULL)
    fclose(SID.fp_in);

  // Clean-up argument stuff
  if(SID.args!=NULL){ 
    while((SID_arg *)(SID.args[i_args])!=NULL){
      if(SID.arg_alloc[i_args])
        free(((SID_arg *)(SID.args[i_args]))->val);
      i_args++;
    }
    if(i_args>0){
      free(SID.arg_alloc);
      free(SID.arg_set);
    }
  }

  // Clean-up any memory still allocated

  // Report execution statistics
  if(status!=ERROR_SYNTAX){
  if(SID.I_am_Master){
    fprintf(SID.fp_log,"\n");
    fprintf(SID.fp_log,"Run statistics:\n");
    fprintf(SID.fp_log,"--------------\n");
    (void)time(&(SID.time_stop));
    n_secs =(int)(SID.time_stop-SID.time_start);
    seconds2ascii(n_secs,time_string);
    fprintf(SID.fp_log,"Time elapsed=%s.\n",time_string);
  }

  // Report memory usage
  if(SID.I_am_Master){
    fprintf(SID.fp_log,"\nMemory usage:\n");
    fprintf(SID.fp_log,"------------\n");
  }
  #ifdef USE_MPI
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Allreduce(&(SID.max_RAM_local),&max_RAM,1,MPI_SIZE_T,MPI_SUM,MPI_COMM_WORLD);
    if(SID.n_proc>1){
      for(i_rank=0;i_rank<SID.n_proc;i_rank++){
        SID_max_RAM_local=SID.max_RAM_local;
        if(i_rank!=MASTER_RANK)
          MPI_Bcast(&SID_max_RAM_local,1,MPI_SIZE_T,i_rank,MPI_COMM_WORLD);
        if(SID.I_am_Master){
          if(SID.n_proc>1000){
            if((float)SID.max_RAM_local/(float)SIZE_OF_MEGABYTE>1.)
              fprintf(SID.fp_log,"Peak for rank %4d=%4.2lf Gb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_GIGIBYTE);
            else if((float)SID.max_RAM_local/(float)SIZE_OF_KILOBYTE>1.)
              fprintf(SID.fp_log,"Peak for rank %4d=%4.2lf Mb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_MEGABYTE);
            else
              fprintf(SID.fp_log,"Peak for rank %4d=%4.2lf kb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_KILOBYTE);
            strcpy(spacer,"       ");
          }
          else if(SID.n_proc>100){
            if((float)SID.max_RAM_local/(float)SIZE_OF_MEGABYTE>1.)
              fprintf(SID.fp_log,"Peak for rank %3d=%4.2lf Gb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_GIGIBYTE);
            else if((float)SID.max_RAM_local/(float)SIZE_OF_KILOBYTE>1.)
              fprintf(SID.fp_log,"Peak for rank %3d=%4.2lf Mb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_MEGABYTE);
            else
              fprintf(SID.fp_log,"Peak for rank %3d=%4.2lf kb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_KILOBYTE);
            strcpy(spacer,"      ");
          }
          else if(SID.n_proc>10){
            if((float)SID.max_RAM_local/(float)SIZE_OF_MEGABYTE>1.)
              fprintf(SID.fp_log,"Peak for rank %2d=%4.2lf Gb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_GIGIBYTE);
            else if((float)SID.max_RAM_local/(float)SIZE_OF_KILOBYTE>1.)
              fprintf(SID.fp_log,"Peak for rank %2d=%4.2lf Mb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_MEGABYTE);
            else
              fprintf(SID.fp_log,"Peak for rank %2d=%4.2lf kb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_KILOBYTE);
            strcpy(spacer,"     ");
          }
          else{
            if((float)SID.max_RAM_local/(float)SIZE_OF_MEGABYTE>1.)
              fprintf(SID.fp_log,"Peak for rank %d=%4.2lf Gb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_GIGIBYTE);
            else if((float)SID.max_RAM_local/(float)SIZE_OF_KILOBYTE>1.)
              fprintf(SID.fp_log,"Peak for rank %d=%4.2lf Mb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_MEGABYTE);
            else
              fprintf(SID.fp_log,"Peak for rank %d=%4.2lf kb\n",i_rank,(float)SID_max_RAM_local/(float)SIZE_OF_KILOBYTE);
            strcpy(spacer,"    ");
          }
        }
        MPI_Barrier(MPI_COMM_WORLD);
      }
    }
  #else
    strcpy(spacer,"");
    max_RAM=SID.max_RAM_local;
  #endif
  if(SID.I_am_Master){
    if((float)max_RAM/(float)SIZE_OF_MEGABYTE>1.)
      fprintf(SID.fp_log,"Peak total %s=%4.2lf Gb\n",spacer,(float)max_RAM/(float)SIZE_OF_GIGIBYTE);
    else if((float)max_RAM/(float)SIZE_OF_KILOBYTE>1.)
      fprintf(SID.fp_log,"Peak total %s=%4.2lf Mb\n",spacer,(float)max_RAM/(float)SIZE_OF_MEGABYTE);
    else
      fprintf(SID.fp_log,"Peak total %s=%4.2lf kb\n",spacer,(float)max_RAM/(float)SIZE_OF_KILOBYTE);
  }
  }

  // Free some arrays
  SID_free(SID_FARG SID.time_start_level);
  SID_free(SID_FARG SID.time_stop_level);
  SID_free(SID_FARG SID.time_total_level);
  SID_free(SID_FARG SID.flag_use_timer);
  SID_free(SID_FARG SID.IO_size);
  SID_free(SID_FARG SID.My_node);

  // Finalize MPI
  SID_Comm_free(&(SID.COMM_WORLD));
  #ifdef USE_MPI_IO
    MPI_Info_free(&(SID.file_info));
    MPI_Finalize(); 
  #endif
  exit(status);
}

