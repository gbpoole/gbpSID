#ifndef SID_H
#define SID_H
#include <stdio.h>     // Needed for type FILE
#include <sys/types.h> // Needed for type time_t
#include <stdarg.h>

#define DEFAULT_MAX_WALLCLOCK_TIME 172800

#if USE_MPI
  #ifndef MPI_AWAKE
    #include <mpi.h>
  #else
    #define MPI_AWAKE 
  #endif
#endif 

#ifndef _FILE_H
#   define _FILE_H
#   if _FILE_C
#      define _FILE_C_CLASS
#   else
#      define _FILE_C_CLASS extern
#   endif
_FILE_C_CLASS int a;
_FILE_C_CLASS int b;
#endif

// TTPXX=Two-to-the-power-XX
#define DEFAULT_MODE 0
#define TTTP00 1
#define TTTP01 2
#define TTTP02 4
#define TTTP03 8
#define TTTP04 16
#define TTTP05 32
#define TTTP06 64
#define TTTP07 128
#define TTTP08 256
#define TTTP09 512
#define TTTP10 1024
#define TTTP11 2048
#define TTTP12 4096
#define TTTP13 8192
#define TTTP14 16384
#define TTTP15 32768
#define TTTP16 65536
#define TTTP17 131072
#define TTTP18 262144
#define TTTP19 524288
#define TTTP20 1048576
#define TTTP21 2097152
#define TTTP22 4194304
#define TTTP23 8388608
#define TTTP24 16777216
#define TTTP25 33554432
#define TTTP26 67108864
#define TTTP27 134217728
#define TTTP28 268435456
#define TTTP29 536870912
#define TTTP30 1073741824
#define TTTP31 2147483648
#define TTTP32 4294967296

#define IO_BUFFER_SIZE      4096
#define MAX_FILENAME_LENGTH 256

// Storage sizes
#define SIZE_OF_KILOBYTE  1024
#define SIZE_OF_MEGABYTE  1048576
#define SIZE_OF_GIGIBYTE  1073741824

#define TRUE  1
#define FALSE 0
#define MIN(A,B)  ((A) < (B) ?  (A) : (B))
#define MAX(A,B)  ((A) > (B) ?  (A) : (B))
#define IABS(A)   ((A) <  0  ? -(A) : (A))

// Compile flags to control large variables
#if USE_DOUBLE
#define GBPREAL double
#else
#define GBPREAL float
#endif

#define big_int long long
#define id_int  size_t

// MPI
#if USE_MPI
  #ifndef MPI_DEFINED
    #include <mpi.h>
  #else
    #define MPI_DEFINED 1
  #endif
  #if USE_DOUBLE
    #define MPI_MY_REAL MPI_DOUBLE
  #else
    #define MPI_MY_REAL MPI_FLOAT
  #endif
  #define MPI_SIZE_T MPI_LONG_LONG
#endif

// Error messages
#define ERROR_NONE      0
#define ERROR_SYNTAX    TTTP01
#define ERROR_LOGIC     TTTP02
#define ERROR_IO_OPEN   TTTP03
#define ERROR_IO_READ   TTTP04
#define ERROR_IO_WRITE  TTTP05
#define ERROR_MEMORY    TTTP06

#define MASTER_RANK    0

#define N_IO_FILES_MAX 64

#define SID_ERROR_HEADER      "ERROR:"
#define SID_WARNING_HEADER    "WARNING:"
#define SID_LOG_INDENT_STRING "   "

#define SID_WARNING_DEFAULT 0

#define SID_FARG (void **)&

#define SID_LOG_MAX_LEVELS   30
#define SID_LOG_OPEN         TTTP00
#define SID_LOG_CLOSE        TTTP01
#define SID_LOG_TIMER        TTTP02
#define SID_LOG_CONTINUE     TTTP03
#define SID_LOG_IO_RATE      TTTP04
#define SID_LOG_COMMENT      TTTP05
#define SID_LOG_NOPRINT      TTTP06
#define SID_LOG_ALLRANKS     TTTP07
#define SID_LOG_CHECKPOINT   TTTP08
#define SID_LOG_SILENT_CLOSE SID_LOG_CLOSE|SID_LOG_NOPRINT

#define SID_SET_VERBOSITY_DEFAULT  DEFAULT_MODE
#define SID_SET_VERBOSITY_ABSOLUTE TTTP00
#define SID_SET_VERBOSITY_RELATIVE TTTP01

