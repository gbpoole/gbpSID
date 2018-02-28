#include <string.h>
#include <gbpSID.h>

void SID_Isend(void *sendbuf, int sendcount, SID_Datatype sendtype, int dest, int sendtag, SID_Comm *comm, SID_Request *request) {
#if USE_MPI
    MPI_Isend(sendbuf, sendcount, (MPI_Datatype)sendtype, dest, sendtag, (MPI_Comm)(comm->comm),request);
#else
    SID_log_error("SID_Isend() not currently supported for non-MPI execution.",SID_ERROR_LOGIC);
#endif
}
