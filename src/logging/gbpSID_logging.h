#ifndef GBPSID_LOGGING_H
#define GBPSID_LOGGING_H

#define SID_ERROR_HEADER "ERROR:"
#define SID_WARNING_HEADER "WARNING:"
#define SID_LOG_INDENT_STRING "   "

#define SID_WARNING_DEFAULT SID_DEFAULT_MODE

#define SID_LOG_MAX_LEVELS 16
#define SID_LOG_OPEN SID_TTTP00
#define SID_LOG_CLOSE SID_TTTP01
#define SID_LOG_TIMER SID_TTTP02
#define SID_LOG_CONTINUE SID_TTTP03
#define SID_LOG_IO_RATE SID_TTTP04
#define SID_LOG_COMMENT SID_TTTP05
#define SID_LOG_NOPRINT SID_TTTP06
#define SID_LOG_ANYRANK SID_TTTP07
#define SID_LOG_ALLRANKS SID_TTTP08
#define SID_LOG_LABELRANK SID_TTTP09
#define SID_LOG_CHECKPOINT SID_TTTP10
#define SID_LOG_SILENT_CLOSE (SID_LOG_CLOSE | SID_LOG_NOPRINT)

#define SID_SET_VERBOSITY_RELATIVE SID_DEFAULT_MODE
#define SID_SET_VERBOSITY_ABSOLUTE SID_TTTP00
#define SID_SET_VERBOSITY_DEFAULT SID_SET_VERBOSITY_RELATIVE

// Datastructure for managing progress counters
typedef struct pcounter_info pcounter_info;
struct pcounter_info {
    size_t n_i;
    size_t i_report_next;
    size_t i_report;
    size_t n_report;
};

// Function declarations
#ifdef __cplusplus
extern "C" {
#endif

void SID_log(const char *fmt, int mode, ...);
void SID_log_set_fp(FILE *fp);
void SID_log_error(const char *fmt, ...);
void SID_log_warning(const char *fmt, int mode, ...);
void SID_log_header();
void SID_log_footer();
void SID_set_verbosity(int mode, ...);
void SID_Init_pcounter(pcounter_info *pcounter, size_t n_i, int n_report);
void SID_check_pcounter(pcounter_info *pcounter, size_t i);

#ifdef __cplusplus
}
#endif

#endif