#define SID_INFO_RESULT    TTTP01
#define SID_INFO_MASTER    TTTP02

#define SID_PROFILE_DEFAULT       TTTP01
#define SID_PROFILE_MPIENABLED    TTTP02
#define SID_PROFILE_NOTMPIENABLED TTTP03

#define SID_CAT_DEFAULT DEFAULT_MODE
#define SID_CAT_CLEAN   TTTP01

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
#define SID_COMM_WORLD  (SID.COMM_WORLD->comm)
#define SID_IN_PLACE    MPI_IN_PLACE
#define SID_COMM_NULL   MPI_COMM_NULL
#define SID_GROUP_EMPTY MPI_GROUP_EMPTY
#define SID_Datatype    MPI_Datatype
#define SID_CHAR        MPI_CHAR
#define SID_INT         MPI_INT
#define SID_UNSIGNED    MPI_UNSIGNED
#define SID_LONG_LONG   MPI_LONG_LONG
#define SID_LONG        MPI_LONG
#define SID_SIZE_T      MPI_LONG_LONG
#define SID_FLOAT       MPI_FLOAT
#define SID_DOUBLE      MPI_DOUBLE
#define SID_BYTE        MPI_BYTE
#define SID_Op          MPI_Op
#define SID_SUM         MPI_SUM
#define SID_MAX         MPI_MAX
#define SID_MIN         MPI_MIN
#else
#define SID_COMM_WORLD  NULL
#define SID_IN_PLACE    NULL
#define SID_COMM_NULL   NULL
#define SID_GROUP_EMPTY NULL
#define SID_Datatype    int
#define SID_LONG_LONG   TTTP01
#define SID_LONG        TTTP02
#define SID_FLOAT       TTTP03
#define SID_DOUBLE      TTTP04
#define SID_INT         TTTP05
#define SID_UNSIGNED    TTTP06
#define SID_SIZE_T      TTTP07
#define SID_BYTE        TTTP08
#define SID_CHAR        TTTP09
#define SID_Op          int
#define SID_SUM         TTTP01
#define SID_MAX         TTTP02
#define SID_MIN         TTTP03
#endif 
#if USE_DOUBLE
  #define SID_REAL SID_DOUBLE
#else
  #define SID_REAL SID_FLOAT
#endif

#define CALC_MODE_DEFAULT       DEFAULT_MODE
#define CALC_MODE_RETURN_DOUBLE TTTP00
#define CALC_MODE_ABS           TTTP01

#define CALC_STAT_DEFAULT       DEFAULT_MODE
#define CALC_STAT_RETURN_DOUBLE TTTP00
#define CALC_STAT_GLOBAL        TTTP01
#define CALC_STAT_SUM           TTTP02
#define CALC_STAT_MIN           TTTP03
#define CALC_STAT_MAX           TTTP04
#define CALC_STAT_MEAN          TTTP05
#define CALC_STAT_MEDIAN        TTTP06
#define CALC_STAT_STDDEV        TTTP07

// Variable limits
#include <limits.h>
#include <float.h>
#define SID_MAX_DOUBLE DBL_MAX
#define SID_MIN_DOUBLE DBL_MIN
#define SID_MAX_FLOAT  FLT_MAX
#define SID_MIN_FLOAT  FLT_MIN
#define SID_MAX_INT    INT_MAX
#define SID_MIN_INT    INT_MIN

#define LOG_ZERO  -1000.0

#define FIVE_THIRDS    1.6666667
#define THREE_HALVES   1.5
#define TWO_THIRDS     0.6666667
#define ONE_THIRD      0.3333333
#define ONE_HALF       0.4999999
#define ONE_QUARTER    0.25

#define FOUR_THIRDS_PI     4.1887902
#define PI                 3.1415926
#define HALF_PI            1.5707963
#define THREE_QUARTERS_PI  2.3561944
#define TWO_PI             6.2831853
#define FOUR_PI           12.5663706
#define LN_OF_10           2.30288509
#define LOG10_OF_E         0.43429448
#define SQRT_OF_2          1.41421356

