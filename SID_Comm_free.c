#include <gbpCommon.h>
#include <gbpSID.h>

void SID_Comm_free(SID_Comm **comm){
#if USE_MPI
  MPI_Comm_free(&((*comm)->comm));
  MPI_Group_free(&((*comm)->group));
#endif
  SID_free(SID_FARG (*comm));
}

