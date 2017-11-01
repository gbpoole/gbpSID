#include <gbpSID.h>

size_t fread_verify(void *ptr, size_t size, size_t count, FILE *stream) {
    size_t n_return;
    if((n_return = fread(ptr, size, count, stream)) != count)
        SID_exit_error("Failed to read %lld %lld-byte sized items (only %lld returned).", SID_ERROR_IO_READ, count,
                       size, n_return);
    return (n_return);
}