#define C_VACUUM       2.99792458E8   /* in m/s          */
#define G_NEWTON       6.67428E-11    /* in m^3/(kg*s^2) */
#define M_SOL          1.98892E30     /* in kilograms    */
#define M_HYDROGEN     1.6735E-27     /* in kilograms    */
#define M_PROTON       1.6726216E-27  /* in kilograms    */
#define M_ELECTRON     9.10938188E-31 /* in kilograms    */
#define SIGMA_THOMPSON 6.65245854E-29 /* in m^2          */
#define M_PER_PC       3.08568025E16  /* in meters       */
#define M_PER_KPC      3.08568025E19  /* in meters       */
#define M_PER_MPC      3.08568025E22  /* in meters       */
#ifndef CM_PER_MPC
#define CM_PER_MPC  3.08568025E24  /* in cm           */
#endif
#define S_PER_YEAR     3.155693e+07
#define S_PER_GYR      3.155693e+16   /* in seconds      */
#define S_PER_MYR      3.155693e+13   /* in seconds      */
#define S_PER_YR       3.155693e+7    /* in seconds      */
#define K_BOLTZMANN    1.3806503E-23  /* in J per K      */
#define H_PLANK        6.62606876E-34 /* in J*s          */
#define LOG_M_P      -57.075256       /* in log(M_sol)   */
#define T_CMB          2.728          /* in Kelvin       */

#define DEG_PER_RAD   5.72957795E+1
#define DEG_PER_AMIN  3.43774677E+3
#define DEG_PER_ASEC  4.84811331E-6
#define RAD_PER_DEG   1.74532925E-2
#define RAD_PER_AMIN  2.90888209E-4
#define RAD_PER_ASEC  4.84811331E-6
#define ASEC_PER_RAD  2.06265806E+5
#define ASEC_PER_DEG  3.60000000E+3

#define K_PER_KEV  1.1604447e7
#define ERGS_PER_KEV   1.60217733000e-9
#define ERGS_PER_J     1e7
#define J_PER_KEV      1.60217646E-16
#define SI_TO_MJY      1E29

#define MU_MMW         0.597  /* Mean molecular weight      */
#define XI             1.0878 /* Xi=1+Y/(4*(1-Y)) w/ Y=0.26 */
#define XE             1.1756 /* Xe=1+Y/(2*(1-Y)) w/ Y=0.26 */
#define NE_PER_RHOGAS  XE/(MU_MMW*M_PROTON*(XI+XE))
#define NH_PER_RHOGAS  1.0/(MU_MMW*M_PROTON*(XI+XE))
#define MU_E_MMW       MU_MMW*(XI+XE)/XE
#define GAMMA_ICM      FIVE_THIRDS
#define MSOL_KPCQU_PER_KG_MQU M_PER_KPC*M_PER_KPC*M_PER_KPC/M_SOL

// Structures for parsing the command line
typedef void** SID_args;
typedef struct SID_arg SID_arg;
struct SID_arg {
  char   *key;
  char   *var_name;
  char   *description;
  int     type;
  int     flag_required;
  void   *val;
};

// Custom variadic arguments functions
#define MAX_GBP_VA_ARGS_STREAM_SIZE 128
typedef struct gbp_va_list gbp_va_list;
struct gbp_va_list{
   char  stream[MAX_GBP_VA_ARGS_STREAM_SIZE];
   int   stream_position;
};

typedef struct SID_Comm SID_Comm;
struct SID_Comm{
  #if USE_MPI
    MPI_Comm   comm;
    MPI_Group  group;
  #else
    char      *comm;
    char      *group;
  #endif
  int        n_proc;
  int        My_rank;
};

// Structure to store SID info 
typedef struct SID_info SID_info;
struct SID_info{
  FILE     *fp_log;
  FILE     *fp_in;
  int       error_state;
  int       awake;
  int       verbosity;
  int       level;
  int       indent;
  int       My_rank;
  int       n_proc;
  char     *My_node;
  int       I_am_Master;
  int       I_am_last_rank;
  int       rank_to_left;
  int       rank_to_right;
  time_t    time_start;
  time_t    max_wallclock;
  time_t    time_stop;
  time_t   *time_start_level;
  time_t   *time_stop_level;
  double   *IO_size;
  int      *time_total_level;
  int      *flag_use_timer;
  int       flag_results_on;
  int       flag_input_on;
  size_t    RAM_local;
  size_t    max_RAM_local;
#if USE_MPI
  MPI_Info  file_info;
#endif
  SID_Comm *COMM_WORLD;
#if !USE_MPI_IO
  int       n_groups;
  int       My_group;
#endif
  SID_args *args;
  char      My_binary[MAX_FILENAME_LENGTH];
  int      *arg_set;
  int      *arg_alloc;
};

