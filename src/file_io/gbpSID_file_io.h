#ifndef GBPSID_FILE_IO_H
#define GBPSID_FILE_IO_H

// Some preferred sizes
#define SID_IO_BUFFER_SIZE 4096
#define SID_MAX_FILENAME_LENGTH 256
#define SID_N_IO_FILES_MAX 64

#define SID_PROFILE_DEFAULT SID_TTTP01
#define SID_PROFILE_MPIENABLED SID_TTTP02
#define SID_PROFILE_NOTMPIENABLED SID_TTTP03

#define SID_CAT_DEFAULT SID_DEFAULT_MODE
#define SID_CAT_CLEAN SID_TTTP01

#if USE_MPI_IO
#define SID_SEEK_SET MPI_SEEK_SET
#define SID_SEEK_CUR MPI_SEEK_CUR
#else
#define SID_SEEK_SET SEEK_SET
#define SID_SEEK_CUR SEEK_CUR
#endif

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

int    SID_fopen(const char *filename, const char *mode, SID_fp *fp);
int    SID_fclose(SID_fp *fp);
size_t SID_fread(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
size_t SID_fwrite(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
void   SID_frewind(SID_fp *fp);
void   SID_fseek(SID_fp *fp, size_t size_per_item, size_t n_items, int origin);
void   SID_fskip(size_t size_per_item, size_t n_items, SID_fp *fp);
void   SID_fseek_end(SID_fp *fp);
size_t SID_fread_all(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
size_t SID_fwrite_all(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
void   SID_fread_all_buffer(void *rval, size_t dtype_size, size_t n_items, SID_fp_buffer *fp_buffer);
size_t SID_fread_ordered(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
size_t SID_fwrite_ordered(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
size_t SID_fwrite_shared(void *buffer, size_t size_per_item, size_t n_items, SID_fp *fp);
int    SID_fopen_chunked(const char *filename_root, const char *mode, SID_fp *fp, void *header, ...);
int    SID_fclose_chunked(SID_fp *fp);
size_t SID_fread_chunked(void *buffer, size_t n_x_read_local, size_t i_x_offset_local, SID_fp *fp);
size_t SID_fread_chunked_all(void *buffer, size_t n_x_read, SID_fp *fp);
size_t SID_fread_chunked_ordered(void *buffer, size_t n_x_read_local, SID_fp *fp);
void   SID_frewind_chunked(SID_fp *fp);
void   SID_fseek_chunked(size_t i_x_skip_local, SID_fp *fp);
void   SID_fskip_chunked(size_t n_x_skip_local, SID_fp *fp);
size_t SID_fwrite_chunked(void *buffer, size_t n_x_write_local, size_t i_x_offset_local, SID_fp *fp);
int    SID_remove_chunked(char *filename_root);
void   SID_cat_files(const char *filename_out, int mode, int n_files, ...);
void   SID_init_fp_buffer(SID_fp *fp, size_t n_bytes_to_read, size_t n_bytes_buffer_max, SID_fp_buffer **fp_buffer);
void   SID_reset_fp_buffer(SID_fp_buffer **fp_buffer);
void   SID_free_fp_buffer(SID_fp_buffer **fp_buffer);
size_t SID_fread_verify(void *ptr, size_t size, size_t count, FILE *stream);

#ifdef __cplusplus
}
#endif

#endif
