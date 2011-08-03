#include <stdio.h>     // Needed for type FILE
#include <sys/types.h> // Needed for type time_t
#include <stdarg.h>
#include <gbpCommon.h>

#if USE_MPI
#ifndef MPI_DEFINED
#include <mpi.h>
#else
#define MPI_DEFINED 1
#endif
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

#ifndef SID_AWAKE
#define SID_AWAKE

#define MASTER_RANK    0
#define DEFAULT_MODE   0

#define N_IO_FILES_MAX 64

#define SID_ERROR_HEADER      "ERROR:"
#define SID_WARNING_HEADER    "WARNING:"
#define SID_LOG_INDENT_STRING "   "

#define SID_FARG (void **)&

#define SID_LOG_MAX_LEVELS 30
#define SID_LOG_OPEN       1
#define SID_LOG_CLOSE      2
#define SID_LOG_TIMER      4
#define SID_LOG_CONTINUE   8
#define SID_LOG_SINGLE     16
#define SID_LOG_IO_RATE    32
#define SID_LOG_COMMENT    64
#define SID_LOG_NOPRINT    128
#define SID_LOG_ALLRANKS   256
#define SID_LOG_CHECKPOINT 512

#define SID_SET_VERBOSITY_DEFAULT  0
#define SID_SET_VERBOSITY_ABSOLUTE 1
#define SID_SET_VERBOSITY_RELATIVE 2

#define SID_INFO           1
#define SID_INFO_RESULT    2
#define SID_INFO_MASTER    4

#define SID_PROFILE_DEFAULT       1
#define SID_PROFILE_MPIENABLED    2
#define SID_PROFILE_NOTMPIENABLED 4

#define SID_CAT_DEFAULT 0
#define SID_CAT_CLEAN   2

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
#define SID_IN_PLACE    MPI_IN_PLACE
#define SID_COMM_NULL   MPI_COMM_NULL
#define SID_GROUP_EMPTY MPI_GROUP_EMPTY
#define SID_Datatype    MPI_Datatype
#define SID_CHAR        MPI_CHAR
#define SID_INT         MPI_INT
#define SID_LONG_LONG   MPI_LONG_LONG
#define SID_SIZE_T      MPI_LONG_LONG
#define SID_FLOAT       MPI_FLOAT
#define SID_DOUBLE      MPI_DOUBLE
#define SID_BYTE        MPI_BYTE
#define SID_Op          MPI_Op
#define SID_SUM         MPI_SUM
#define SID_MAX         MPI_MAX
#define SID_MIN         MPI_MIN
#else
#define SID_IN_PLACE    NULL
#define SID_COMM_NULL   NULL
#define SID_GROUP_EMPTY NULL
#define SID_Datatype    int
#define SID_DOUBLE      0
#define SID_LONG_LONG   1
#define SID_FLOAT       2
#define SID_INT         3
#define SID_SIZE_T      6
#define SID_BYTE        7
#define SID_CHAR        8
#define SID_Op          int
#define SID_SUM         1
#define SID_MAX         2
#define SID_MIN         3
#endif 
#if USE_DOUBLE
  #define SID_REAL SID_DOUBLE
#else
  #define SID_REAL SID_FLOAT
#endif

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
SID_info SID={NULL,NULL,FALSE,0,0,FALSE,MASTER_RANK,1,NULL,TRUE,TRUE,MASTER_RANK,MASTER_RANK,0,0,NULL,NULL,NULL,NULL,NULL,FALSE,FALSE,0,0};
#else
extern SID_info SID;
#endif 

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

// Function declarations 
void SID_init(int *argc,char **argv[],SID_args args[]);
void SID_Comm_init(SID_Comm **comm);
void SID_Comm_free(SID_Comm **comm);
void SID_Comm_split(SID_Comm *comm_in,int colour,int key,SID_Comm *comm_out);
int  SID_parse_args(int argc,char *argv[],SID_args args[]);
void SID_print_syntax(int argc,char *argv[],SID_args args[]);
void SID_Bcast(void *buffer,int data_size,int source_rank,SID_Comm *comm);
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
int SID_fopen(char   *filename,
              char   *mode,
              SID_fp *fp);
int SID_fopen_chunked(char   *filename_root,
                      char   *mode,
                      SID_fp *fp,
                      void   *header, ...);
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
void SID_cat_files(char *filename_out,
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
void SID_log(char *fmt, int mode, ...);
void SID_log_error(char *fmt, ...);
void SID_log_warning(char *fmt, int mode, ...);
void SID_out(char *fmt, int mode, ...);
void SID_trap_error(char *fmt, int r_val, ...);
void SID_set_verbosity(int mode, ...);

void SID_profile_stop(int mode);
void SID_profile_start(char *function_name, int mode, ...);

void *SID_malloc(size_t allocation_size);
void *SID_calloc(size_t allocation_size);
void SID_free(void **ptr);

#define CALC_MODE_DEFAULT       DEFAULT_MODE
#define CALC_MODE_RETURN_DOUBLE 1
#define CALC_MODE_ABS           2

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
#endif
