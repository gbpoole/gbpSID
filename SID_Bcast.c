#include <gbpCommon.h>
#include <gbpSID.h>

#define MAX_SEND_LOCAL 10*SIZE_OF_MEGABYTE

void SID_Bcast(void *buffer,int data_size,int source_rank,SID_Comm *comm){
#if USE_MPI
//    int size_left,size_offset,size_used,size_send;
//    size_left  =data_size;
//    size_offset=0;
//    while(size_left>0){
//      size_send=MIN(size_left,MAX_SEND_LOCAL);
//      MPI_Bcast(&(((char *)buffer)[size_offset]),(int)(size_send),MPI_BYTE,source_rank,(MPI_Comm)(comm->comm));
//      size_left  -=size_send;
//      size_offset+=size_send;
//    }
   MPI_Bcast(buffer,data_size,MPI_BYTE,source_rank,(MPI_Comm)(comm->comm));
#endif
}

