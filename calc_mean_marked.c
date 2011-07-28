#include <common.h>

double calc_mean_marked(double *data,
                        int    *marked,
		        int     n_data){
  int     n_marked;
  int     i;
  double  rval;
  for(i=0,n_marked=0;i<n_data;i++)
    if(marked[i])
      n_marked++;
  if(n_marked>1){
    for(rval=0.,i=0;i<n_data;i++)
      if(marked[i]) rval+=data[i];
    rval/=(double)n_marked;
  }
  else
    rval=0.;
  return(rval);
}
