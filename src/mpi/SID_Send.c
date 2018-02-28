#include <string.h>
#include <gbpSID.h>

void SID_Send(void *sendbuf, int sendcount, SID_Datatype sendtype, int dest, int sendtag, SID_Comm *comm) {
#if USE_MPI
    MPI_Send(sendbuf, sendcount, (MPI_Datatype)sendtype, dest, sendtag, (MPI_Comm)(comm->comm));
#else
    SID_log_error("SID_Send() not currently supported for non-MPI execution.",SID_ERROR_LOGIC);
#endif
}
