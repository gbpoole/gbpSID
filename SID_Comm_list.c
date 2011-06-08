#include <gbpCommon.h>
#include <gbpSID.h>

void SID_Comm_list(SID_Comm *comm_in,int comm_id,SID_Comm *comm_out){
#ifdef USE_MPI
  int       i_rank,j_rank;
  int       flag_include_me;
  int      *membership;
  int       group_size;
  SID_Comm  comm_temp;
  if(comm_id<0 || comm_id>=comm_in->n_proc)
    SID_trap_error("Invalid comm_id {%d} in SID_Comm_list",ERROR_LOGIC,comm_id);
  membership=(int *)SID_malloc(sizeof(int)*comm_in->n_proc);
  for(i_rank=0,group_size=0;i_rank<comm_in->n_proc;i_rank++){
    if(comm_id==i_rank) flag_include_me=TRUE;
    else                flag_include_me=FALSE;
    MPI_Allgather(&flag_include_me,1,MPI_INT,membership,comm_in->n_proc,MPI_INT,comm_in->comm);
    if(flag_include_me){
      for(j_rank=0;j_rank<comm_in->n_proc;j_rank++)
        if(membership[j_rank]) membership[group_size++]=j_rank;
    }
  }
  MPI_Group_incl(comm_in->group,group_size,membership,&(comm_out->group));
  SID_free(SID_FARG membership);
  MPI_Comm_create(comm_in->comm,comm_out->group,&(comm_out->comm));
  MPI_Comm_size(comm_in->comm,&(comm_out->n_proc));
  MPI_Comm_rank(comm_in->comm,&(comm_out->My_rank));
#else
  comm_out->comm   =NULL;
  comm_out->group  =NULL;
  comm_out->n_proc =1;
  comm_out->My_rank=MASTER_RANK;
#endif
}

