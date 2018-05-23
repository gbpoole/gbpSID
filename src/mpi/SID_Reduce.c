#include <string.h>
#include <gbpSID.h>

void SID_Reduce(void *       sendbuf,
                void *       recvbuf,
                int          count,
                SID_Datatype datatype,
                SID_MARK_USED(SID_Op op, USE_MPI),
                SID_MARK_USED(int root, USE_MPI),
                SID_MARK_USED(SID_Comm *comm, USE_MPI)) {
#if USE_MPI
    MPI_Reduce(sendbuf, recvbuf, count, datatype, (MPI_Op)op, root, (MPI_Comm)(comm->comm));
#else
    int size;
    SID_Type_size(datatype, &size);
    if(sendbuf != SID_IN_PLACE)
        memcpy(recvbuf, sendbuf, size * count);
#endif
}
