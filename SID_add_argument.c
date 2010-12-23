#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SID.h>
#include <gbpSID.h>

void SID_add_argument(char      short_name[SID_ARG_LENGTH],
		      char      description[SID_ARG_LENGTH],
		      int       data_type,
                      int       required_or_not,
                      void     *default_value){
   SID_arg n_out;
   n_out={NULL,
          short_name,
          description,
          data_type,
          required_or_not,
          default_value};
 
}

