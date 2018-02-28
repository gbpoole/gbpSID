#include <string.h>
#include <gbpSID.h>
#include <sys/time.h>

double SID_Wtime(void) {
#if USE_MPI
    return(MPI_Wtime());
#else
    return((double)time(NULL));
#endif
}
