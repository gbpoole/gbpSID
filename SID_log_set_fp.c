#include <stdio.h>
#include <gbpSID.h>

void SID_log_set_fp(FILE *fp)
{
  // Set the SID.fp_log pointer
  SID.fp_log = fp;
}
