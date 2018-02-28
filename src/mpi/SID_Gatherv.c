#include <string.h>
#include <gbpSID.h>

void SID_Gatherv(void        *sendbuf,
                 int          sendcount,
                 SID_Datatype sendtype,
                 void        *recvbuf,
                 int         *recvcounts,
                 int         *displs,
                 SID_Datatype recvtype,
                 int          root,
                 SID_Comm    *comm){
#if USE_MPI
    MPI_Gatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, (MPI_Comm)(comm->comm));
#else
    if(sendtype!=recvtype)
        SID_log_error("Send and receive datatypes don't match in SID_Gatherv().",SID_ERROR_LOGIC);
    if(sendbuf != SID_IN_PLACE) {
        int size;
        SID_Type_size(sendtype, &size);
        memcpy(recvbuf, sendbuf, size * sendcount);
    }
#endif
}
