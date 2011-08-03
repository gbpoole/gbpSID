#include <stdio.h>
#include <gbpSID.h>

void SID_frewind(SID_fp *fp){
  #if USE_MPI
  #if USE_MPI_IO
    MPI_File_seek(fp->fp,
                  0,
                  MPI_SEEK_SET);
  #else
    rewind(fp->fp);
  #endif
  #else
    rewind(fp->fp);
  #endif
  fp->last_item=0;
}

