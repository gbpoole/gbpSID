#include <unistd.h>
#include <gbpSID.h>

int SID_fclose(SID_fp *fp) {
#if USE_MPI
#if USE_MPI_IO
    MPI_File_sync(fp->fp);
    int r_val = MPI_File_close(&(fp->fp));
#else
    sync();
    int r_val = fclose(fp->fp);
#endif
#else
    sync();
    int r_val = fclose(fp->fp);
#endif
    return (r_val);
}
