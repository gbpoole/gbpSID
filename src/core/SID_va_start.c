#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gbpSID.h>

//! Initialize a variadic argument list
//! \param vargs
void SID_va_start(gbp_va_list *vargs) {
    vargs->stream_position = 0;
}
