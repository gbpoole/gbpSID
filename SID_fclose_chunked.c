#include <gbpCommon.h>
#include <gbpSID.h>

int SID_fclose_chunked(SID_fp *fp){
  int r_val=FALSE;
  free(fp->i_x_step_chunk);
  free(fp->i_x_start_chunk);
  free(fp->i_x_last_chunk);
  free(fp->header_offset);
  return(r_val);
}

