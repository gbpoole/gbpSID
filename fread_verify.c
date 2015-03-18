#include <gbpCommon.h>
#include <gbpSID.h>

size_t fread_verify(void *ptr, size_t size, size_t count, FILE *stream){
   size_t n_return;
   if((n_return=fread(ptr,size,count,stream))!=count)
      SID_trap_error("Failed to read %lld %lld-byte sized items (only %lld returned).",ERROR_IO_READ,count,size,n_return);
   return(n_return);
}

