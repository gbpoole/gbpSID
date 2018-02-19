#include <string.h>
#include <gbpSID.h>

void SID_Irecv(void *recvbuf, int recvcount, SID_Datatype recvtype, int source, int recvtag, SID_Comm *comm, SID_Request *request) {
#if USE_MPI
    MPI_Irecv(recvbuf, recvcount, (MPI_Datatype)recvtype, source, recvtag, (MPI_Comm)(comm->comm), request);
#else
    SID_log_error("SID_Irecv() not currently supported for non-MPI execution.",SID_ERROR_LOGIC);
#endif
}
