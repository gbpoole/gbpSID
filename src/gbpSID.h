#ifndef SID_H
#define SID_H
#include <stdio.h>     // Needed for type FILE
#include <sys/types.h> // Needed for type time_t
#include <stdarg.h>
#if USE_MPI
#include <mpi.h>
#endif

#ifndef _FILE_H
#define _FILE_H
#if _FILE_C
#define _FILE_C_CLASS
#else
#define _FILE_C_CLASS extern
#endif
_FILE_C_CLASS int a;
_FILE_C_CLASS int b;
#endif

// TTPXX=Two-to-the-power-XX
#define SID_DEFAULT_MODE 0
#define SID_TTTP00 1
#define SID_TTTP01 2
#define SID_TTTP02 4
#define SID_TTTP03 8
#define SID_TTTP04 16
#define SID_TTTP05 32
#define SID_TTTP06 64
#define SID_TTTP07 128
#define SID_TTTP08 256
#define SID_TTTP09 512
#define SID_TTTP10 1024
#define SID_TTTP11 2048
#define SID_TTTP12 4096
#define SID_TTTP13 8192
#define SID_TTTP14 16384
#define SID_TTTP15 32768
#define SID_TTTP16 65536
#define SID_TTTP17 131072
#define SID_TTTP18 262144
#define SID_TTTP19 524288
#define SID_TTTP20 1048576
#define SID_TTTP21 2097152
#define SID_TTTP22 4194304
#define SID_TTTP23 8388608
#define SID_TTTP24 16777216
#define SID_TTTP25 33554432
#define SID_TTTP26 67108864
#define SID_TTTP27 134217728
#define SID_TTTP28 268435456
#define SID_TTTP29 536870912
#define SID_TTTP30 1073741824
#define SID_TTTP31 2147483648
#define SID_TTTP32 4294967296

// Some preferred sizes
#define SID_IO_BUFFER_SIZE 4096
#define SID_MAX_FILENAME_LENGTH 256

// Storage sizes
#define SID_SIZE_OF_KILOBYTE 1024
#define SID_SIZE_OF_MEGABYTE 1048576
#define SID_SIZE_OF_GIGIBYTE 1073741824

// Some common macros
#define GBP_TRUE 1
#define GBP_FALSE 0
#define GBP_MIN(A, B) ((A) < (B) ? (A) : (B))
#define GBP_MAX(A, B) ((A) > (B) ? (A) : (B))
#define GBP_IABS(A) ((A) < 0 ? -(A) : (A))

// Compile flags to control large variables
#if USE_DOUBLE
#define GBPREAL double
#else
#define GBPREAL float
#endif
#define big_int long long
#define id_int size_t

// MPI
#if USE_MPI
#if USE_DOUBLE
#define MPI_MY_REAL MPI_DOUBLE
#else
#define MPI_MY_REAL MPI_FLOAT
#endif
#define MPI_SIZE_T MPI_LONG_LONG
#endif

// Error messages
#define SID_ERROR_NONE 0
#define SID_ERROR_SYNTAX SID_TTTP01
#define SID_ERROR_LOGIC SID_TTTP02
#define SID_ERROR_IO_OPEN SID_TTTP03
#define SID_ERROR_IO_READ SID_TTTP04
#define SID_ERROR_IO_WRITE SID_TTTP05
#define SID_ERROR_MEMORY SID_TTTP06

#define SID_MASTER_RANK 0

#define SID_N_IO_FILES_MAX 64

#define SID_ERROR_HEADER "ERROR:"
#define SID_WARNING_HEADER "WARNING:"
#define SID_LOG_INDENT_STRING "   "

#define SID_WARNING_DEFAULT SID_DEFAULT_MODE

#define SID_FARG (void **)&

#define SID_LOG_MAX_LEVELS 30
#define SID_LOG_OPEN SID_TTTP00
#define SID_LOG_CLOSE SID_TTTP01
#define SID_LOG_TIMER SID_TTTP02
#define SID_LOG_CONTINUE SID_TTTP03
#define SID_LOG_IO_RATE SID_TTTP04
#define SID_LOG_COMMENT SID_TTTP05
#define SID_LOG_NOPRINT SID_TTTP06
#define SID_LOG_ALLRANKS SID_TTTP07
#define SID_LOG_CHECKPOINT SID_TTTP08
#define SID_LOG_SILENT_CLOSE SID_LOG_CLOSE | SID_LOG_NOPRINT

