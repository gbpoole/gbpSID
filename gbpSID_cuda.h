#ifndef SID_CUDA_AWAKE
#define SID_CUDA_AWAKE
__global__ void calc_array_multiply_kernel_int(int *a,int *b);
__global__ void calc_array_multiply_kernel_size_t(size_t *a,size_t *b);
__global__ void calc_array_multiply_kernel_float(float *a,float *b);
__global__ void calc_array_multiply_kernel_double(double *a,double *b);
void calc_array_multiply(void         *data_1,
                         void         *data_2,
                         void         *result,
    	                 size_t        n_data,
                         SID_Datatype  type,
                         int           mode);
#endif
