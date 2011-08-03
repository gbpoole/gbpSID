#include <gbpCommon.h>
#include <gbpSID.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

void SID_profile_start(char *function_name, int mode, ...){
  va_list vargs;
  va_start(vargs,mode);

#if USE_MPI
  if(check_mode_for_flag(mode,SID_PROFILE_NOTMPIENABLED)){
    SID_trap_error("MPI not supported in function %s!",ERROR_LOGIC,function_name);
  }
#endif

  va_end(vargs);
}

