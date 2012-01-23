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
  MPI_Status status;
  MPI_Sendrecv(sendbuf,sendcount,sendtype,dest,sendtag,recvbuf,recvcount,recvtype,source,recvtag,comm->comm,&status);
#else
  int    send_type_size;
  int    recv_type_size;
  size_t send_size;
  size_t recv_size;
  if(sendbuf!=recvbuf){
    SID_Type_size(sendtype,&send_type_size);
    SID_Type_size(recvtype,&recv_type_size);
    send_size=(size_t)sendcount*(size_t)send_type_size;
    recv_size=(size_t)recvcount*(size_t)recv_type_size;
    if(send_size==recv_size)
      memcpy(recvbuf,sendbuf,send_size);
    else
      SID_trap_error("Send/Receive buffer size mismatch (i.e. %lld!=%lld) in SID_Sendrecv",ERROR_LOGIC,send_size,recv_size);
  }
#endif
}

