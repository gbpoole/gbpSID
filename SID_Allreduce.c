#include <string.h>
#include <gbpSID.h>

void SID_Allreduce(void *sendbuf,void *recvbuf,int count,SID_Datatype datatype,SID_Op op,SID_Comm *comm){
#ifdef USE_MPI
  MPI_Allreduce(sendbuf,recvbuf,count,datatype,(MPI_Op)op,(MPI_Comm)(comm->comm));
#else
  int     size;
  void   *result;
  void   *data;

  SID_Type_size(datatype,&size);
  result=SID_malloc((size_t)size);

  if(sendbuf!=SID_IN_PLACE)
    data=sendbuf;
  else
    data=recvbuf;

  if(op==SID_SUM)
    calc_sum(data,result,(size_t)count,datatype,CALC_MODE_DEFAULT);
  else if(op==SID_MIN)
    calc_min(data,result,(size_t)count,datatype,CALC_MODE_DEFAULT);
  else if(op==SID_MAX)
    calc_max(data,result,(size_t)count,datatype,CALC_MODE_DEFAULT);
  else
    SID_trap_error("Operation not supported in SID_Allreduce.",ERROR_LOGIC);

  memcpy(recvbuf,result,(size_t)size);

  SID_free(SID_FARG result);
#endif
}

