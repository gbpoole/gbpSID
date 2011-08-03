#include <string.h>
#include <gbpSID.h>

void SID_Recv(void         *recvbuf,
              int           recvcount,
              SID_Datatype  recvtype,
              int           source,
              int           recvtag,
              SID_Comm     *comm){
#if USE_MPI
  MPI_Recv(recvbuf,recvcount,(MPI_Datatype)recvtype,source,recvtag,(MPI_Comm)(comm->comm),MPI_STATUS_IGNORE);
#endif
}

