#include <string.h>
#include <stdarg.h>
#include <gbpSID.h>

//! Output a debug test message
//! \param val
//! \param fmt
//! \param ...
void SID_test(int val, const char *fmt, ...) {
    char    temp_char[2];
    int     i;
    va_list vargs;
    va_start(vargs, fmt);
    fprintf(SID.fp_log, "\n");
#if USE_MPI
    fprintf(SID.fp_log, "SID_test N=%05d R=%05d ", val, SID.My_rank);
#else
    fprintf(SID.fp_log, "SID_test N=%05d ", val);
#endif
    if(fmt != NULL) {
        vfprintf(SID.fp_log, fmt, vargs);
        fprintf(SID.fp_log, "\n");
    }
    SID_Barrier(SID.COMM_WORLD);
    va_end(vargs);
}