#define SID_SET_VERBOSITY_DEFAULT SID_DEFAULT_MODE
#define SID_SET_VERBOSITY_ABSOLUTE SID_TTTP00
#define SID_SET_VERBOSITY_RELATIVE SID_TTTP01

#define SID_INFO_RESULT SID_TTTP01
#define SID_INFO_MASTER SID_TTTP02

#define SID_PROFILE_DEFAULT SID_TTTP01
#define SID_PROFILE_MPIENABLED SID_TTTP02
#define SID_PROFILE_NOTMPIENABLED SID_TTTP03

#define SID_CAT_DEFAULT SID_DEFAULT_MODE
#define SID_CAT_CLEAN SID_TTTP01

#if USE_MPI
#define SID_MAXLENGTH_PROCESSOR_NAME MPI_MAX_PROCESSOR_NAME
#else
#define SID_MAXLENGTH_PROCESSOR_NAME 64
#endif

#if USE_MPI_IO
#define SID_SEEK_SET MPI_SEEK_SET
#define SID_SEEK_CUR MPI_SEEK_CUR
#else
#define SID_SEEK_SET SEEK_SET
#define SID_SEEK_CUR SEEK_CUR
#endif

#if USE_MPI
#define SID_COMM_WORLD (SID.COMM_WORLD->comm)
#define SID_IN_PLACE MPI_IN_PLACE
#define SID_COMM_NULL MPI_COMM_NULL
#define SID_GROUP_EMPTY MPI_GROUP_EMPTY
#define SID_Datatype MPI_Datatype
#define SID_CHAR MPI_CHAR
#define SID_INT MPI_INT
#define SID_UNSIGNED MPI_UNSIGNED
#define SID_LONG_LONG MPI_LONG_LONG
#define SID_LONG MPI_LONG
#define SID_SIZE_T MPI_LONG_LONG
#define SID_FLOAT MPI_FLOAT
#define SID_DOUBLE MPI_DOUBLE
#define SID_BYTE MPI_BYTE
#define SID_Op MPI_Op
#define SID_SUM MPI_SUM
#define SID_MAX MPI_MAX
#define SID_MIN MPI_MIN
#else
#define SID_COMM_WORLD NULL
#define SID_IN_PLACE NULL
#define SID_COMM_NULL NULL
#define SID_GROUP_EMPTY NULL
#define SID_Datatype int
#define SID_LONG_LONG SID_TTTP01
#define SID_LONG SID_TTTP02
#define SID_FLOAT SID_TTTP03
#define SID_DOUBLE SID_TTTP04
#define SID_INT SID_TTTP05
#define SID_UNSIGNED SID_TTTP06
#define SID_SIZE_T SID_TTTP07
#define SID_BYTE SID_TTTP08
#define SID_CHAR SID_TTTP09
#define SID_Op int
#define SID_SUM SID_TTTP01
#define SID_MAX SID_TTTP02
#define SID_MIN SID_TTTP03
#endif
#if USE_DOUBLE
#define SID_REAL SID_DOUBLE
#else
#define SID_REAL SID_FLOAT
#endif

// Structures for parsing the command line
typedef void **        SID_args;
typedef struct SID_arg SID_arg;
struct SID_arg {
    char *key;
    char *var_name;
    char *description;
    int   type;
    int   flag_required;
    void *val;
};

// Custom variadic arguments functions
#define SID_MAX_VARGS_STREAM_SIZE 128
typedef struct gbp_va_list gbp_va_list;
struct gbp_va_list {
    char stream[SID_MAX_VARGS_STREAM_SIZE];
    int  stream_position;
};

typedef struct SID_Comm SID_Comm;
struct SID_Comm {
#if USE_MPI
    MPI_Comm  comm;
    MPI_Group group;
#else
    char *comm;
    char *group;
#endif
    int n_proc;
    int My_rank;
};

