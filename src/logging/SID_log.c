#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <gbpSID.h>

void SID_log(const char *fmt, int mode, ...) {
    int     flag_write_time = GBP_FALSE;
    int     level_next;
    va_list vargs;
    va_start(vargs, mode);

    // If n_ranks>1 and ALLRANKS is turned-on in the mode, then
    // loop over all ranks, replacing the switch with ANYRANK
    // and LABELRANK, and then exit.  Turn-off SID_LOG_CHECKPOINT
    // to make sure that the call to SID_log() here does not block.
    if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_ALLRANKS)){
        mode&=(~SID_LOG_ALLRANKS);
        if(SID.n_proc>1){
            mode|=(SID_LOG_ANYRANK|SID_LOG_LABELRANK);
            for(int i_rank=0;i_rank<SID.n_proc;i_rank++){
                if(i_rank==SID.My_rank)
                    SID_log(fmt,mode&(~SID_LOG_CHECKPOINT),vargs);
                SID_Barrier(SID_COMM_WORLD);
            }
            return;
        }
    }

    if(SID.logging_active && (SID.I_am_Master || SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_ANYRANK)) && (SID.fp_log != NULL)) {
        if(SID.level < SID_LOG_MAX_LEVELS) {
            // If SID_LOG_NOPRINT is set, do not write anything (useful for changing indenting)
            int flag_print = GBP_TRUE;
            if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_NOPRINT))
                flag_print = GBP_FALSE;

            // If SID_LOG_IO_RATE is set, the first varg is the IO size
            double IO_size=0;
            if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_IO_RATE))
                IO_size = (double)((size_t)va_arg(vargs, size_t)) / (double)SID_SIZE_OF_MEGABYTE;

            // Close a log bracket
            if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_CLOSE)) {
                SID.level = GBP_MAX(0, SID.level - 1);
                if(SID.level < SID_LOG_MAX_LEVELS) {
                    if(SID.flag_use_timer[SID.level]) {
                        (void)time(&(SID.time_stop_level[SID.level]));
                        SID.time_total_level[SID.level] = (int)(SID.time_stop_level[SID.level] - SID.time_start_level[SID.level]);
                        flag_write_time                 = GBP_TRUE;
                    } else {
                        SID.time_stop_level[SID.level] = 0;
                        flag_write_time                = GBP_FALSE;
                    }
                }
            }
            // Set timer for comments
            else if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_COMMENT) && SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_TIMER)) {
                if(SID.level > 0 && SID.level < SID_LOG_MAX_LEVELS) {
                    if(SID.flag_use_timer[SID.level - 1]) {
                        (void)time(&(SID.time_stop_level[SID.level - 1]));
                        SID.time_total_level[SID.level] = (int)(SID.time_stop_level[SID.level - 1] - SID.time_start_level[SID.level - 1]);
                        flag_write_time                 = GBP_TRUE;
                    }
                }
            } else
                flag_write_time = GBP_FALSE;

            if(SID.level <= SID.verbosity && flag_print) {
                // Write indenting text
                if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_OPEN) && !SID.indent) {
                    fprintf(SID.fp_log, "\n");
                    SID.indent = GBP_TRUE;
                } else if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_COMMENT) && !SID.indent) {
                    fprintf(SID.fp_log, "\n");
                    SID.indent = GBP_TRUE;
                }
                if(SID.indent) {
                    for(int i_level = 0; i_level < SID.level; i_level++)
                        fprintf(SID.fp_log, "%s", SID_LOG_INDENT_STRING);
                }

                // Write a rank label, if required
                if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_LABELRANK))
                    fprintf(SID.fp_log,"[Rank %3d]: ",SID.My_rank);

                // Write text
                vfprintf(SID.fp_log, fmt, vargs);

                // Write closing text
                if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_CLOSE) || SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_COMMENT)) {
                    // Write time elapsed if SID_LOG_TIMER was set on opening
                    if(flag_write_time) {
                        char time_string[48];
                        SID_seconds2ascii(SID.time_total_level[SID.level], time_string);
                        fprintf(SID.fp_log, " (%s", time_string);
                        if(SID.IO_size[SID.level] > 0.)
                            fprintf(SID.fp_log, "; %3.1lf Mb/s", SID.IO_size[SID.level] / (double)SID.time_total_level[SID.level]);
                        fprintf(SID.fp_log, ")");
                    }
                    fprintf(SID.fp_log, "\n");
                }

                // Determine if the next log entry needs to be indented or not
                if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_CONTINUE) || SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_OPEN))
                    SID.indent = GBP_FALSE;
                else {
                    SID.indent = GBP_TRUE;
                }
            }

            // Open a new indent bracket
            if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_OPEN)) {
                if(SID.level < SID_LOG_MAX_LEVELS - 1) {
                    if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_TIMER)) {
                        SID.flag_use_timer[SID.level] = GBP_TRUE;
                        (void)time(&(SID.time_start_level[SID.level]));
                        SID.IO_size[SID.level] = IO_size;
                    } else {
                        SID.flag_use_timer[SID.level]   = GBP_FALSE;
                        SID.time_start_level[SID.level] = 0;
                    }
                    SID.level++;
                }
            }
        }
        fflush(SID.fp_log);
    }

#if USE_MPI
    if(SID_CHECK_BITFIELD_SWITCH(mode, SID_LOG_CHECKPOINT))
        SID_Barrier(SID_COMM_WORLD);
#endif

    va_end(vargs);
}
