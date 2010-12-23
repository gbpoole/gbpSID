#include <gbpCommon.h>
#include <gbpSID.h>

#define MAX_SEND_LOCAL 100*SIZE_OF_MEGABYTE

size_t SID_fread_all(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp){
  size_t r_val;
#ifdef USE_MPI
#ifdef USE_MPI_IO
  int    r_val_i;
  MPI_Status status;
  MPI_File_read_all(fp->fp,
                    buffer,
                    size_per_item*n_items,
                    MPI_BYTE,
                    &status);
  MPI_Get_count(&status,MPI_BYTE,&r_val_i);
  r_val=(size_t)r_val_i/size_per_item;
#else
  size_t size_send,size_left,size_offset;
  if(size_per_item*n_items>0){
    if(SID.I_am_Master){
      r_val=fread(buffer,
                  size_per_item,
                  n_items,
                  fp->fp);
    }
    else{
      fseek(fp->fp,
            size_per_item*n_items,
            SEEK_CUR); 
    }
    size_left  =size_per_item*n_items;
    size_offset=0;
    while(size_left>0){
      size_send=MIN(size_left,MAX_SEND_LOCAL);
      MPI_Bcast(&(((char *)buffer)[size_offset]),(int)(size_send),MPI_BYTE,MASTER_RANK,MPI_COMM_WORLD);
      size_left  -=size_send;
      size_offset+=size_send;
    }
    MPI_Bcast(&r_val,1,MPI_SIZE_T,MASTER_RANK,MPI_COMM_WORLD);
  }
  else
    r_val=0;
#endif
#else
  r_val=fread(buffer,
              size_per_item,
              n_items,
              fp->fp);
#endif
  return(r_val);
}