// Structure to store SID info
typedef struct SID_info SID_info;
struct SID_info {
    FILE *  fp_log;
    FILE *  fp_in;
    int     error_state;
    int     awake;
    int     verbosity;
    int     level;
    int     indent;
    int     My_rank;
    int     n_proc;
    char *  My_node;
    int     I_am_Master;
    int     I_am_last_rank;
    int     rank_to_left;
    int     rank_to_right;
    time_t  time_start;
    time_t  max_wallclock;
    time_t  time_stop;
    time_t *time_start_level;
    time_t *time_stop_level;
    double *IO_size;
    int *   time_total_level;
    int *   flag_use_timer;
    int     flag_results_on;
    int     flag_input_on;
    size_t  RAM_local;
    size_t  max_RAM_local;
#if USE_MPI
    MPI_Info file_info;
#endif
    SID_Comm *COMM_WORLD;
#if !USE_MPI_IO
    int n_groups;
    int My_group;
#endif
    SID_args *args;
    char      My_binary[SID_MAX_FILENAME_LENGTH];
    int *     arg_set;
    int *     arg_alloc;
};

// Default values
#define DEFAULT_MAX_WALLCLOCK_TIME 31536000 // 1 year
#ifdef _MAIN
SID_info SID = {
    NULL, NULL, GBP_FALSE, GBP_FALSE, 0,    0,    GBP_FALSE, SID_MASTER_RANK, 1, NULL, GBP_TRUE, GBP_TRUE, SID_MASTER_RANK, SID_MASTER_RANK, 0, 0,
    0,    NULL, NULL,      NULL,      NULL, NULL, GBP_FALSE, GBP_FALSE,       0, 0};
#else
extern SID_info SID;
#endif

// Datastructure for managing progress counters
typedef struct pcounter_info pcounter_info;
struct pcounter_info {
    size_t n_i;
    size_t i_report_next;
    int    i_report;
    int    n_report;
};

// Structures to define file header info for chunked files
typedef struct chunked_header_info chunked_header_info;
struct chunked_header_info {
    size_t header_size;
    size_t n_items;
    size_t item_size;
    int    n_chunk;
};
typedef struct chunked_subheader_info chunked_subheader_info;
struct chunked_subheader_info {
    size_t n_items;
    int    i_chunk;
};

// Structure to store file info
typedef struct SID_fp SID_fp;
struct SID_fp {
#if USE_MPI
#if USE_MPI_IO
    MPI_File fp;
#else
    FILE *fp;
#endif
#else
    FILE *fp;
#endif
    char                filename_root[256];
    chunked_header_info chunked_header;
    void *              header;
    size_t *            i_x_step_chunk;
    size_t *            i_x_start_chunk;
    size_t *            i_x_last_chunk;
    size_t *            header_offset;
    size_t              last_item;
};

// This is used with SID_fp to perform buffered reads
typedef struct SID_fp_buffer SID_fp_buffer;
struct SID_fp_buffer {
    SID_fp *fp;
    char *  buffer;
    size_t  n_bytes_buffer_max;
    size_t  n_bytes_to_read;
    size_t  n_bytes_unread;
    size_t  n_bytes_buffer_unprocessed;
    size_t  n_bytes_buffer_processed;
    size_t  n_bytes_buffer;
};

