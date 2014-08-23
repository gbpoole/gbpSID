#include <gbpCommon.h>
#include <gbpSID.h>

// Free the read buffer
void free_SID_fp_buffer(SID_fp_buffer **fp_buffer){
   if((*fp_buffer)->n_bytes_unread!=0)
      SID_trap_error("The file was not entirely processed.  %zd bytes left.",ERROR_LOGIC,(*fp_buffer)->n_bytes_unread);
   if((*fp_buffer)->n_bytes_buffer_unprocessed!=0)
      SID_trap_error("The file buffer was not entirely processed.  %zd of %zd bytes left.",ERROR_LOGIC,(*fp_buffer)->n_bytes_buffer_unprocessed,(*fp_buffer)->n_bytes_buffer);
   SID_free(SID_FARG (*fp_buffer)->buffer);
   SID_free(SID_FARG (*fp_buffer));
}

