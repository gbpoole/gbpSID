#include <string.h>
#include <stdarg.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_log_warning(char *fmt, int r_val, ...){
  char    temp_char[2];
  int     flag_CR=FALSE;
  int     i;
  va_list vargs;
  va_start(vargs,r_val);
  if(SID.I_am_Master){
    if(!SID.indent){
      fprintf(SID.fp_log,"\n");
      SID.indent=TRUE;
    }
    fprintf(SID.fp_log,"%s ",SID_WARNING_HEADER);
    vfprintf(SID.fp_log,fmt,vargs);
    fprintf(SID.fp_log,"\n");
  }
  va_end(vargs);
}

