#include <string.h>
#include <gbpSID.h>

void SID_Probe(SID_MARK_USED(int source, USE_MPI),
               SID_MARK_USED(int tag, USE_MPI),
               SID_MARK_USED(SID_Comm *comm, USE_MPI),
               SID_MARK_USED(SID_Status *status, USE_MPI)) {
#if USE_MPI
    MPI_Probe(source, tag, (MPI_Comm)(comm->comm), status);
#endif
}
