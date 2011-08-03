#include <gbpLib.h>
#include <gbpStats.h>

void calc_mean(void   *data,
               void   *result,
	       size_t  n_data,
               SID_Datatype type,
               int          mode){
  double temp;
  int    flag_abs;
  if(check_mode_for_flag(mode,CALC_MODE_ABS))
    flag_abs=CALC_MODE_ABS;
  else
    flag_abs=FALSE;
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
      SID_trap_error("Unknown variable type in calc_min",ERROR_LOGIC);
  }
  else{
    calc_sum(data,&temp,n_data,type,CALC_MODE_RETURN_DOUBLE|flag_abs);
    temp/=(double)n_data;
    if(type==SID_DOUBLE)
      ((double *)result)[0]=(double)temp; 
    else if(type==SID_FLOAT)
      ((float  *)result)[0]=(float)temp; 
    else if(type==SID_INT)
      ((int    *)result)[0]=(int)temp; 
    else if(type==SID_SIZE_T)
      ((size_t *)result)[0]=(size_t)temp; 
  }
}
