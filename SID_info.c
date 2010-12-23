#include <gbpSID.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void SID_info(char *fmt, int mode, ...){
  int      flag_write_time;
  int      i_level;
  FILE    *fp_info;
  va_list  vargs;
  va_start(vargs,mode);

  fp_info=stderr;

#ifdef USE_MPI
  if(!SID.flag_results_on && check_mode(mode,SID_INFO_RESULT)){
    fprintf(fp_info,"\n");
    fprintf(fp_info,"-------------\n");
    fprintf(fp_info,"   Results   \n");
    fprintf(fp_info,"-------------\n");
    fprintf(fp_info,"\n");
    SID.flag_infos_started=TRUE;
  }
#else
  if(SID.flag_continue){
    fprintf(fp_info,"\n");
    SID.level++;
    SID.flag_continue=FALSE;
  }
  // Write indenting text
  if(SID.indent){
    for(i_level=0;i_level<SID.level;i_level++)
      fprintf(fp_info,"%s",SID_LOG_INDENT_STRING);
  }
#endif

  // Write text
  vfprintf(fp_info,fmt,vargs);
  fprintf(fp_info,"\n");

  fflush(fp_info);
  va_end(vargs);
}