// Default values
#ifdef _MAIN
SID_info SID={NULL,NULL,FALSE,FALSE,0,0,FALSE,MASTER_RANK,1,NULL,TRUE,TRUE,MASTER_RANK,MASTER_RANK,0,0,0,NULL,NULL,NULL,NULL,NULL,FALSE,FALSE,0,0};
#else
extern SID_info SID;
#endif 

// Datastructure for managing progress counters
typedef struct pcounter_info pcounter_info;
struct pcounter_info{
  size_t n_i;
  size_t i_report_next;
  int    i_report;
  int    n_report;
};

// Structures to define file header info for chunked files
typedef struct chunked_header_info chunked_header_info;
struct chunked_header_info{
  size_t header_size;
  size_t n_items;
  size_t item_size;
  int    n_chunk;
};
typedef struct chunked_subheader_info chunked_subheader_info;
struct chunked_subheader_info{
  size_t n_items;
  int    i_chunk;
};

// Structure to store file info 
typedef struct SID_fp SID_fp;
struct SID_fp{
#if USE_MPI
#if USE_MPI_IO
  MPI_File fp;
#else
  FILE    *fp;
#endif
#else
  FILE    *fp;
#endif
  char                 filename_root[256];
  chunked_header_info  chunked_header;
  void                *header;
  size_t              *i_x_step_chunk;
  size_t              *i_x_start_chunk;
  size_t              *i_x_last_chunk;
  size_t              *header_offset;
  size_t               last_item;
};

