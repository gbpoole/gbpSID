#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gbpSID.h>

//! Clean-up a SID runtime configuration
void SID_Finalize() {
    int    n_days;
    int    n_hrs;
    int    n_mins;
    size_t max_RAM;
    size_t SID_max_RAM_local;
    int    i_rank;
    char   spacer[10];

    // Deal with I/O channels
    fflush(SID.fp_log);
    SID_Barrier(SID_COMM_WORLD);

    // Free some arrays
    SID_free(SID_FARG SID.time_start_level);
    SID_free(SID_FARG SID.time_stop_level);
    SID_free(SID_FARG SID.time_total_level);
    SID_free(SID_FARG SID.flag_use_timer);
    SID_free(SID_FARG SID.IO_size);
    SID_free(SID_FARG SID.My_node);

    // Finalize MPI
    SID_Comm_free(&(SID_COMM_WORLD));
#if USE_MPI_IO
    MPI_Info_free(&(SID.file_info));
#endif
#if USE_MPI
    MPI_Finalize();
#endif
}
