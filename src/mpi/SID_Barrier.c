#include <gbpSID.h>

void SID_Barrier(SID_MARK_USED(SID_Comm *comm, USE_MPI)) {
#if USE_MPI
    MPI_Barrier((MPI_Comm)(comm->comm));
#endif
}
