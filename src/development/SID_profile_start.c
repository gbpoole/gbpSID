#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <gbpSID.h>

void SID_profile_start(const char *function_name, int mode, ...) {
    va_list vargs;
    va_start(vargs, mode);

#if USE_MPI
    if(SID_CHECK_BITFIELD_SWITCH(mode, SID_PROFILE_NOTMPIENABLED)) {
        SID_exit_error("MPI not supported in function %s!", SID_ERROR_LOGIC, function_name);
    }
#endif

    va_end(vargs);
}
