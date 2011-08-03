#include <gbpSID.h>

void SID_fskip(size_t size_per_item,
               size_t n_items,
               SID_fp *fp){
#if USE_MPI
#if USE_MPI_IO
   MPI_File_seek(fp->fp,
                 size_per_item*n_items,
                 MPI_SEEK_CUR);
#else
   fseeko(fp->fp,
          (off_t)(size_per_item*n_items),
          SEEK_CUR);
#endif
#else
   fseeko(fp->fp,
          (off_t)(size_per_item*n_items),
          SEEK_CUR);
#endif
}

