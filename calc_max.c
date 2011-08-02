#include <gbpLib.h>
#include <gbpStats.h>

void calc_max(void   *data,
              void   *result,
    	      size_t  n_data,
              SID_Datatype  type,
              int           mode){
  int     i_data;
  if(n_data<1){
    if(type==SID_DOUBLE || check_mode_for_flag(mode,CALC_MODE_RETURN_DOUBLE))
      ((double *)result)[0]=0.;
    else if(type==SID_FLOAT)
      ((float  *)result)[0]=0.;
    else if(type==SID_INT)
      ((int    *)result)[0]=0;
    else if(type==SID_SIZE_T)
      ((size_t *)result)[0]=0;
    else
      SID_trap_error("Unknown variable type in calc_max",ERROR_LOGIC);
  }
  else if(check_mode_for_flag(mode,CALC_MODE_RETURN_DOUBLE)){
    if(type==SID_DOUBLE)
      ((double *)result)[0]=(double)((double *)data)[0];
    else if(type==SID_FLOAT)
      ((double *)result)[0]=(double)((float  *)data)[0];
    else if(type==SID_INT)
      ((double *)result)[0]=(double)((int    *)data)[0];
    else if(type==SID_SIZE_T)
      ((double *)result)[0]=(double)((size_t *)data)[0];
    else
      SID_trap_error("Unknown variable type in calc_max\n",ERROR_LOGIC);
    if(type==SID_DOUBLE){
      for(i_data=1;i_data<n_data;i_data++)
        if((double)(((double *)data)[i_data])>(double)(((double *)result)[0])) ((double *)result)[0]=(double)(((double *)data)[i_data]);
    }
    else if(type==SID_FLOAT){
      for(i_data=1;i_data<n_data;i_data++)
        if((double)(((float  *)data)[i_data])>(double)(((double *)result)[0])) ((double *)result)[0]=(double)(((float  *)data)[i_data]);
    }
    else if(type==SID_INT){
      for(i_data=1;i_data<n_data;i_data++)
        if((double)(((int    *)data)[i_data])>(double)(((double *)result)[0])) ((double *)result)[0]=(double)(((int    *)data)[i_data]);
    }
    else if(type==SID_SIZE_T){
      for(i_data=1;i_data<n_data;i_data++)
        if((double)(((size_t *)data)[i_data])>(double)(((double *)result)[0])) ((double *)result)[0]=(double)(((size_t *)data)[i_data]);
    }
  }
  else{
    if(type==SID_DOUBLE)
      ((double *)result)[0]=((double *)data)[0];
    else if(type==SID_FLOAT)
      ((float  *)result)[0]=((float  *)data)[0];
    else if(type==SID_INT)
      ((int    *)result)[0]=((int    *)data)[0];
    else if(type==SID_SIZE_T)
      ((size_t *)result)[0]=((size_t *)data)[0];
    else
      SID_trap_error("Unknown variable type in calc_max\n",ERROR_LOGIC);
    if(type==SID_DOUBLE){
      for(i_data=1;i_data<n_data;i_data++)
        if(((double *)data)[i_data]>((double *)result)[0]) ((double *)result)[0]=((double *)data)[i_data];
    }
    else if(type==SID_FLOAT){
      for(i_data=1;i_data<n_data;i_data++)
        if(((float  *)data)[i_data]>((float  *)result)[0]) ((float  *)result)[0]=((float *)data)[i_data];
    }
    else if(type==SID_INT){
      for(i_data=1;i_data<n_data;i_data++)
        if(((int    *)data)[i_data]>((int    *)result)[0]) ((int    *)result)[0]=((int   *)data)[i_data];
    }
    else if(type==SID_SIZE_T){
      for(i_data=1;i_data<n_data;i_data++)
        if(((size_t *)data)[i_data]>((size_t *)result)[0]) ((size_t *)result)[0]=((size_t *)data)[i_data];
    }
  }
}

