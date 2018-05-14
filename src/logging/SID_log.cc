#include <gbpSID.hh>

// This is a wrapper of SID_log() for C++ strings
void SID_log(const std::string &fmt, int mode, ...) {
    va_list vargs;
    va_start(vargs, mode);

    SID_log(fmt.c_str(),mode,vargs);
}
