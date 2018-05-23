#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gbpSID.h>

void SID_log_footer() {
    int    n_days;
    int    n_hrs;
    int    n_mins;
    size_t max_RAM;
    size_t SID_max_RAM_local;
    int    i_rank;
    char   spacer[10];

    // Report execution statistics
    if(SID.I_am_Master) {
        char time_string[48];
        fprintf(SID.fp_log, "\n");
        fprintf(SID.fp_log, "Run statistics:\n");
        fprintf(SID.fp_log, "--------------\n");
        (void)time(&(SID.time_stop));
        int n_secs = (int)(SID.time_stop - SID.time_start);
        SID_seconds2ascii(n_secs, time_string);
        fprintf(SID.fp_log, "Time elapsed=%s.\n", time_string);
        fprintf(SID.fp_log, "\n");
    }

    // Report memory usage
    /*
    if(SID.I_am_Master){
      fprintf(SID.fp_log,"\nMemory usage:\n");
      fprintf(SID.fp_log,"------------\n");
    }
    #if USE_MPI
      SID_Barrier(SID_COMM_WORLD);
      SID_Allreduce(&(SID.max_RAM_local),&max_RAM,1,SID_SIZE_T,SID_SUM,SID_COMM_WORLD);
      if(SID.n_proc>1){
        for(i_rank=0;i_rank<SID.n_proc;i_rank++){
          SID_max_RAM_local=SID.max_RAM_local;
          if(i_rank!=SID_MASTER_RANK)
            SID_Bcast(&SID_max_RAM_local,sizeof(size_t),i_rank,SID_COMM_WORLD);
          if(SID.I_am_Master){
            if(SID.n_proc>1000){
              if((float)SID.max_RAM_local/(float)SID_SIZE_OF_MEGABYTE>1.)
                fprintf(SID.fp_log,"Peak for rank %4d=%4.2lf Gb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_GIGIBYTE);
              else if((float)SID.max_RAM_local/(float)SID_SIZE_OF_KILOBYTE>1.)
                fprintf(SID.fp_log,"Peak for rank %4d=%4.2lf Mb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_MEGABYTE);
              else
                fprintf(SID.fp_log,"Peak for rank %4d=%4.2lf kb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_KILOBYTE);
              strcpy(spacer,"       ");
            }
            else if(SID.n_proc>100){
              if((float)SID.max_RAM_local/(float)SID_SIZE_OF_MEGABYTE>1.)
                fprintf(SID.fp_log,"Peak for rank %3d=%4.2lf Gb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_GIGIBYTE);
              else if((float)SID.max_RAM_local/(float)SID_SIZE_OF_KILOBYTE>1.)
                fprintf(SID.fp_log,"Peak for rank %3d=%4.2lf Mb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_MEGABYTE);
              else
                fprintf(SID.fp_log,"Peak for rank %3d=%4.2lf kb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_KILOBYTE);
              strcpy(spacer,"      ");
            }
            else if(SID.n_proc>10){
              if((float)SID.max_RAM_local/(float)SID_SIZE_OF_MEGABYTE>1.)
                fprintf(SID.fp_log,"Peak for rank %2d=%4.2lf Gb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_GIGIBYTE);
              else if((float)SID.max_RAM_local/(float)SID_SIZE_OF_KILOBYTE>1.)
                fprintf(SID.fp_log,"Peak for rank %2d=%4.2lf Mb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_MEGABYTE);
              else
                fprintf(SID.fp_log,"Peak for rank %2d=%4.2lf kb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_KILOBYTE);
              strcpy(spacer,"     ");
            }
            else{
              if((float)SID.max_RAM_local/(float)SID_SIZE_OF_MEGABYTE>1.)
                fprintf(SID.fp_log,"Peak for rank %d=%4.2lf Gb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_GIGIBYTE);
              else if((float)SID.max_RAM_local/(float)SID_SIZE_OF_KILOBYTE>1.)
                fprintf(SID.fp_log,"Peak for rank %d=%4.2lf Mb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_MEGABYTE);
              else
                fprintf(SID.fp_log,"Peak for rank %d=%4.2lf kb\n",i_rank,(float)SID_max_RAM_local/(float)SID_SIZE_OF_KILOBYTE);
              strcpy(spacer,"    ");
            }
          }
          SID_Barrier(SID_COMM_WORLD);
        }
      }
    #else
      strcpy(spacer,"\0");
      max_RAM=SID.max_RAM_local;
    #endif
    if(SID.I_am_Master){
      if((float)max_RAM/(float)SID_SIZE_OF_MEGABYTE>1.)
        fprintf(SID.fp_log,"Peak total %s=%4.2lf Gb\n",spacer,(float)max_RAM/(float)SID_SIZE_OF_GIGIBYTE);
      else if((float)max_RAM/(float)SID_SIZE_OF_KILOBYTE>1.)
        fprintf(SID.fp_log,"Peak total %s=%4.2lf Mb\n",spacer,(float)max_RAM/(float)SID_SIZE_OF_MEGABYTE);
      else
        fprintf(SID.fp_log,"Peak total %s=%4.2lf kb\n",spacer,(float)max_RAM/(float)SID_SIZE_OF_KILOBYTE);
    }
    */
}
