#include <gbpLib.h>
#include <gbpStats.h>

void calc_max_global(void   *data_local,
                     void   *result,
 	    	     size_t  n_data_local,
                     SID_Datatype     type,
                     int              mode,
                     SID_Comm        *comm){
  calc_max(data_local,result,n_data_local,type,mode);
  if(check_mode_for_flag(mode,CALC_MODE_RETURN_DOUBLE))
    SID_Allreduce(SID_IN_PLACE,result,1,SID_DOUBLE,SID_MAX,comm);
  else
    SID_Allreduce(SID_IN_PLACE,result,1,type,      SID_MAX,comm);
}
