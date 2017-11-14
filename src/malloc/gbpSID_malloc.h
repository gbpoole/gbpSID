#ifndef GBPSID_MALLOC_H
#define GBPSID_MALLOC_H

// This construct occurs often.  It's
// particularly common with use of
// SID_free() ... hence the name:
// SID_FARG -> "SID_free argument"
#define SID_FARG (void **)&

// Function declarations
#ifdef __cplusplus
extern "C" {
#endif

void *SID_malloc(size_t allocation_size);
void *SID_calloc(size_t allocation_size);
void *SID_realloc(void *original_pointer, size_t allocation_size);
void  SID_free(void **ptr);

#ifdef __cplusplus
}
#endif

#endif
