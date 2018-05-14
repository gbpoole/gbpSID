#include <stdarg.h>
#include <gbpSID.hh>

// This is a wrapper of SID_log_error() for C++ strings
void SID_log_error(const std::string &fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    SID_log_error(fmt.c_str(),vargs);
}
