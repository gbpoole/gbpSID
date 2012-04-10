#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void *SID_realloc(void *original_pointer,size_t allocation_size){
  void *r_val;
  if(allocation_size>0){
    r_val=realloc(original_pointer,allocation_size);
    if(r_val==NULL)
      SID_trap_error("Could not re-allocate %lld bytes of RAM!",ERROR_MEMORY,allocation_size);
    SID.RAM_local   +=allocation_size;
    SID.max_RAM_local=MAX(SID.max_RAM_local,SID.RAM_local);
  }
  else
    r_val=NULL;
  return(r_val);
}

