#include <gbpSID.h>

void SID_Barrier(SID_Comm *comm){
#if USE_MPI
  MPI_Barrier((MPI_Comm)(comm->comm));
#endif
}

