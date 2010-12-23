#include <gbpSID.h>

void SID_Barrier(SID_Comm comm){
#ifdef USE_MPI
  MPI_Barrier(comm);
#endif
}

