#include <math.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void calc_stddev_global(void   *data,
    void   *result,
    size_t  n_data_local,
    SID_Datatype type,
    int          mode,
    SID_Comm    *comm){
  int     i_data;
  double  stddev;
  double  mean;
  size_t n_data;

  SID_Allreduce(&n_data_local,&n_data,1,SID_SIZE_T,SID_SUM,comm);
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
    if(check_mode_for_flag(mode,CALC_MODE_ABS)){
      calc_mean_global(data,&mean,n_data_local,type,CALC_MODE_RETURN_DOUBLE|CALC_MODE_ABS,comm);
      for(i_data=0,stddev=0.;i_data<n_data_local;i_data++){
        if(type==SID_DOUBLE)
          stddev+=pow(IABS((double)((double *)data)[i_data])-mean,2.);
        else if(type==SID_FLOAT)
          stddev+=pow(IABS((double)((float  *)data)[i_data])-mean,2.);
        else if(type==SID_INT)
          stddev+=pow(IABS((double)((int    *)data)[i_data])-mean,2.);
        else if(type==SID_UNSIGNED)
          stddev+=pow(IABS((double)((unsigned int *)data)[i_data])-mean,2.);
        else if(type==SID_SIZE_T)
          stddev+=pow(IABS((double)((size_t *)data)[i_data])-mean,2.);
        else
          SID_trap_error("Unknown variable type in calc_stddev",ERROR_LOGIC);
      }
    }
    else{
      calc_mean_global(data,&mean,n_data_local,type,CALC_MODE_RETURN_DOUBLE,comm);
      for(i_data=0,stddev=0.;i_data<n_data_local;i_data++){
        if(type==SID_DOUBLE)
          stddev+=pow((double)((double *)data)[i_data]-mean,2.);
        else if(type==SID_FLOAT)
          stddev+=pow((double)((float  *)data)[i_data]-mean,2.);
        else if(type==SID_INT)
          stddev+=pow((double)((int    *)data)[i_data]-mean,2.);
        else if(type==SID_UNSIGNED)
          stddev+=pow((double)((unsigned int *)data)[i_data]-mean,2.);
        else if(type==SID_SIZE_T)
          stddev+=pow((double)((size_t *)data)[i_data]-mean,2.);
        else
          SID_trap_error("Unknown variable type in calc_stddev",ERROR_LOGIC);
      }
    }
    SID_Allreduce(SID_IN_PLACE,&stddev, 1,SID_DOUBLE,SID_SUM,comm);
    stddev=sqrt(stddev/(double)n_data);
    if(type==SID_DOUBLE || check_mode_for_flag(mode,CALC_MODE_RETURN_DOUBLE))
      ((double *)result)[0]=(double)stddev;
    else if(type==SID_FLOAT)
      ((float  *)result)[0]=(float)stddev;
    else if(type==SID_INT)
      ((int    *)result)[0]=(int)stddev;
    else if(type==SID_UNSIGNED)
      ((unsigned int *)result)[0]=(unsigned int)stddev;
    else if(type==SID_SIZE_T)
      ((size_t *)result)[0]=(size_t)stddev;
    else
      SID_trap_error("Unknown variable type in calc_min",ERROR_LOGIC);
  }
}
