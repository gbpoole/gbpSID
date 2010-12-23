#include <gbpSID.h>
#include <unistd.h>

size_t SID_fwrite_all(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp){
  size_t r_val;
#ifdef USE_MPI
#ifdef USE_MPI_IO
  int    r_val_i;
  MPI_Status status;
  MPI_File_write_all(fp->fp,
                 buffer,
                 size_per_item*n_items,
                 MPI_BYTE,
                 &status);
  MPI_Get_count(&status,MPI_BYTE,&r_val_i);
  r_val=(size_t)r_val_i/size_per_item;
#else
  r_val=fwrite(buffer,
               size_per_item,
               n_items,
               fp->fp);
  sync();
#endif
#else
  r_val=fwrite(buffer,
               size_per_item,
               n_items,
               fp->fp);
  sync();
#endif
  return(r_val);
}

