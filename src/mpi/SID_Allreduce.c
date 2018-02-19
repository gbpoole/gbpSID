#include <string.h>
#include <gbpSID.h>

void SID_Allreduce(void *sendbuf, void *recvbuf, int count, SID_Datatype datatype, SID_Op op, SID_Comm *comm) {
#if USE_MPI
    MPI_Allreduce(sendbuf, recvbuf, count, datatype, (MPI_Op)op, (MPI_Comm)(comm->comm));
#else
    if(sendbuf != SID_IN_PLACE) {
        int size;
        SID_Type_size(datatype, &size);
        memcpy(recvbuf, sendbuf, size * count);
    }
#endif
}
