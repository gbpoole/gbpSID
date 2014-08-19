#include <gbpCommon.h>
#include <gbpSID.h>
#include <unistd.h>
#include <stdarg.h>

void SID_mpi_gdb_here()
{
  int i = 0;
  char hostname[256];
  gethostname(hostname, sizeof(hostname));
  printf("Task %d, PID %d on %s ready for attach\n", SID.My_rank, getpid(), hostname);
  printf("Once connected go up stack to 'sleep(5)' and 'set var i=7'\n");
  fflush(stdout);
  while (0 == i)
    sleep(5);
}
