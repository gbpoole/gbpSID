#include <string.h>
#include <gbpSID.h>

void SID_Isend(SID_MARK_USED(void *sendbuf, USE_MPI),
               SID_MARK_USED(int sendcount, USE_MPI),
               SID_MARK_USED(SID_Datatype sendtype, USE_MPI),
               SID_MARK_USED(int dest, USE_MPI),
               SID_MARK_USED(int sendtag, USE_MPI),
               SID_MARK_USED(SID_Comm *comm, USE_MPI),
               SID_MARK_USED(SID_Request *request, USE_MPI)) {
#if USE_MPI
    MPI_Isend(sendbuf, sendcount, (MPI_Datatype)sendtype, dest, sendtag, (MPI_Comm)(comm->comm), request);
#else
    SID_log_error("SID_Isend() not currently supported for non-MPI execution.", SID_ERROR_LOGIC);
#endif
}
