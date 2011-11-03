#include <gbpCommon.h>
#include <gbpSID.h>
#include <math.h>

void calc_stddev(void   *data,
                 void   *result,
 		 size_t  n_data,
                 SID_Datatype type,
                 int          mode){
  int     i_data;
  double  stddev;
  double  mean;
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
    if(check_mode_for_flag(mode,CALC_MODE_ABS)){
      calc_mean(data,&mean,n_data,type,CALC_MODE_RETURN_DOUBLE|CALC_MODE_ABS);
      for(i_data=0,stddev=0.;i_data<n_data;i_data++){
        if(type==SID_DOUBLE)
          stddev+=pow(IABS((double)((double *)data)[i_data])-mean,2.);
        else if(type==SID_FLOAT)
          stddev+=pow(IABS((double)((float  *)data)[i_data])-mean,2.);
        else if(type==SID_INT)
          stddev+=pow(IABS((double)((int    *)data)[i_data])-mean,2.);
        else if(type==SID_SIZE_T)
          stddev+=pow(IABS((double)((size_t *)data)[i_data])-mean,2.);
        else
          SID_trap_error("Unknown variable type in calc_stddev",ERROR_LOGIC);
      }
      stddev=sqrt(stddev/(double)n_data);
      if(type==SID_DOUBLE || check_mode_for_flag(mode,CALC_MODE_RETURN_DOUBLE))
        ((double *)result)[0]=(double)stddev;
      else if(type==SID_FLOAT)
        ((float  *)result)[0]=(float)stddev;
      else if(type==SID_INT)
        ((int    *)result)[0]=(int)stddev;
      else if(type==SID_SIZE_T)
        ((size_t *)result)[0]=(size_t)stddev;
      else
        SID_trap_error("Unknown variable type in calc_min",ERROR_LOGIC);
    }
    else{
      calc_mean(data,&mean,n_data,type,CALC_MODE_RETURN_DOUBLE);
      for(i_data=0,stddev=0.;i_data<n_data;i_data++){
        if(type==SID_DOUBLE)
          stddev+=pow((double)((double *)data)[i_data]-mean,2.);
        else if(type==SID_FLOAT)
          stddev+=pow((double)((float  *)data)[i_data]-mean,2.);
        else if(type==SID_INT)
          stddev+=pow((double)((int    *)data)[i_data]-mean,2.);
        else if(type==SID_SIZE_T)
          stddev+=pow((double)((size_t *)data)[i_data]-mean,2.);
        else
          SID_trap_error("Unknown variable type in calc_stddev",ERROR_LOGIC);
      }
      stddev=sqrt(stddev/(double)n_data);
      if(type==SID_DOUBLE || check_mode_for_flag(mode,CALC_MODE_RETURN_DOUBLE))
        ((double *)result)[0]=(double)stddev;
      else if(type==SID_FLOAT)
        ((float  *)result)[0]=(float)stddev;
      else if(type==SID_INT)
        ((int    *)result)[0]=(int)stddev;
      else if(type==SID_SIZE_T)
        ((size_t *)result)[0]=(size_t)stddev;
      else
        SID_trap_error("Unknown variable type in calc_min",ERROR_LOGIC);
    }
  }
}

