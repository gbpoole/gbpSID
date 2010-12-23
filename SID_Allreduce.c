#include <string.h>
#include <gbpSID.h>

void SID_Allreduce(void *sendbuf,void *recvbuf,int count,SID_Datatype datatype,SID_Op op,SID_Comm comm){
#ifdef USE_MPI
  MPI_Allreduce(sendbuf,recvbuf,count,datatype,(MPI_Op)op,(MPI_Comm)comm);
#else
  int size;
  if(sendbuf!=SID_IN_PLACE){
    SID_type_size(datatype,&size);
    memcpy(recvbuf,sendbuf,(size_t)(count*size));
  }
#endif
}

