#include <string.h>
#include <gbpSID.h>

void SID_Allgather(void *       sendbuf,
                   int          sendcount,
                   SID_Datatype sendtype,
                   void *       recvbuf,
                   SID_MARK_USED(int recvcount, USE_MPI),
                   SID_Datatype recvtype,
                   SID_MARK_USED(SID_Comm *comm, USE_MPI)) {
#if USE_MPI
    MPI_Allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, (MPI_Comm)(comm->comm));
#else
    if(sendtype != recvtype)
        SID_log_error("Send and receive datatypes don't match in SID_Allgather().", SID_ERROR_LOGIC);
    if(sendbuf != SID_IN_PLACE) {
        int size;
        SID_Type_size(sendtype, &size);
        memcpy(recvbuf, sendbuf, size * sendcount);
    }
#endif
}
