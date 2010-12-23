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
                  SID_Comm      comm){
#ifdef USE_MPI
fprintf(stderr,"zz %3d: %d %d %d %d %d %d\n",sendcount,dest,sendtag,recvcount,source,recvtag);
  MPI_Sendrecv(sendbuf,sendcount,(MPI_Datatype)sendtype,dest,sendtag,recvbuf,recvcount,(MPI_Datatype)recvtype,source,recvtag,(MPI_Comm)comm,MPI_STATUS_IGNORE);
#else
  size_t send_size;
  size_t recv_size;
  if(sendbuf!=recvbuf){
    send_size=(size_t)sendcount*SID_sizeof(sendtype);
    recv_size=(size_t)recvcount*SID_sizeof(recvtype);
    if(send_size==recv_size)
      memcpy(recvbuf,sendbuf,send_size);
    else
      SID_trap_error("Send/Receive buffer size mismatch (i.e. %lld!=%lld) in SID_Sendrecv",ERROR_LOGIC,send_size,recv_size);
  }
#endif
}

