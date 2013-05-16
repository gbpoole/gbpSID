#include <string.h>
#include <stdarg.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_throw_error(const char *fmt, int r_val, ...){
  char    temp_char[2];
  int     flag_CR=FALSE;
  int     i;
  va_list vargs;
  va_start(vargs,r_val);

  // Set the error state
  SID.error_state=TRUE;

  // Communicate the error state (not implemented yet).  This will
  //   be received by ranks who call SID_trap_error once implemented.

  // Write error message
  if(SID.n_proc>1)
    fprintf(SID.fp_log,"\n%s (RANK %d ABORTING) ",SID_ERROR_HEADER,SID.My_rank);
  else
    fprintf(SID.fp_log,"\n%s ",SID_ERROR_HEADER);
  vfprintf(SID.fp_log,fmt,vargs);
  fprintf(SID.fp_log,"\n");

  va_end(vargs);

  // Abort
  SID_exit(r_val);
}

