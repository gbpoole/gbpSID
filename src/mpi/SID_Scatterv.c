#include <string.h>
#include <gbpSID.h>

void SID_Scatterv(void        *sendbuf,
                  int          sendcount,
                  int         *displs,
                  SID_Datatype sendtype,
                  void        *recvbuf,
                  int         *recvcounts,
                  SID_Datatype recvtype,
                  int          root,
                  SID_Comm    *comm){
#if USE_MPI
    MPI_Scatterv(sendbuf, sendcount, displs, sendtype, recvbuf, recvcounts, recvtype, root, (MPI_Comm)(comm->comm));
#else
    if(sendtype!=recvtype)
        SID_log_error("Send and receive datatypes don't match in SID_Scatterv().",SID_ERROR_LOGIC);
    if(sendbuf != SID_IN_PLACE) {
        int size;
        SID_Type_size(sendtype, &size);
        memcpy(recvbuf, sendbuf, size * sendcount);
    }
#endif
}
