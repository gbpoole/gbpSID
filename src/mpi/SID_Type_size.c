#include <gbpSID.h>

void SID_Type_size(SID_Datatype type, int *size) {
#if USE_MPI
    MPI_Type_size(type, size);
#else
    if(type == SID_INT)
        (*size) = (int)sizeof(int);
    else if(type == SID_LONG_LONG)
        (*size) = (int)sizeof(long long);
    else if(type == SID_UNSIGNED)
        (*size) = (int)sizeof(unsigned int);
    else if(type == SID_SIZE_T)
        (*size) = (int)sizeof(size_t);
    else if(type == SID_FLOAT)
        (*size) = (int)sizeof(float);
    else if(type == SID_DOUBLE)
        (*size) = (int)sizeof(double);
    else if(type == SID_CHAR)
        (*size) = (int)sizeof(char);
    else
        SID_exit_error("Unsupported SID_Datatype (%d) in SID_Type_size().", SID_ERROR_LOGIC, type);
#endif
}
