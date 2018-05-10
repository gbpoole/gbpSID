#include <string.h>
#include <gbpSID.h>

void SID_Wait(SID_Request *array_request,
              SID_Status  *array_status){
#if USE_MPI
    MPI_Wait(array_request,array_status);
#endif
}
