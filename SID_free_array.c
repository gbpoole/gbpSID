#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_free_array_local_recursive(void **ptr,int n_D,size_t *D);
void SID_free_array_local_recursive(void **ptr,int n_D,size_t *D){
  int       i_D;

  if(D[0]<0)
    SID_trap_error("Size of dimension %zd<0 in SID_free_array",ERROR_LOGIC,D[0]);
  if(n_D==1)
    SID_free(ptr);
  else if(n_D>1){
    for(i_D=0;i_D<D[0];i_D++)
      SID_free_array_local_recursive(SID_FARG (((char *)(*ptr))[i_D]),n_D-1,&(D[1]));
    SID_free(ptr);
  }
  else
    SID_trap_error("Number of dimensions %d<0 in SID_free_array",ERROR_LOGIC,n_D);
}

void SID_free_array(void **ptr,int n_D,...){
  int       i_D;
  size_t   *D;
  va_list   vargs;
  va_start(vargs,n_D);
  D=(size_t *)SID_malloc(sizeof(size_t)*n_D);
  for(i_D=0;i_D<n_D;i_D++)
    D[i_D]=(size_t)va_arg(vargs,size_t);
  SID_free_array_local_recursive(ptr,n_D,D);
  SID_free(SID_FARG D);
  va_end(vargs);
}

