#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void *SID_malloc_array(size_t allocation_size_i,int n_D,...){
  int       i_D;
  int       n_D_pass;
  size_t    D_i;
  size_t    count;
  size_t    allocation_size;
  char     *ptr_temp;
  char     *ptr_return;
  va_list   vargs;

  // Count the number of elements to allocate
  va_start(vargs,n_D);
  for(i_D=0,count=0;i_D<n_D;i_D++)
    count+=(size_t)va_arg(vargs,size_t);

  // Set the total allocation size
  if(n_D==1)
    allocation_size=allocation_size_i*count;
  else
    allocation_size=sizeof(char *)*count;

  if(allocation_size>0){

    // Rewind argument counter
    va_start(vargs,n_D);

    // Loop over dimensions
    D_i=(size_t)va_arg(vargs,size_t);
    if(n_D==1)
      ptr_return=SID_malloc(allocation_size_i*D_i);
    else if(n_D>1){
      ptr_return=SID_malloc(sizeof(char *)*D_i);
      n_D_pass=n_D-1;
      for(i_D=0;i_D<D_i;i_D++)
        ((void **)ptr_return)[i_D]=SID_malloc_array(allocation_size_i,n_D_pass,vargs);
    }
    else
      SID_trap_error("Dimension size %d<0 in SID_malloc_array",ERROR_LOGIC,D_i);
  }
  else
    ptr_return=NULL;
  va_end(vargs);
  return(ptr_return);
}

