#include <gbpSID.h>

void SID_fseek_end(SID_fp *fp){
#if USE_MPI
#if USE_MPI_IO
   MPI_File_seek(fp->fp,
                 0,
                 MPI_SEEK_END);
#else
   fseeko(fp->fp,
          0,
          SEEK_END);
#endif
#else
   fseeko(fp->fp,
          0,
          SEEK_END);
#endif
}

