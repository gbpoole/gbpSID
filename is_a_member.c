#include <gbpCommon.h>
#include <gbpSID.h>

int is_a_member(void *candidate,void *list,int n_list,SID_Datatype type){
  int i_list;
  int result=FALSE;
  if(type==SID_DOUBLE){
     double  candidate_double;
     double *list_double;
     candidate_double=((double *)candidate)[0];
     list_double     = (double *)list;
     for(i_list=0;i_list<n_list && !result;i_list++){
        if(candidate_double==list_double[i_list]) result=TRUE;
     }
  }
  else if(type==SID_INT){
     int  candidate_int;
     int *list_int;
     candidate_int=((int *)candidate)[0];
     list_int     = (int *)list;
     for(i_list=0;i_list<n_list && !result;i_list++){
        if(candidate_int==list_int[i_list]) result=TRUE;
     }
  }
  else
    SID_trap_error("Unknown variable type in is_a_member.",ERROR_LOGIC);
  return(result);
}
