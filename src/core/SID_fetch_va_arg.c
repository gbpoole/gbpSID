#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gbpSID.h>

//! Return the content of a variadic argument
//! \param vargs
//! \param size
//! \param ptr
void SID_fetch_va_arg(gbp_va_list *vargs, size_t size, void *ptr) {
    size_t next_position = vargs->stream_position + size;
    if(next_position >= SID_MAX_VARGS_STREAM_SIZE)
        SID_log("gbp_va_args stream has been over-run.", SID_ERROR_LOGIC);
    memcpy(ptr, &(vargs->stream[vargs->stream_position]), size);
    vargs->stream_position = next_position;
}
