#include <gbpCommon.h>
#include <gbpSID.h>

// Inititialize the read buffer
// IMPORTANT: n_bytes_buffer_max must be bigger than any single buffered read you will need!
void init_SID_fp_buffer(SID_fp *fp,size_t n_bytes_to_read,size_t n_bytes_buffer_max,SID_fp_buffer **fp_buffer){
   if((*fp_buffer)==NULL)
      (*fp_buffer)=(SID_fp_buffer *)SID_malloc(sizeof(SID_fp_buffer));
   else
      SID_free(SID_FARG (*fp_buffer)->buffer);
   (*fp_buffer)->fp                        =fp;
   (*fp_buffer)->buffer                    =(char *)SID_malloc(n_bytes_buffer_max);
   (*fp_buffer)->n_bytes_buffer_max        =n_bytes_buffer_max;
   (*fp_buffer)->n_bytes_unread            =n_bytes_to_read;
   (*fp_buffer)->n_bytes_buffer_unprocessed=0; // This way we will perform a read right away
   (*fp_buffer)->n_bytes_buffer_processed  =0;
   (*fp_buffer)->n_bytes_buffer            =0;
}