// This is used with SID_fp to perform buffered reads
typedef struct SID_fp_buffer SID_fp_buffer;
struct SID_fp_buffer{
   SID_fp *fp;
   char   *buffer;
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
void gbp_va_start    (gbp_va_list *vargs);
void gbp_add_va_arg  (gbp_va_list *vargs,size_t size,void *ptr);
void gbp_fetch_va_arg(gbp_va_list *vargs,size_t size,void *ptr);
void SID_init(int *argc,char **argv[],SID_args args[], void *mpi_comm_as_void);
void SID_Comm_init(SID_Comm **comm);
void SID_Comm_free(SID_Comm **comm);
void SID_Comm_split(SID_Comm *comm_in,int colour,int key,SID_Comm *comm_out);
int  SID_parse_args(int argc,char *argv[],SID_args args[]);
void SID_print_syntax(int argc,char *argv[],SID_args args[]);
void SID_Bcast(void *buffer, int count, SID_Datatype datatype, SID_Comm *comm, int source_rank);
void SID_Type_size(SID_Datatype type,int *size);
void SID_Reduce(void *sendbuf,void *recvbuf,int count,SID_Datatype datatype,SID_Op op,int root,SID_Comm *comm);
void SID_Allreduce(void *sendbuf,void *recvbuf,int count,SID_Datatype datatype,SID_Op op,SID_Comm *comm);
void SID_Send(void         *sendbuf,
              int           sendcount,
              SID_Datatype  sendtype,
              int           dest,
              int           sendtag,
              SID_Comm     *comm);
void SID_Recv(void         *recvbuf,
              int           recvcount,
              SID_Datatype  recvtype,
              int           source,
              int           recvtag,
              SID_Comm     *comm);
void SID_Sendrecv(void         *sendbuf,
                  int           sendcount,
                  SID_Datatype  sendtype,
                  int           dest,
                  int           sendtag,
                  void         *recvbuf,
                  int           recvcount,
                  SID_Datatype  recvtype,
                  int           source,
                  int           recvtag,
                  SID_Comm     *comm);
void SID_test(int val,char *fmt,...);
void SID_barrier();
void SID_Barrier(SID_Comm *comm);
void SID_demote();
void SID_premote();
void SID_say(char *fmt, ...);
void SID_exit(int status);
int SID_fopen(const char   *filename,
              const char   *mode,
              SID_fp *fp);
int SID_fopen_chunked(const char   *filename_root,
                      const char   *mode,
                      SID_fp *fp,
                      void   *header, ...);
size_t fread_verify(void *ptr, size_t size, size_t count, FILE *stream);
size_t SID_fread_all(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp);
size_t SID_fread_ordered(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp);
size_t SID_fread(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp);
size_t SID_fread_chunked(void   *buffer,
                         size_t  n_x_read_local,
                         size_t  i_x_offset_local,
                         SID_fp *fp);
size_t SID_fread_chunked_ordered(void   *buffer,
                                 size_t  n_x_read_local,
                                 SID_fp *fp);
size_t SID_fread_chunked_all(void   *buffer,
                             size_t  n_x_read,
                             SID_fp *fp);

void init_SID_fp_buffer(SID_fp *fp,size_t n_bytes_to_read,size_t n_bytes_buffer_max,SID_fp_buffer **fp_buffer);
void reset_SID_fp_buffer(SID_fp_buffer **fp_buffer);
void free_SID_fp_buffer(SID_fp_buffer **fp_buffer);
void SID_fread_all_buffer(void *rval,size_t dtype_size,size_t n_items,SID_fp_buffer *fp_buffer);

void SID_fskip_chunked(size_t  n_x_skip_local,
                       SID_fp *fp);
void SID_fseek_chunked(size_t  i_x_skip_local,
                       SID_fp *fp);
void SID_frewind_chunked(SID_fp *fp);
size_t SID_fread(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp);
void SID_fseek(SID_fp *fp,
               size_t  size_per_item,
               size_t  n_items,
               int     origin);
void SID_fseek_end(SID_fp *fp);
void SID_fskip(size_t size_per_item,
               size_t n_items,
               SID_fp *fp);
void SID_frewind(SID_fp *fp);
void SID_cat_files(const char *filename_out,
                   int   mode,
                   int   n_files, ...);
size_t SID_fwrite_all(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp);
size_t SID_fwrite_ordered(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp);
size_t SID_fwrite(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp);
size_t SID_fwrite_chunked(void   *buffer,
                          size_t  n_x_write_local,
                          size_t  i_x_offset_local,
                          SID_fp *fp);
size_t SID_fwrite(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp);
size_t SID_fwrite_shared(void *buffer,size_t size_per_item, size_t n_items,SID_fp *fp);
int SID_fclose(SID_fp *fp);
int SID_fclose_chunked(SID_fp *fp);
int SID_remove_chunked(char *filename_root);

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
void SID_trap_error(const char *fmt, int r_val, ...);
void SID_set_verbosity(int mode, ...);

void SID_profile_stop(int mode);
void SID_profile_start(const char *function_name, int mode, ...);

void *SID_malloc(size_t allocation_size);
void *SID_realloc(void *original_pointer,size_t allocation_size);
void *SID_malloc_array(size_t allocation_size_i,int n_D,...);
void *SID_calloc(size_t allocation_size);
void SID_free_array(void **ptr,int n_D,...);

void calc_max(void   *data,
              void   *result,
	      size_t  n_data,
              SID_Datatype type,
              int          mode);
void calc_max_global(void   *data_local,
                     void   *result,
 	    	     size_t  n_data_local,
                     SID_Datatype type,
                     int          mode,
                     SID_Comm    *comm);
void calc_mean(void  *data,
               void  *result,
	       size_t n_data,
               SID_Datatype type,
               int          mode);
void calc_mean_global(void   *data_local,
                      void   *result,
 		      size_t  n_data_local,
                      SID_Datatype type,
                      int          mode,
                      SID_Comm    *comm);
void calc_min(void   *data,
              void   *result,
 	      size_t  n_data,
              SID_Datatype type,
              int          mode);
void calc_min_global(void   *data_local,
                     void   *result,
 	    	     size_t  n_data_local,
                     SID_Datatype type,
                     int          mode,
                     SID_Comm    *comm);
void calc_stddev(void   *data,
                 void   *result,
 		 size_t  n_data,
                 SID_Datatype type,
                 int          mode);
void calc_stddev_global(void   *data_local,
                        void   *result,
 		        size_t  n_data_local,
                        SID_Datatype type,
                        int          mode,
                        SID_Comm    *comm);
void calc_sum(void   *data,
              void   *result,
 	      size_t  n_data,
              SID_Datatype type,
              int          mode);
void calc_sum_global(void   *data_local,
                     void   *result,
 	    	     size_t  n_data_local,
                     SID_Datatype type,
                     int          mode,
                     SID_Comm    *comm);

// These routines manage progress counters
void SID_init_pcounter(pcounter_info *pcounter,
                       size_t         n_i,
                       int            n_report);
void SID_check_pcounter(pcounter_info *pcounter,
                        size_t         i);

#ifdef __cplusplus
}
#endif
#endif
