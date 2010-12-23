#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_set_verbosity(int mode, ...){
  int     i_level;
  va_list vargs;
  va_start(vargs,mode);

  if(check_mode_for_flag(mode,SID_SET_VERBOSITY_ABSOLUTE))
    SID.verbosity =(int)va_arg(vargs,int);
  else if(check_mode_for_flag(mode,SID_SET_VERBOSITY_RELATIVE))
    SID.verbosity =SID.level+(int)va_arg(vargs,int);
  else if(check_mode_for_flag(mode,SID_SET_VERBOSITY_DEFAULT))
    SID.verbosity =SID_LOG_MAX_LEVELS;
  else
    SID_trap_error("Invalid mode passed to SID_log_verbosity!",ERROR_LOGIC);

  va_end(vargs);
}

