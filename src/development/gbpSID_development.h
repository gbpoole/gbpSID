#ifndef GBPSID_DEVELOPMENT_H
#define GBPSID_DEVELOPMENT_H

// Function declarations
#ifdef __cplusplus
extern "C" {
#endif

void SID_mpi_gdb_here();
void SID_profile_stop(int mode);
void SID_profile_start(const char *function_name, int mode, ...);
void SID_test(int val, char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
