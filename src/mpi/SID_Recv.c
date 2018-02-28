#include <string.h>
#include <gbpSID.h>

void SID_Recv(void *recvbuf, int recvcount, SID_Datatype recvtype, int source, int recvtag, SID_Comm *comm, SID_Status *status) {
#if USE_MPI
    MPI_Recv(recvbuf, recvcount, (MPI_Datatype)recvtype, source, recvtag, (MPI_Comm)(comm->comm), status);
#else
    SID_log_error("SID_Recv() not currently supported for non-MPI execution.",SID_ERROR_LOGIC);
    if(status!=NULL)
        (*status) = SID_SUCCESS;
#endif
}
