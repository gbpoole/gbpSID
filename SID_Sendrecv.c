#include <string.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_Sendrecv(void         *sendbuf,
                  int           sendcount,
                  SID_Datatype  sendtype,
                  int           dest,
                  int           sendtag,
                  void         *recvbuf,
                  int           recvcount,
                  SID_Datatype  recvtype,
                  int           source,
                  int           recvtag,
                  SID_Comm     *comm){
#if USE_MPI
  MPI_Sendrecv(sendbuf,sendcount,sendtype,dest,sendtag,recvbuf,recvcount,recvtype,source,recvtag,(MPI_Comm)(comm->comm),MPI_STATUS_IGNORE);
#else
  size_t send_size;
  size_t recv_size;
  if(sendbuf!=recvbuf){
    SID_Type_size(sendtype,&send_size);
    SID_Type_size(recvtype,&recv_size);
    send_size*=(size_t)sendcount;
    recv_size*=(size_t)recvcount;
    if(send_size==recv_size)
      memcpy(recvbuf,sendbuf,send_size);
    else
      SID_trap_error("Send/Receive buffer size mismatch (i.e. %lld!=%lld) in SID_Sendrecv",ERROR_LOGIC,send_size,recv_size);
  }
#endif
}

