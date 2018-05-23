#include <gbpSID.h>

#define MAX_SEND_LOCAL 10 * SID_SIZE_OF_MEGABYTE

void SID_Bcast(SID_MARK_USED(void *buffer, USE_MPI),
               SID_MARK_USED(int count, USE_MPI),
               SID_MARK_USED(SID_Datatype datatype, USE_MPI),
               SID_MARK_USED(int source_rank, USE_MPI),
               SID_MARK_USED(SID_Comm *comm, USE_MPI)) {
#if USE_MPI
    MPI_Bcast(buffer, count, datatype, source_rank, (MPI_Comm)(comm->comm));
#endif
}
