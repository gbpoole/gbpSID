#include <string.h>
#include <stdarg.h>
#include <gbpCommon.h>
#include <gbpSID.h>

int SID_fopen_chunked(char   *filename_root,
                      char   *mode,
                      SID_fp *fp,
                      void   *header, ...){
  int     i_chunk;
  int     i_group;
  int     n_chunk;
  int     r_val=TRUE;
  SID_fp  fp_temp;
  char    filename_temp[256];
  va_list vargs;
  chunked_subheader_info read_subheader;
  chunked_header_info    read_header;
  va_start(vargs,header);
  fp->header   =header;
  fp->last_item=0;
  strcpy(fp->filename_root,filename_root);
  if(!strcmp(mode,"r")){
    i_chunk=0;
    sprintf(filename_temp,"%s.%d",fp->filename_root,i_chunk);
#if USE_MPI_IO
    for(i_group=0;i_group<SID.n_groups;i_group++){
      if(SID.My_group==i_group){
#endif
        SID_fopen(filename_temp,"r",&fp_temp);
        SID_fread_all(&(fp->chunked_header),sizeof(chunked_header_info),1,&fp_temp);
        if(fp->header!=NULL && fp->chunked_header.header_size>0)
          SID_fread_all(fp->header,fp->chunked_header.header_size,1,&fp_temp);
        else
          fp->chunked_header.header_size=0;
        SID_fread_all(&read_subheader,sizeof(chunked_subheader_info),1,&fp_temp);
        SID_fclose(&fp_temp);
#if USE_MPI_IO
      }
      SID_Barrier(SID.COMM_WORLD);
    }
#endif
    fp->i_x_step_chunk =(size_t *)SID_malloc(sizeof(size_t)*fp->chunked_header.n_chunk);
    fp->i_x_start_chunk=(size_t *)SID_malloc(sizeof(size_t)*fp->chunked_header.n_chunk);
    fp->i_x_last_chunk =(size_t *)SID_malloc(sizeof(size_t)*fp->chunked_header.n_chunk);
    fp->header_offset  =(size_t *)SID_malloc(sizeof(size_t)*fp->chunked_header.n_chunk);
    fp->i_x_start_chunk[0]=0;
    fp->i_x_step_chunk[0] =read_subheader.n_items;
    fp->i_x_last_chunk[0] =read_subheader.n_items-1;
    fp->header_offset[0]  =sizeof(chunked_header_info)+fp->chunked_header.header_size+sizeof(chunked_subheader_info);
    for(i_chunk=1;i_chunk<fp->chunked_header.n_chunk;i_chunk++){
      sprintf(filename_temp,"%s.%d",fp->filename_root,i_chunk);
#if USE_MPI_IO
      for(i_group=0;i_group<SID.n_groups;i_group++){
        if(SID.My_group==i_group){
#endif
          SID_fopen(filename_temp,"r",&fp_temp);
          SID_fread_all(&read_subheader,sizeof(chunked_subheader_info), 1,&fp_temp);
          SID_fclose(&fp_temp);
#if USE_MPI_IO
        }
        SID_Barrier(SID.COMM_WORLD);
      }
#endif
      fp->i_x_start_chunk[i_chunk]=fp->i_x_last_chunk[i_chunk-1]+1;
      fp->i_x_step_chunk[i_chunk] =read_subheader.n_items;
      fp->i_x_last_chunk[i_chunk] =fp->i_x_start_chunk[i_chunk]+fp->i_x_step_chunk[i_chunk]-1;
      fp->header_offset[i_chunk]  =sizeof(chunked_subheader_info);
    }
  }
  else if(!strcmp(mode,"w")){
    fp->chunked_header.header_size=(size_t)va_arg(vargs,size_t);
    if(fp->header==NULL)
      fp->chunked_header.header_size=0;
    fp->chunked_header.n_items    =(size_t)va_arg(vargs,size_t);
    fp->chunked_header.item_size  =(size_t)va_arg(vargs,size_t);
    fp->chunked_header.n_chunk    =(int)   va_arg(vargs,int);
    fp->i_x_step_chunk            =(size_t *)SID_malloc(sizeof(size_t)*fp->chunked_header.n_chunk);
    fp->i_x_start_chunk           =(size_t *)SID_malloc(sizeof(size_t)*fp->chunked_header.n_chunk);
    fp->i_x_last_chunk            =(size_t *)SID_malloc(sizeof(size_t)*fp->chunked_header.n_chunk);
    fp->header_offset             =(size_t *)SID_malloc(sizeof(size_t)*fp->chunked_header.n_chunk);
    fp->i_x_step_chunk[0]         =(int)(0.5+(double)fp->chunked_header.n_items/(double)fp->chunked_header.n_chunk);
    fp->i_x_start_chunk[0]        =0;
    fp->i_x_last_chunk[0]         =fp->i_x_step_chunk[0]-1;
    fp->header_offset[0]          =sizeof(chunked_header_info)+fp->chunked_header.header_size+sizeof(chunked_subheader_info);
    for(i_chunk=1;i_chunk<(fp->chunked_header.n_chunk)-1;i_chunk++){
      fp->i_x_step_chunk[i_chunk] =fp->i_x_step_chunk[i_chunk-1];
      fp->i_x_start_chunk[i_chunk]=fp->i_x_last_chunk[i_chunk-1]+1;
      fp->i_x_last_chunk[i_chunk] =fp->i_x_last_chunk[i_chunk-1]+fp->i_x_step_chunk[i_chunk];
      fp->header_offset[i_chunk]  =sizeof(chunked_subheader_info);
    }
    if(fp->chunked_header.n_chunk>1)
      fp->i_x_start_chunk[fp->chunked_header.n_chunk-1]=fp->i_x_last_chunk[i_chunk-1]+1;
    fp->i_x_last_chunk[fp->chunked_header.n_chunk-1]=fp->chunked_header.n_items-1;
    fp->i_x_step_chunk[fp->chunked_header.n_chunk-1]=
      fp->i_x_last_chunk[fp->chunked_header.n_chunk-1]-
      fp->i_x_start_chunk[fp->chunked_header.n_chunk-1]+1;
    fp->header_offset[fp->chunked_header.n_chunk-1]=sizeof(chunked_subheader_info);
    if(SID.I_am_Master){
      for(i_chunk=0;i_chunk<(fp->chunked_header.n_chunk);i_chunk++){
        sprintf(filename_temp,"%s.%d",fp->filename_root,i_chunk);
        remove(filename_temp);
      }
    }
  }
  else
    r_val=FALSE;
  va_end(vargs);
  return(r_val);
}

