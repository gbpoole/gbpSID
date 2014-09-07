#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void gbp_va_start(gbp_va_list *vargs){
   vargs->stream_position=0;
}

