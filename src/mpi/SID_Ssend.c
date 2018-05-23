#include <string.h>
#include <gbpSID.h>

void SID_Ssend(SID_MARK_USED(void *buf,USE_MPI),
               SID_MARK_USED(int count,USE_MPI),
               SID_MARK_USED(SID_Datatype datatype,USE_MPI),
               SID_MARK_USED(int dest,USE_MPI),
               SID_MARK_USED(int tag,USE_MPI),
               SID_MARK_USED(SID_Comm *comm,USE_MPI)){
#if USE_MPI
    MPI_Ssend(buf,count,datatype,dest,tag,(MPI_Comm)(comm->comm));
#else
    SID_log_error("SID_Ssend() not currently supported for non-MPI execution.",SID_ERROR_LOGIC);
#endif
}
