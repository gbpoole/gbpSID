#include <gbpSID.h>

#define MAX_SEND_LOCAL 10*SIZE_OF_MEGABYTE

void SID_Bcast(void *buffer, int count, SID_Datatype datatype, SID_Comm *comm, int source_rank) {
#if USE_MPI
  MPI_Bcast(buffer,data_size,MPI_BYTE,source_rank,(MPI_Comm)(comm->comm));
#endif
}

