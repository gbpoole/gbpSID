#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void *SID_calloc(size_t allocation_size){
  void *r_val;
  if(allocation_size>0){
    r_val=calloc(allocation_size,1);
    if(r_val==NULL)
      SID_trap_error("Could not allocate %lld bytes of RAM!",ERROR_MEMORY,allocation_size);
    SID.RAM_local   +=allocation_size;
    SID.max_RAM_local=MAX(SID.max_RAM_local,SID.RAM_local);
  }
  else
    r_val=NULL;
  return(r_val);
}

