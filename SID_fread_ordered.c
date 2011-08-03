#include <gbpSID.h>

size_t SID_fread_ordered(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp){
  size_t r_val;
#if USE_MPI
#if USE_MPI_IO
  int    r_val_i;
  MPI_Status status;
  MPI_File_read_ordered(fp->fp,
                        buffer,
                        size_per_item*n_items,
                        MPI_BYTE,
                        &status);
  MPI_Get_count(&status,MPI_BYTE,&r_val_i);
  r_val=(size_t)r_val_i/size_per_item;
#else
  r_val=fread(buffer,
              size_per_item,
              n_items,
              fp->fp);
#endif
#else
  r_val=fread(buffer,
              size_per_item,
              n_items,
              fp->fp);
#endif
  return(r_val);
}

