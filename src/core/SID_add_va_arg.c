#include <stdio.h>
#include <string.h>
#include <gbpSID.h>

//! Add a variadic argument
//! \param vargs
//! \param size
//! \param ptr
void SID_add_va_arg(gbp_va_list *vargs, size_t size, void *ptr) {
    size_t next_position = vargs->stream_position + size;
    if(next_position >= SID_MAX_VARGS_STREAM_SIZE)
        SID_log("gbp_va_args stream has been over-run.", SID_ERROR_LOGIC);
    memcpy(&(vargs->stream[vargs->stream_position]), ptr, size);
    vargs->stream_position = next_position;
}
