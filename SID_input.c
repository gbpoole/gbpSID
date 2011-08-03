#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_input(char *fmt, SID_Datatype type, void *input, ...){
  int      char_length;
  va_list  vargs;
  va_start(vargs,input);

  // Master does the work
  if(SID.I_am_Master){
    if(!SID.flag_input_on){
      printf("\n");
      printf("----------------------\n");
      printf("   Input Parameters   \n");
      printf("----------------------\n");
      printf("\n");
    }

    // Write text
    vfprintf(stdout,fmt,vargs);

    // Fetch and display input
    if(type==SID_CHAR){
      fscanf(SID.fp_in,"%s",(char *)input);
      printf(" {%s}\n",(char *)input);
    }
    else if(type==SID_DOUBLE){
      fscanf(SID.fp_in,"%le",(double *)input);
      printf(" {%le}\n",((double *)input)[0]);
    }
    else if(type==SID_FLOAT){
      fscanf(SID.fp_in,"%e",(float *)input);
      printf(" {%e}\n",((float *)input)[0]);
    }
    else if(type==SID_INT){
      fscanf(SID.fp_in,"%d",(int *)input);
      printf(" {%d}\n",((int *)input)[0]);
    }
    else if(type==SID_SIZE_T){
      fscanf(SID.fp_in,"%zd",(size_t *)input);
      printf(" {%zd}\n",((size_t *)input)[0]);
    }
    else
      SID_trap_error("Datatype is not a supported user-input type.",ERROR_LOGIC);
    fflush(stdout);
  }

  // Make sure all ranks get the input
#if USE_SID
  SID_Barrier(SID.COMM_WORLD);
  if(type==SID_CHAR){
    char_length=strlen((char *)input)+1;
    SID_Bcast(&char_length,1,          SID_INTEGER,MASTER_RANK,SID.COMM_WORLD);
    SID_Bcast(input,       char_length,SID_CHAR,   MASTER_RANK,SID.COMM_WORLD);
  }
  else if(type==SID_DOUBLE)
    SID_Bcast(input,1,SID_DOUBLE,MASTER_RANK,SID.COMM_WORLD);
  else if(type==SID_FLOAT)
    SID_Bcast(input,1,SID_FLOAT,MASTER_RANK,SID.COMM_WORLD);
  else if(type==SID_INT)
    SID_Bcast(input,1,SID_INT,MASTER_RANK,SID.COMM_WORLD);
  else if(type==SID_SIZE_T)
    SID_Bcast(input,1,SID_SIZE_T,MASTER_RANK,SID.COMM_WORLD);
  else
    SID_trap_error("Datatype is not a supported user-input type.",ERROR_LOGIC);
#endif
  SID.flag_input_on=TRUE;
  va_end(vargs);
}

