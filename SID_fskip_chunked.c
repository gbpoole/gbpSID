#include <gbpSID.h>

void SID_fskip_chunked(size_t  n_x_skip_local,
                       SID_fp *fp){
  fp->last_item+=n_x_skip_local;
}

