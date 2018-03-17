#include <stdlib.h>
#include <string.h>
#include <gbpSID.h>

void exchange_ring_buffer(void *  send_buffer,
                          size_t  buffer_type_size,
                          size_t  send_count,
                          void *  receive_buffer,
                          size_t *receive_count_out,
                          int     i_rank) {
    int    send_buffer_size;
    int    receive_buffer_size;
    size_t receive_count;
    int    rank_to, rank_from;

#if USE_MPI
    // Exchange buffer sizes
    send_buffer_size = (int)(send_count * buffer_type_size);
    if(send_buffer == NULL || send_buffer_size <= 0)
        send_buffer_size = 0;
    set_exchange_ring_ranks(&rank_to, &rank_from, i_rank);
    if(i_rank != 0) {
        SID_Sendrecv(&send_count, 1, SID_SIZE_T, rank_to, 1036267, &receive_count, 1, SID_SIZE_T, rank_from, 1036267, SID_COMM_WORLD, SID_STATUS_IGNORE);
        receive_buffer_size = (int)(receive_count * buffer_type_size);
        SID_Sendrecv(send_buffer,
                     send_buffer_size,
                     SID_BYTE,
                     rank_to,
                     1256269,
                     receive_buffer,
                     receive_buffer_size,
                     SID_BYTE,
                     rank_from,
                     1256269,
                     SID_COMM_WORLD,
                     SID_STATUS_IGNORE);
    } else {
        receive_buffer_size = send_buffer_size;
        receive_count       = send_count;
        memcpy(receive_buffer, send_buffer, (size_t)receive_buffer_size);
    }
#else
    send_buffer_size = (int)(send_count * buffer_type_size);
    if(send_buffer != NULL && send_buffer_size > 0) {
        receive_buffer_size = send_buffer_size;
        receive_count       = send_count;
        memcpy(receive_buffer, send_buffer, (size_t)receive_buffer_size);
    } else
        receive_count = 0;
#endif
    // At times, we may not want to bother
    //   returning the number of received items
    //   (perhaps because it's fixed and known)
    //   This takes care of that if receive_count_in
    //   is set to NULL.
    if(receive_count_out != NULL)
        (*receive_count_out) = receive_count;
}
