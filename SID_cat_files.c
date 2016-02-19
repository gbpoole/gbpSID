#include <sys/stat.h>
#include <stdarg.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_cat_files(const char *filename_out,
                   int   mode,
                   int   n_files, ...){
  int      i_file;
  char    *filename_in;
  va_list  vargs;
  FILE    *fp_in;
  FILE    *fp_out;
  int      r_val;
  int      flag_clean;
  struct   stat file_stats;
  size_t   n_bytes;
  size_t   n_bytes_buffer;
  void    *buffer;

  va_start(vargs,n_files);

  SID_log("Concatinating %d files to output {%s}...",SID_LOG_OPEN|SID_LOG_TIMER,n_files,filename_out);

  // Interpret mode
  if(check_mode_for_flag(mode,SID_CAT_CLEAN)) flag_clean=TRUE;
  else                                        flag_clean=FALSE;

  // Open output file
  fp_out=fopen(filename_out,"w");
  if(fp_out==NULL)
    SID_trap_error("Could not open file {%s}!",ERROR_IO_OPEN,filename_out);
  buffer=SID_malloc(IO_BUFFER_SIZE);

  // Loop over the files to be concatinated...
  for(i_file=0;i_file<n_files;i_file++){
    // Open next file and get file size
    filename_in=(char *)va_arg(vargs,char *);
    r_val      =stat(filename_in,&file_stats);
    if(r_val!=0)
      SID_trap_error("Could not open file {%s}!",ERROR_IO_OPEN,filename_in);
    else
      SID_log("Processing {%s}...",SID_LOG_OPEN,filename_in);
    n_bytes=file_stats.st_size;
    fp_in  =fopen(filename_in,"r");

    // Copy this input file to the output file in chunks ...
    n_bytes_buffer=MIN(n_bytes,IO_BUFFER_SIZE);
    while(n_bytes_buffer>0){
      // Read
      r_val=fread_verify(buffer,
                         1,
                         n_bytes_buffer,
                         fp_in);
      // Write
      r_val=fwrite(buffer,
                   1,
                   n_bytes_buffer,
                   fp_out);
      // Adjust buffer size
      n_bytes-=n_bytes_buffer;
      n_bytes_buffer=MIN(n_bytes,IO_BUFFER_SIZE);
    }

    // Close input file and remove it if asked to
    fclose(fp_in);
    if(flag_clean)
      remove(filename_in);

    SID_log("Done.",SID_LOG_CLOSE);
  }

  // Clean-up
  fclose(fp_out);
  SID_free(SID_FARG buffer);

  SID_log("Done.",SID_LOG_CLOSE);

  va_end(vargs);
}
