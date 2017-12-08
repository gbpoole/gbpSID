#include <gbpSID.h>

#define MAX_SEND_LOCAL 100 * SID_SIZE_OF_MEGABYTE

//! Perform an identical read to all ranks with a SID file pointer
//! \param buffer
//! \param size_per_item
//! \param n_items
//! \param fp
//! \return
size_t SID_fread_all(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp) {
    size_t r_val;
#if USE_MPI
#if USE_MPI_IO
    int        r_val_i;
    MPI_Status status;
    MPI_File_read_all(fp->fp, buffer, size_per_item * n_items, MPI_BYTE, &status);
    MPI_Get_count(&status, MPI_BYTE, &r_val_i);
    r_val = (size_t)r_val_i / size_per_item;
#else
    size_t size_send, size_left, size_offset;
    if(size_per_item * n_items > 0) {
        if(SID.I_am_Master) {
            r_val = SID_fread_verify(buffer, size_per_item, n_items, fp->fp);
        } else {
            fseek(fp->fp, size_per_item * n_items, SEEK_CUR);
        }
        size_left   = size_per_item * n_items;
        size_offset = 0;
        while(size_left > 0) {
            size_send = GBP_MIN(size_left, MAX_SEND_LOCAL);
            SID_Bcast(&(((char *)buffer)[size_offset]), size_send, SID_BYTE, SID_MASTER_RANK, SID_COMM_WORLD);
            size_left -= size_send;
            size_offset += size_send;
        }
        SID_Bcast(&r_val, sizeof(size_t), SID_BYTE, SID_MASTER_RANK, SID_COMM_WORLD);
    } else
        r_val = 0;
#endif
#else
    r_val = SID_fread_verify(buffer, size_per_item, n_items, fp->fp);
#endif
    return (r_val);
}
