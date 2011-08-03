#include <gbpCommon.h>
#include <gbpSID.h>

size_t SID_fread_chunked_ordered(void   *buffer,
                                 size_t  n_x_read_local,
                                 SID_fp *fp){
  int    i_chunk;
  int    i_group;
  int    i_rank;
  size_t i_x_offset_local;
  size_t n_x_read_local_bcast;
  size_t i_x_read_chunk;
  size_t i_x_offset_global;
  size_t i_x_chunk;
  size_t n_skip;
  size_t n_x_chunk;
  size_t n_x_chunk_max;
  size_t header_size;
  size_t r_val=0;
  char   filename_chunk[256];

  // Operates the same way as SID_fread_chunked() except i_x_offset_local is 
  //   computed here under the assumption that reads are done in order by rank
  i_x_offset_local=0;
#if USE_MPI
  for(i_rank=0;i_rank<SID.n_proc;i_rank++){
    n_x_read_local_bcast=n_x_read_local;
    SID_Bcast(&n_x_read_local_bcast,sizeof(size_t),i_rank,SID.COMM_WORLD);
    if(i_rank<SID.My_rank)
      i_x_offset_local+=n_x_read_local_bcast;
  }
#endif

  i_x_offset_global=fp->last_item;
  for(i_chunk=0,i_x_read_chunk=0,i_x_chunk=i_x_offset_local+i_x_offset_global;
      i_chunk<fp->chunked_header.n_chunk;
      i_chunk++){
    if(fp->i_x_start_chunk[i_chunk]<=i_x_chunk && fp->i_x_last_chunk[i_chunk]>=i_x_chunk){
      n_skip   =i_x_chunk-fp->i_x_start_chunk[i_chunk];
      n_x_chunk=MIN(n_x_read_local-i_x_read_chunk,fp->i_x_step_chunk[i_chunk]-n_skip);
    }
    else{
      n_x_chunk=0;
      n_skip   =0;
    }
    SID_Allreduce(&n_x_chunk,&n_x_chunk_max,1,SID_SIZE_T,SID_MAX,SID.COMM_WORLD);
    if(n_x_chunk_max>0){
      sprintf(filename_chunk,"%s.%d",fp->filename_root,i_chunk);
#if !USE_MPI_IO
      for(i_group=0;i_group<SID.n_proc;i_group++){
        if(SID.My_group==i_group && n_x_chunk>0){
#endif
          SID_fopen(filename_chunk,"r",fp);
          if(n_x_chunk>0){
            SID_fseek(fp,
                      1,
                      fp->header_offset[i_chunk]+n_skip*fp->chunked_header.item_size,
                      SID_SEEK_SET);
            SID_fread((char *)buffer+i_x_read_chunk*fp->chunked_header.item_size,
                      fp->chunked_header.item_size,
                      n_x_chunk,
                      fp);
            i_x_chunk     +=n_x_chunk;
            i_x_read_chunk+=n_x_chunk;
          }
          SID_fclose(fp);
#if !USE_MPI_IO
        }
        SID_Barrier(SID.COMM_WORLD);
      }
#endif
    }
  }
  SID_Allreduce(&i_x_chunk,&(fp->last_item),1,SID_SIZE_T,SID_MAX,SID.COMM_WORLD);
  //fp->last_item--;
  return(r_val);
}

