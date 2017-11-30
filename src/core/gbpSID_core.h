#ifndef GBPSID_CORE_H
#define GBPSID_CORE_H

#include <stdio.h>     // Needed for type FILE
#include <sys/types.h> // Needed for type time_t
#include <gbpSID_file_io.h>
#include <gbpSID_mpi.h>

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
// These are useful for setting
// switches on bit fields
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
#define SID_CHECK_BITFIELD_SWITCH(bitfield, flag) (((bitfield & flag) == flag))
#define SID_DISABLE_BITFIELD_SWITCH(bitfield, flag) ((bitfield=(bitfield && !flag)))

// Use double precision judiciously?
#if USE_DOUBLE
#define GBPREAL double
#else
#define GBPREAL float
#endif

// This is not ment as an error code per se but
//   signals that the syntax message should
//   be (or has been) printed.  This may just
//   be because the user has requested it.
//   Once syntax is printed, this message
//   should be removed.
#define SID_ERROR_PRINT_SYNTAX SID_TTTP01

// Error codes
#define SID_ERROR_NONE 0
#define SID_ERROR_LOGIC SID_TTTP02
#define SID_ERROR_IO_OPEN SID_TTTP03
#define SID_ERROR_IO_READ SID_TTTP04
#define SID_ERROR_IO_WRITE SID_TTTP05
#define SID_ERROR_MEMORY SID_TTTP06
#define SID_ERROR_SYNTAX SID_TTTP07


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
    char My_binary[SID_MAX_FILENAME_LENGTH];
    int *arg_set;
    int *arg_alloc;
};

// Default values
#define DEFAULT_MAX_WALLCLOCK_TIME 31536000 // 1 year
#ifdef _MAIN
SID_info SID = {
    NULL, NULL, GBP_FALSE, GBP_FALSE, 0,    0,    GBP_FALSE, SID_MASTER_RANK, 1, NULL, GBP_TRUE, GBP_TRUE, SID_MASTER_RANK, SID_MASTER_RANK, 0, 0,
    0,    NULL, NULL,      NULL,      NULL, NULL, GBP_FALSE, GBP_FALSE,       0, 0,
#if USE_MPI
    0,
#endif
    NULL,
#if !USE_MPI_IO
    1,    1,
#endif
    "",   NULL, NULL};
#else
extern SID_info SID;
#endif

// Function declarations
#ifdef __cplusplus
extern "C" {
#endif

void SID_Init(int *argc, char **argv[], void *mpi_comm_as_void);
void SID_Finalize();
void SID_exit_error(const char *fmt, int r_val, ...);
void SID_seconds2ascii(int n_secs, char *string);

void SID_va_start(gbp_va_list *vargs);
void SID_add_va_arg(gbp_va_list *vargs, size_t size, void *ptr);
void SID_fetch_va_arg(gbp_va_list *vargs, size_t size, void *ptr);

#ifdef __cplusplus
}
#endif

#endif
