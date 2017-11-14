#include <gbpSID.h>

#define MAX_SEND_LOCAL 10 * SID_SIZE_OF_MEGABYTE

void SID_Bcast(void *buffer, int count, SID_Datatype datatype, int source_rank, SID_Comm *comm) {
#if USE_MPI
    MPI_Bcast(buffer, count, datatype, source_rank, (MPI_Comm)(comm->comm));
#endif
}