// Function declarations
#ifdef __cplusplus
extern "C" {
#endif
void   gbp_va_start(gbp_va_list *vargs);
void   gbp_add_va_arg(gbp_va_list *vargs, size_t size, void *ptr);
void   gbp_fetch_va_arg(gbp_va_list *vargs, size_t size, void *ptr);
void   SID_init(int *argc, char **argv[], SID_args args[], void *mpi_comm_as_void);
void   SID_Comm_init(SID_Comm **comm);
void   SID_Comm_free(SID_Comm **comm);
void   SID_Comm_split(SID_Comm *comm_in, int colour, int key, SID_Comm *comm_out);
int    SID_parse_args(int argc, char *argv[], SID_args args[]);
void   SID_print_syntax(int argc, char *argv[], SID_args args[]);
void   SID_Bcast(void *buffer, int count, SID_Datatype datatype, int source_rank, SID_Comm *comm);
void   SID_Type_size(SID_Datatype type, int *size);
void   SID_Reduce(void *sendbuf, void *recvbuf, int count, SID_Datatype datatype, SID_Op op, int root, SID_Comm *comm);
void   SID_Allreduce(void *sendbuf, void *recvbuf, int count, SID_Datatype datatype, SID_Op op, SID_Comm *comm);
void   SID_Send(void *sendbuf, int sendcount, SID_Datatype sendtype, int dest, int sendtag, SID_Comm *comm);
void   SID_Recv(void *recvbuf, int recvcount, SID_Datatype recvtype, int source, int recvtag, SID_Comm *comm);
void   SID_Sendrecv(void *       sendbuf,
                    int          sendcount,
                    SID_Datatype sendtype,
                    int          dest,
                    int          sendtag,
                    void *       recvbuf,
                    int          recvcount,
                    SID_Datatype recvtype,
                    int          source,
                    int          recvtag,
                    SID_Comm *   comm);
void   SID_test(int val, char *fmt, ...);
void   SID_Barrier(SID_Comm *comm);
void   SID_exit(int status);
int    SID_fopen(const char *filename, const char *mode, SID_fp *fp);
int    SID_fopen_chunked(const char *filename_root, const char *mode, SID_fp *fp, void *header, ...);
size_t fread_verify(void *ptr, size_t size, size_t count, FILE *stream);
size_t SID_fread_all(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
size_t SID_fread_ordered(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
size_t SID_fread(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
size_t SID_fread_chunked(void *buffer, size_t n_x_read_local, size_t i_x_offset_local, SID_fp *fp);
size_t SID_fread_chunked_ordered(void *buffer, size_t n_x_read_local, SID_fp *fp);
size_t SID_fread_chunked_all(void *buffer, size_t n_x_read, SID_fp *fp);

void init_SID_fp_buffer(SID_fp *fp, size_t n_bytes_to_read, size_t n_bytes_buffer_max, SID_fp_buffer **fp_buffer);
void reset_SID_fp_buffer(SID_fp_buffer **fp_buffer);
void free_SID_fp_buffer(SID_fp_buffer **fp_buffer);
void SID_fread_all_buffer(void *rval, size_t dtype_size, size_t n_items, SID_fp_buffer *fp_buffer);

void   SID_fskip_chunked(size_t n_x_skip_local, SID_fp *fp);
void   SID_fseek_chunked(size_t i_x_skip_local, SID_fp *fp);
void   SID_frewind_chunked(SID_fp *fp);
size_t SID_fread(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
void   SID_fseek(SID_fp *fp, size_t size_per_item, size_t n_items, int origin);
void   SID_fseek_end(SID_fp *fp);
void   SID_fskip(size_t size_per_item, size_t n_items, SID_fp *fp);
void   SID_frewind(SID_fp *fp);
void   SID_cat_files(const char *filename_out, int mode, int n_files, ...);
size_t SID_fwrite_all(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
size_t SID_fwrite_ordered(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
size_t SID_fwrite(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
size_t SID_fwrite_chunked(void *buffer, size_t n_x_write_local, size_t i_x_offset_local, SID_fp *fp);
size_t SID_fwrite(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
size_t SID_fwrite_shared(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
int    SID_fclose(SID_fp *fp);
int    SID_fclose_chunked(SID_fp *fp);
int    SID_remove_chunked(char *filename_root);

void seconds2ascii(int n_secs, char *string);
int  check_mode_for_flag(int mode, int flag);

void SID_input(char *fmt, SID_Datatype type, void *input, ...);
void SID_log(const char *fmt, int mode, ...);
void SID_log_set_fp(FILE *fp);
void SID_free(void **ptr);
void SID_log_error(const char *fmt, ...);
void SID_log_warning(const char *fmt, int mode, ...);
void SID_out(char *fmt, int mode, ...);
void SID_throw_error(const char *fmt, int r_val, ...);
void SID_exit_error(const char *fmt, int r_val, ...);
void SID_set_verbosity(int mode, ...);

void SID_profile_stop(int mode);
void SID_profile_start(const char *function_name, int mode, ...);

void *SID_malloc(size_t allocation_size);
void *SID_realloc(void *original_pointer, size_t allocation_size);
void *SID_malloc_array(size_t allocation_size_i, int n_D, ...);
void *SID_calloc(size_t allocation_size);
void  SID_free_array(void **ptr, int n_D, ...);

// These routines manage progress counters
void SID_init_pcounter(pcounter_info *pcounter, size_t n_i, int n_report);
void SID_check_pcounter(pcounter_info *pcounter, size_t i);

#ifdef __cplusplus
}
#endif

#endif
