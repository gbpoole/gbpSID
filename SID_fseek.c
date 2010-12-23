#include <gbpSID.h>

void SID_fseek(size_t size_per_item,
               size_t n_items,
               SID_fp *fp){
#ifdef USE_MPI
#ifdef USE_MPI_IO
   MPI_File_seek(fp->fp,
                 size_per_item*n_items,
                 MPI_SEEK_SET);
#else
   fseeko(fp->fp,
          (off_t)(size_per_item*n_items),
          SEEK_SET);
#endif
#else
   fseeko(fp->fp,
          (off_t)(size_per_item*n_items),
          SEEK_SET);
#endif
}

