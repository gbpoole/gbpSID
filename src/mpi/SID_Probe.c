#include <string.h>
#include <gbpSID.h>

void SID_Probe(int source,
               int tag,
               SID_Comm *comm,
               SID_Status *status){
#if USE_MPI
    MPI_Probe(source,tag,(MPI_Comm)(comm->comm),status);
#endif
}
