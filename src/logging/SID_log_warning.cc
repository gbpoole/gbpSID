#include <stdarg.h>
#include <gbpSID.hh>

// This is an overload of SID_log_warning() for C++ strings
void SID_log_warning(const std::string &fmt, int mode, ...) {
    va_list vargs;
    va_start(vargs, mode);

    SID_log_warning(fmt.c_str(),mode,vargs);
}
