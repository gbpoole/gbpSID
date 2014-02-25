#include <gbpCommon.h>
#include <gbpSID.h>

void SID_Comm_init(SID_Comm **comm){
  (*comm)       =(SID_Comm *)SID_malloc(sizeof(SID_Comm));
#if USE_MPI
  (*comm)->comm =SID_COMM_NULL;
  (*comm)->group=SID_GROUP_EMPTY;
#else
  (*comm)->comm =NULL;
  (*comm)->group=NULL;
#endif
  (*comm)->n_proc =1;
  (*comm)->My_rank=MASTER_RANK;
}

