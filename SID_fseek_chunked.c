#include <gbpSID.h>

void SID_fseek_chunked(size_t  i_x_skip_local,
                       SID_fp *fp){
  fp->last_item=i_x_skip_local;
}

