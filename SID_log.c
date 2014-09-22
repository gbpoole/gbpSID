#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <gbpCommon.h>
#include <gbpSID.h>

void SID_log(const char *fmt, int mode, ...){
  int     flag_write_time;
  int     flag_print=TRUE;
  int     i_level;
  int     level_next;
  char    time_string[48];
  double  IO_size;
  va_list vargs;
  va_start(vargs,mode);

  if(SID.awake && (SID.I_am_Master || check_mode_for_flag(mode,SID_LOG_ALLRANKS)) && (SID.fp_log != NULL)){
    if(SID.level<SID_LOG_MAX_LEVELS){
      // If SID_LOG_NOPRINT is set, do not write anything (useful for changing indenting)
      if(check_mode_for_flag(mode,SID_LOG_NOPRINT))
        flag_print=FALSE;

      // If SID_LOG_IO_RATE is set, the first varg is the IO size
      if(check_mode_for_flag(mode,SID_LOG_IO_RATE))
        IO_size=(double)((size_t)va_arg(vargs,size_t))/(double)SIZE_OF_MEGABYTE;
      else
        IO_size=0.;

      // Close a log bracket
      if(check_mode_for_flag(mode,SID_LOG_CLOSE)){
        SID.level=MAX(0,SID.level-1);
        if(SID.level<SID_LOG_MAX_LEVELS){
          if(SID.flag_use_timer[SID.level]){
            (void)time(&(SID.time_stop_level[SID.level]));
            SID.time_total_level[SID.level]=(int)
              (SID.time_stop_level[SID.level]-
               SID.time_start_level[SID.level]);
            flag_write_time=TRUE;
          }
          else{
            SID.time_stop_level[SID.level]=0;
            flag_write_time=FALSE;
          }
        }
      }
      else if(check_mode_for_flag(mode,SID_LOG_COMMENT) && check_mode_for_flag(mode,SID_LOG_TIMER)){
        if(SID.level>0 && SID.level<SID_LOG_MAX_LEVELS){
          if(SID.flag_use_timer[SID.level-1]){
            (void)time(&(SID.time_stop_level[SID.level-1]));
            SID.time_total_level[SID.level]=(int)
              (SID.time_stop_level[SID.level-1]-
               SID.time_start_level[SID.level-1]);
            flag_write_time=TRUE;
          }
        }
      }
      else
        flag_write_time=FALSE;

      if(SID.level<=SID.verbosity && flag_print){

        // Write indenting text
        if(check_mode_for_flag(mode,SID_LOG_OPEN) && !SID.indent){
          fprintf(SID.fp_log,"\n");
          SID.indent=TRUE;
        }
        else if(check_mode_for_flag(mode,SID_LOG_COMMENT) && !SID.indent){
          fprintf(SID.fp_log,"\n");
          SID.indent=TRUE;
        }
/*
        else if(check_mode_for_flag(mode,SID_LOG_CONTINUE))
          SID.indent=FALSE;
*/
        if(SID.indent){
          for(i_level=0;i_level<SID.level;i_level++)
            fprintf(SID.fp_log,"%s",SID_LOG_INDENT_STRING);
        }

        // Write text
        vfprintf(SID.fp_log,fmt,vargs);

        // Write closing text
        if(check_mode_for_flag(mode,SID_LOG_CLOSE) || check_mode_for_flag(mode,SID_LOG_COMMENT)){
          // Write time elapsed if SID_LOG_TIMER was set on opening
          if(flag_write_time){
            seconds2ascii(SID.time_total_level[SID.level],time_string);
            fprintf(SID.fp_log," (%s",time_string);
            if(SID.IO_size[SID.level]>0.)
              fprintf(SID.fp_log,"; %3.1lf Mb/s",SID.IO_size[SID.level]/(double)SID.time_total_level[SID.level]);
            fprintf(SID.fp_log,")");
          }
          fprintf(SID.fp_log,"\n");
        }

        // Determine if the next log entry needs to be indented or not
        if(check_mode_for_flag(mode,SID_LOG_CONTINUE) ||
           check_mode_for_flag(mode,SID_LOG_OPEN)) 
          SID.indent=FALSE;
        else{
          SID.indent=TRUE;
        }
      }

      // Open a new indent bracket
      if(check_mode_for_flag(mode,SID_LOG_OPEN)){
        if(SID.level<SID_LOG_MAX_LEVELS-1){
          if(check_mode_for_flag(mode,SID_LOG_TIMER)){
            SID.flag_use_timer[SID.level]=TRUE;
            (void)time(&(SID.time_start_level[SID.level]));
            SID.IO_size[SID.level]=IO_size;
          }
          else{
            SID.flag_use_timer[SID.level]  =FALSE;
            SID.time_start_level[SID.level]=0;
          }
          SID.level++;
        }
      }
    }
    fflush(SID.fp_log);
  }

#if USE_MPI
  if(check_mode_for_flag(mode,SID_LOG_CHECKPOINT))
    SID_Barrier(SID.COMM_WORLD);
#endif

  va_end(vargs);
}

