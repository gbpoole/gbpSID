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
#define SID_DISABLE_BITFIELD_SWITCH(bitfield, flag) ((bitfield = (bitfield && !flag)))

// Use double precision judiciously?
#if USE_DOUBLE
#define GBPREAL double
#else
#define GBPREAL float
#endif

// This is not meant as an error code per se but
//   signals that the syntax message should
//   be (or has been) printed.  This may just
//   be because the user has requested it.
//   Once syntax is printed, this message
//   should be removed.
#define SID_ERROR_PRINT_SYNTAX SID_TTTP01

#define SID_MAX_VARGS_STREAM_SIZE 128

//! \defgroup core_classes Class definitions
//! \defgroup core_error_codes Error code definitions

// Error codes
//! \addtogroup core_error_codes
//!@{
#define SID_ERROR_NONE 0              //!< No error
#define SID_ERROR_LOGIC SID_TTTP02    //!< Generic error in logic
#define SID_ERROR_IO_OPEN SID_TTTP03  //!< I/O open error
#define SID_ERROR_IO_READ SID_TTTP04  //!< I/O read error
#define SID_ERROR_IO_WRITE SID_TTTP05 //!< I/O write error
#define SID_ERROR_MEMORY SID_TTTP06   //!< Memory allocation error
#define SID_ERROR_SYNTAX SID_TTTP07   //!< Syntax error
//!@}

// Type declarations
typedef struct gbp_va_list gbp_va_list;
typedef struct SID_info    SID_info;

//! \addtogroup core_classes
//!@{
//! Structure specifying a *gbpSID* runtime configuration
struct SID_info {
    SID_Comm *COMM_WORLD;                         //!< The communicator used by SID
    FILE *    fp_log;                             //!< File pointer for log output
    int       My_rank;                            //!< Rank of process in SID_COMM_WORLD
    int       n_proc;                             //!< Number of processes in SID_COMM_WORLD communicator
    int       logging_active;                     //!< Used to control whether a rank can write to the log or not
    int       verbosity;                          //!< Sets the maximum indentation level of the log
    int       level;                              //!< Sets the current indentation level of the log
    int       indent;                             //!< If evluates to True, then next log entry needs to be indented
    int       I_am_Master;                        //!< SID rank identified as the "Master Rank"
    int       I_am_last_rank;                     //!< SID rank which is identified as the "Last Rank"
    int       rank_to_left;                       //!< SID rank identified as being to the "left" of the current rank
    int       rank_to_right;                      //!< SID rank identified as being to the "right" of the current rank
    time_t    time_start;                         //!< Time of application execution start
    time_t    time_stop;                          //!< Time of application execution end
    time_t *  time_start_level;                   //!< Time of start for all active indentation levels
    time_t *  time_stop_level;                    //!< Time of end for all active indentation levels
    double *  IO_size;                            //!< I/O Size for I/O progress counter
    int *     time_total_level;                   //!< Total time spent in this indent level
    int *     flag_use_timer;                     //!< True if timing reporting is to be reported for this indent level
    char *    My_node;                            //!< Name of the rank's node
    char      My_binary[SID_MAX_FILENAME_LENGTH]; //!< Application executable name
#if USE_MPI
    MPI_Info file_info;
#endif
#if !USE_MPI_IO
    int n_groups;
    int My_group;
#endif
};

//! Variadic arguments structure
struct gbp_va_list {
    char stream[SID_MAX_VARGS_STREAM_SIZE]; //!< A c-style string specifying the argument
    int  stream_position;                   //!< Position in the list
};

//! @}

// Default values
#ifdef _MAIN
SID_info SID = {
    NULL, NULL, 0,    1,    GBP_TRUE, 0, 0, GBP_TRUE, GBP_TRUE, GBP_TRUE, SID_MASTER_RANK, SID_MASTER_RANK, 0, 0, NULL, NULL,
    NULL, NULL, NULL, NULL, "",
#if USE_MPI
    0,
#endif
#if !USE_MPI_IO
    1,    1,
#endif
};
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

// Custom variadic arguments functions
void SID_va_start(gbp_va_list *vargs);
void SID_add_va_arg(gbp_va_list *vargs, size_t size, void *ptr);
void SID_fetch_va_arg(gbp_va_list *vargs, size_t size, void *ptr);

#ifdef __cplusplus
}
#endif

#endif
