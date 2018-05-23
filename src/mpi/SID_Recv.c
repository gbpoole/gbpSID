#include <string.h>
#include <gbpSID.h>

void SID_Recv(SID_MARK_USED(void *recvbuf, USE_MPI),
              SID_MARK_USED(int recvcount, USE_MPI),
              SID_MARK_USED(SID_Datatype recvtype, USE_MPI),
              SID_MARK_USED(int source, USE_MPI),
              SID_MARK_USED(int recvtag, USE_MPI),
              SID_MARK_USED(SID_Comm *comm, USE_MPI),
              SID_Status *status) {
#if USE_MPI
    MPI_Recv(recvbuf, recvcount, (MPI_Datatype)recvtype, source, recvtag, (MPI_Comm)(comm->comm), status);
#else
    SID_log_error("SID_Recv() not currently supported for non-MPI execution.", SID_ERROR_LOGIC);
    if(status != NULL)
        (*status) = SID_SUCCESS;
#endif
}
