#include <string.h>
#include <gbpSID.h>

void SID_Wait(SID_MARK_USED(SID_Request *array_request, USE_MPI), SID_MARK_USED(SID_Status *array_status, USE_MPI)) {
#if USE_MPI
    MPI_Wait(array_request, array_status);
#endif
}
