#include <string.h>
#include <gbpSID.h>

void SID_Send(void         *sendbuf,
              int           sendcount,
              SID_Datatype  sendtype,
              int           dest,
              int           sendtag,
              SID_Comm     *comm){
#if USE_MPI
  MPI_Send(sendbuf,sendcount,(MPI_Datatype)sendtype,dest,sendtag,(MPI_Comm)(comm->comm));
#endif
}

