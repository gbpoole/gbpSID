#include <string.h>
#include <gbpCommon.h>
#include <gbpSID.h>

int SID_fread_all_buffer(void *rval,size_t dtype_size,size_t n_items,SID_fp_buffer *fp_buffer){
    // Set the requested total return size
    size_t data_size=dtype_size*n_items;
    // Check if we need to peroform the next read
    if((fp_buffer->n_bytes_buffer_unprocessed)<data_size){
       // Deal with any unfinished parts of the last-read chunk
       if((fp_buffer->n_bytes_buffer_unprocessed)>0){
          // Use as much of the already-read chunk as possible
          size_t n_items_part_read=(fp_buffer->n_bytes_buffer_unprocessed)/dtype_size;
          if(n_items_part_read>0){
             size_t data_size_part_read=dtype_size*n_items_part_read;
             SID_fread_all_buffer(rval,dtype_size,n_items_part_read,fp_buffer);
             rval=&(((char *)rval)[data_size_part_read]);
             n_items-=n_items_part_read;
          }
          // Copy what's left to the start of the new buffer
          memcpy(fp_buffer->buffer,&(fp_buffer->buffer[fp_buffer->n_bytes_buffer_processed]),fp_buffer->n_bytes_buffer_unprocessed);
       }
       // Set how many bytes we are going to read
       size_t n_bytes_read=MIN((fp_buffer->n_bytes_unread),(fp_buffer->n_bytes_buffer_max)-fp_buffer->n_bytes_buffer_unprocessed);
       // Set the new buffer size
       fp_buffer->n_bytes_buffer=fp_buffer->n_bytes_buffer_unprocessed+n_bytes_read;
       // Perform read
       SID_fread_all(&(fp_buffer->buffer[fp_buffer->n_bytes_buffer_unprocessed]),n_bytes_read,1,fp_buffer->fp);
       // Adjust counters
       (fp_buffer->n_bytes_unread)            -= n_bytes_read;
       (fp_buffer->n_bytes_buffer_unprocessed) = fp_buffer->n_bytes_buffer;
       (fp_buffer->n_bytes_buffer_processed)   = 0;
    }
    // Copy buffered value to the return pointer's location
    memcpy(rval,&(fp_buffer->buffer[fp_buffer->n_bytes_buffer_processed]),data_size);
    // Adjust counters
    (fp_buffer->n_bytes_buffer_unprocessed)-=data_size;
    (fp_buffer->n_bytes_buffer_processed)  +=data_size;
}

