#include <gbpCommon.h>
#include <gbpSID.h>

void SID_Comm_split(SID_Comm *comm_in,int colour,int key,SID_Comm *comm_out){
#if USE_MPI
  MPI_Comm_split(comm_in->comm, colour,key,&(comm_out->comm));
  MPI_Comm_group(comm_out->comm,&(comm_out->group));
  MPI_Comm_size(comm_out->comm, &(comm_out->n_proc));
  MPI_Comm_rank(comm_out->comm, &(comm_out->My_rank));
#else
  comm_out->comm   =NULL;
  comm_out->group  =NULL;
  comm_out->n_proc =1;
  comm_out->My_rank=MASTER_RANK;
#endif
}

