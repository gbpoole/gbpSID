#ifndef GBPSID_LOGGING_HH
#define GBPSID_LOGGING_HH

// C++ overloads of ANSI-C functions
#include <string>
void SID_log(const std::string &fmt, const int mode, ...);
void SID_log_error(const std::string &fmt, ...);
void SID_log_warning(const std::string &fmt, const int mode, ...);

#endif
