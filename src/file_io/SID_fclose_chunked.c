#include <gbpSID.h>

//! Close a chuncked SID file pointer
//! \param fp
//! \return
int SID_fclose_chunked(SID_fp *fp) {
    int r_val = GBP_FALSE;
    SID_free(SID_FARG fp->i_x_step_chunk);
    SID_free(SID_FARG fp->i_x_start_chunk);
    SID_free(SID_FARG fp->i_x_last_chunk);
    SID_free(SID_FARG fp->header_offset);
    return (r_val);
}
