#include <string.h>
#include <gbpSID.h>

void SID_Waitall(SID_MARK_USED(int count, USE_MPI),
                 SID_MARK_USED(SID_Request array_request[], USE_MPI),
                 SID_MARK_USED(SID_Status array_status[], USE_MPI)) {
#if USE_MPI
    MPI_Waitall(count, array_request, array_status);
#endif
}
