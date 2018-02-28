#include <string.h>
#include <gbpSID.h>

void SID_Ssend(void *buf,
               int count,
               SID_Datatype datatype,
               int dest,
               int tag,
               SID_Comm *comm){
#if USE_MPI
    MPI_Ssend(buf,count,datatype,dest,tag,(MPI_Comm)(comm->comm));
#else
    SID_log_error("SID_Ssend() not currently supported for non-MPI execution.",SID_ERROR_LOGIC);
#endif
}
