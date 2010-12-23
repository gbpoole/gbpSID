#include <string.h>
#include <gbpCommon.h>
#include <gbpSID.h>

int SID_remove_chunked(char *filename_root){
   int     i_chunk;
   int     r_val=TRUE;
   SID_fp  fp_temp;
   char    filename_temp[256];
   chunked_header_info    header;
   sprintf(filename_temp,"%s.%d",filename_root,0);
   SID_fopen(filename_temp,"r",&fp_temp);
   SID_fread_all(&header,sizeof(chunked_header_info),1,&fp_temp);
   SID_fclose(&fp_temp);
   if(SID.I_am_Master){
     for(i_chunk=0;i_chunk<header.n_chunk;i_chunk++){
       sprintf(filename_temp,"%s.%d",filename_root,i_chunk);
       remove(filename_temp);
     }
   }
   return(r_val);
}

