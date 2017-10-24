#include <string.h>
#include <stdarg.h>
#include <gbpSID.h>

void SID_trap_error(const char *fmt, int r_val, ...){
  char    temp_char[2];
  int     flag_CR=FALSE;
  int     i;
  va_list vargs;
  va_start(vargs,r_val);
  if(SID.n_proc>1)
    fprintf(SID.fp_log,"\n%s (RANK %d ABORTING) ",SID_ERROR_HEADER,SID.My_rank);
  else
    fprintf(SID.fp_log,"\n%s ",SID_ERROR_HEADER);
  vfprintf(SID.fp_log,fmt,vargs);
  fprintf(SID.fp_log,"\n");
  va_end(vargs);
  SID_exit(r_val);
}

