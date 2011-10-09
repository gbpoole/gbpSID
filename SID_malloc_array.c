#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void *SID_malloc_array_local_recursive(size_t allocation_size_i,int n_D,size_t *D);
void *SID_malloc_array_local_recursive(size_t allocation_size_i,int n_D,size_t *D){
  int       i_D;
  int       n_D_pass;
  void     *ptr_return;

  if(D[0]<0)
    SID_trap_error("Size of dimension %zd<0 in SID_malloc_array",ERROR_LOGIC,D[0]);
  if(n_D==1){
    ptr_return=SID_malloc(allocation_size_i*D[0]);
  }
  else if(n_D>1){
    ptr_return=SID_malloc(sizeof(char *)*D[0]);
    n_D_pass=n_D-1;
    for(i_D=0;i_D<D[0];i_D++)
      ((void **)ptr_return)[i_D]=SID_malloc_array_local_recursive(allocation_size_i,n_D_pass,&(D[1]));
  }
  else
    SID_trap_error("Number of dimensions %d<0 in SID_malloc_array",ERROR_LOGIC,n_D);
  return(ptr_return);
}

void *SID_malloc_array(size_t allocation_size_i,int n_D,...){
  int       i_D;
  size_t   *D;
  void     *ptr_return;
  va_list   vargs;
  va_start(vargs,n_D);
  D=(size_t *)SID_malloc(sizeof(size_t)*n_D);
  for(i_D=0;i_D<n_D;i_D++)
    D[i_D]=(size_t)va_arg(vargs,size_t);
  va_end(vargs);
  ptr_return=SID_malloc_array_local_recursive(allocation_size_i,n_D,D);
  SID_free(SID_FARG D);
  return(ptr_return);
}

