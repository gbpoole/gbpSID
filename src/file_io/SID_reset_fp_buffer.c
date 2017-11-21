#include <gbpSID.h>

void SID_reset_fp_buffer(SID_fp_buffer **fp_buffer) {
    (*fp_buffer)->n_bytes_unread             = (*fp_buffer)->n_bytes_to_read;
    (*fp_buffer)->n_bytes_buffer_unprocessed = 0; // This way we will perform a read right away
    (*fp_buffer)->n_bytes_buffer_processed   = 0;
    (*fp_buffer)->n_bytes_buffer             = 0;
}
