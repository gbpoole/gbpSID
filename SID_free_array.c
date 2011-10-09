#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_free_array(void **ptr,int n_D,...){
  int       i_D;
  int       n_D_pass;
  size_t    D_i;
  va_list   vargs;

  va_start(vargs,n_D);

  if((*ptr)!=NULL){

    // Loop over dimensions
    D_i=(size_t)va_arg(vargs,size_t);
    if(n_D==1)
      SID_free(SID_FARG ptr);
    else if(n_D>1){
      n_D_pass=n_D-1;
      for(i_D=0;i_D<D_i;i_D++)
        SID_free_array(ptr[i_D],n_D_pass,vargs);
      SID_free(SID_FARG ptr);
    }
    else
      SID_trap_error("Dimension size %d<0 in SID_free_array",ERROR_LOGIC,D_i);
  }
  va_end(vargs);
}

