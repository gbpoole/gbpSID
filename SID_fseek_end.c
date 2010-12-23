#include <gbpSID.h>

void SID_fseek_end(SID_fp *fp){
#ifdef USE_MPI
#ifdef USE_MPI_IO
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

