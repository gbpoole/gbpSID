#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void gbp_add_va_arg(gbp_va_list *vargs,size_t size,void *ptr){
   size_t next_position=vargs->stream_position+size;
   if(next_position>=MAX_GBP_VA_ARGS_STREAM_SIZE)
      SID_log("gbp_va_args stream has been over-run.",ERROR_LOGIC);
   memcpy(&(vargs->stream[vargs->stream_position]),ptr,size);
   vargs->stream_position=next_position;
}

