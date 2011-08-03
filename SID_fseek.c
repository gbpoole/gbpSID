#include <gbpSID.h>

void SID_fseek(SID_fp *fp,
               size_t  size_per_item,
               size_t  n_items,
               int     origin){
#if USE_MPI
#if USE_MPI_IO
   MPI_File_seek(fp->fp,
                 size_per_item*n_items,
                 origin);
#else
   fseeko(fp->fp,
          (off_t)(size_per_item*n_items),
          origin);
#endif
#else
   fseeko(fp->fp,
          (off_t)(size_per_item*n_items),
          origin);
#endif
}

