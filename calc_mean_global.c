#include <gbpCommon.h>
#include <gbpSID.h>

void calc_mean_global(void   *data_local,
                      void   *result,
	              size_t  n_data_local,
                      SID_Datatype type,
                      int          mode,
                      SID_Comm    *comm){
  double temp;
  size_t n_data;
  int    flag_abs;

  if(check_mode_for_flag(mode,CALC_MODE_ABS))
    flag_abs=CALC_MODE_ABS;
  else
    flag_abs=FALSE;

  calc_sum_global(&n_data_local,&n_data,1,           SID_SIZE_T,CALC_MODE_DEFAULT,               comm);
  if(n_data<1){
    if(type==SID_DOUBLE || check_mode_for_flag(mode,CALC_MODE_RETURN_DOUBLE))
      ((double *)result)[0]=0.;
    else if(type==SID_FLOAT)
      ((float  *)result)[0]=0.;
    else if(type==SID_INT)
      ((int    *)result)[0]=0;
    else if(type==SID_UNSIGNED)
      ((unsigned int *)result)[0]=0;
    else if(type==SID_SIZE_T)
      ((size_t *)result)[0]=0;
    else
      SID_trap_error("Unknown variable type in calc_min",ERROR_LOGIC);
  }
  else{
    calc_sum_global(data_local,   &temp,  n_data_local,type,      CALC_MODE_RETURN_DOUBLE|flag_abs,comm);
    temp/=(double)n_data;
    if(type==SID_DOUBLE)
      ((double *)result)[0]=(double)temp; 
    else if(type==SID_FLOAT)
      ((float  *)result)[0]=(float)temp; 
    else if(type==SID_INT)
      ((int    *)result)[0]=(int)temp; 
    else if(type==SID_UNSIGNED)
      ((unsigned int *)result)[0]=(unsigned int)temp; 
    else if(type==SID_SIZE_T)
      ((size_t *)result)[0]=(size_t)temp; 
  }
}

