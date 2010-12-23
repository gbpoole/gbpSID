#include <stdio.h>
#include <stdlib.h>
#include <gbpSID.h>
#include <string.h>

void SID_free(void **ptr){
  if((*ptr)!=NULL){
    SID.RAM_local-=sizeof((*ptr));
    free((*ptr));
    (*ptr)=NULL;
  }
}

