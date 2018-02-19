#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gbpSID.h>

void *SID_calloc(size_t allocation_size) {
    void *r_val;
    if(allocation_size > 0) {
        r_val = calloc(allocation_size, 1);
        if(r_val == NULL)
            SID_exit_error("Could not allocate %lld bytes of RAM!", SID_ERROR_MEMORY, allocation_size);
    } else
        r_val = NULL;
    return (r_val);
}
