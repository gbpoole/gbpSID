#include <string.h>
#include <gbpSID.h>

void SID_Allgatherv(void        *sendbuf,
                    int          sendcount,
                    SID_Datatype sendtype,
                    void        *recvbuf,
                    int         *recvcounts,
                    int         *displs,
                    SID_Datatype recvtype,
                    SID_Comm    *comm){
#if USE_MPI
    MPI_Allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, (MPI_Comm)(comm->comm));
#else
    if(sendtype!=recvtype)
        SID_log_error("Send and receive datatypes don't match in SID_Allgatherv().",SID_ERROR_LOGIC);
    if(sendbuf != SID_IN_PLACE) {
        int size;
        SID_Type_size(sendtype, &size);
        memcpy(recvbuf, sendbuf, size * sendcount);
    }
#endif
}
