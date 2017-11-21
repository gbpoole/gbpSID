#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <gbpSID.h>

void SID_set_verbosity(int mode, ...) {
#if !SID_DEBUG
    int     i_level;
    va_list vargs;
    va_start(vargs, mode);
    if(SID_CHECK_BITFIELD_SWITCH(mode, SID_SET_VERBOSITY_ABSOLUTE))
        SID.verbosity = (int)va_arg(vargs, int);
    else if(SID_CHECK_BITFIELD_SWITCH(mode, SID_SET_VERBOSITY_RELATIVE))
        SID.verbosity = SID.level + (int)va_arg(vargs, int);
    else if(SID_CHECK_BITFIELD_SWITCH(mode, SID_SET_VERBOSITY_DEFAULT))
        SID.verbosity = SID_LOG_MAX_LEVELS;
    else
        SID_exit_error("Invalid mode passed to SID_log_verbosity!", SID_ERROR_LOGIC);
    va_end(vargs);
#endif
}
