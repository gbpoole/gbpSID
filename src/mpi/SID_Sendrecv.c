#include <string.h>
#include <gbpSID.h>

void SID_Sendrecv(void *sendbuf, int sendcount, SID_Datatype sendtype, int dest, int sendtag, void *recvbuf,
                  int recvcount, SID_Datatype recvtype, int source, int recvtag, SID_Comm *comm, SID_Status *status) {
#ifdef SID_SENDRECV_SIZELIMIT
#if USE_MPI
    // The following code was adapted from Gadget

    if(dest != source)
        SID_log_error("dest=source in SID_Sendrecv().",SID_ERROR_LOGIC);

    int size_sendtype;
    int size_recvtype;
    SID_Type_size(sendtype, &size_sendtype);
    SID_Type_size(recvtype, &size_recvtype);

    if(dest == SID.My_rank) {
        memcpy(recvbuf, sendbuf, recvcount * size_recvtype);
    }

    int count_limit = (int)((((long long)SID_SENDRECV_SIZELIMIT) * 1024 * 1024) / size_sendtype);
    int iter = 0;
    while(sendcount > 0 || recvcount > 0) {
        int send_now;
        if(sendcount > count_limit) {
            send_now = count_limit;
            if(iter == 0) {
                printf("imposing size limit on SID_Sendrecv() on task=%d (send of size=%d)\n", SID.My_rank, sendcount * size_sendtype);
                fflush(stdout);
            }
            iter++;
        } else
            send_now = sendcount;

        int recv_now;
        if(recvcount > count_limit)
            recv_now = count_limit;
        else
            recv_now = recvcount;

        MPI_Sendrecv(sendbuf, send_now, sendtype, dest, sendtag, recvbuf, recv_now, recvtype, source, recvtag, (MPI_Comm)(comm->comm), status);

        sendcount -= send_now;
        recvcount -= recv_now;

        sendbuf += send_now * size_sendtype;
        recvbuf += recv_now * size_recvtype;
    }
#else
    if(sendbuf != recvbuf) {
        int send_type_size;
        int recv_type_size;
        SID_Type_size(sendtype, &send_type_size);
        SID_Type_size(recvtype, &recv_type_size);
        size_t send_size = (size_t)sendcount * (size_t)send_type_size;
        size_t recv_size = (size_t)recvcount * (size_t)recv_type_size;
        if(send_size == recv_size)
            memcpy(recvbuf, sendbuf, send_size);
        else
            SID_exit_error("Send/Receive buffer size mismatch (i.e. %lld!=%lld) in SID_Sendrecv", SID_ERROR_LOGIC, send_size, recv_size);
    }
#endif
}
#else
#if USE_MPI
    MPI_Status status;
    MPI_Sendrecv(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm->comm, &status);
#else
    if(sendbuf != recvbuf) {
        int send_type_size;
        int recv_type_size;
        SID_Type_size(sendtype, &send_type_size);
        SID_Type_size(recvtype, &recv_type_size);
        size_t send_size = (size_t)sendcount * (size_t)send_type_size;
        size_t recv_size = (size_t)recvcount * (size_t)recv_type_size;
        if(send_size == recv_size)
            memcpy(recvbuf, sendbuf, send_size);
        else
            SID_exit_error("Send/Receive buffer size mismatch (i.e. %lld!=%lld) in SID_Sendrecv", SID_ERROR_LOGIC, send_size, recv_size);
    }
#endif
}
#endif