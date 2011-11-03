#include <gbpCommon.h>
#include <gbpSID.h>

__global__ void calc_array_multiply_kernel_int(int *a,int *b){
   a[threadIdx.x]*=b[threadIdx.x];
}

__global__ void calc_array_multiply_kernel_size_t(size_t *a,size_t *b){
   a[threadIdx.x]*=b[threadIdx.x];
}
__global__ void calc_array_multiply_kernel_float(float *a,float *b){
   a[threadIdx.x]*=b[threadIdx.x];
}
/*
__global__ void calc_array_multiply_kernel_double(double *a,double *b){
   a[threadIdx.x]*=b[threadIdx.x];
}
*/
void calc_array_multiply(void         *data_1,
                         void         *data_2,
                         void         *result,
    	                 size_t        n_data,
                         SID_Datatype  type,
                         int           mode){
  int datatype_size;

  // Don't do anything if there's no data
  if(n_data<1){
    if(type==SID_DOUBLE || check_mode_for_flag(mode,CALC_MODE_RETURN_DOUBLE))
      ((double *)result)[0]=0.;
    else if(type==SID_FLOAT)
      ((float  *)result)[0]=0.;
    else if(type==SID_INT)
      ((int    *)result)[0]=0;
    else if(type==SID_SIZE_T)
      ((size_t *)result)[0]=0;
    else
      SID_trap_error("Unknown variable type in calc_array_multiply",ERROR_LOGIC);
    return;
  }

  // Set size of datatype
  SID_Type_size(type,&datatype_size);

  // Define grid and block size
  int numBlocks          = 1;
  int numThreadsPerBlock = n_data;

  // Create data buffer on Device
  void   *data_1_device;
  void   *data_2_device;
  size_t  memSize = numBlocks*numThreadsPerBlock*(size_t)datatype_size;
  cudaMalloc(SID_FARG data_1_device,memSize);
  cudaMalloc(SID_FARG data_2_device,memSize);

  // Load data onto device
  cudaMemcpy(data_1_device,data_1,memSize,cudaMemcpyHostToDevice);
  cudaMemcpy(data_2_device,data_2,memSize,cudaMemcpyHostToDevice);

  //dim3 dimGrid(  );
  //dim3 dimBlock(  );

  if(type==SID_FLOAT)
     calc_array_multiply_kernel_float<<<numBlocks,numThreadsPerBlock>>>((float *)data_1_device,(float *)data_2_device);
/*
  else if(type==SID_DOUBLE)
     calc_array_multiply_kernel_double<<<numBlocks,numThreadsPerBlock>>>((double *)data_1_device,(double *)data_2_device);
*/
  else if(type==SID_INT)
     calc_array_multiply_kernel_int<<<numBlocks,numThreadsPerBlock>>>((int *)data_1_device,(int *)data_2_device);
  else if(type==SID_SIZE_T)
     calc_array_multiply_kernel_size_t<<<numBlocks,numThreadsPerBlock>>>((size_t *)data_1_device,(size_t *)data_2_device);
  else
    SID_trap_error("Unknown variable type in calc_array_multiply",ERROR_LOGIC);

  // Block until the Device is done
  cudaThreadSynchronize();

  // Copy the result back
  if(result==NULL)
    cudaMemcpy(data_1,data_1_device,memSize,cudaMemcpyDeviceToHost);
  else
    cudaMemcpy(result,data_1_device,memSize,cudaMemcpyDeviceToHost);

  // Free device buffer
  cudaFree(data_1_device);
  cudaFree(data_2_device);

  return;
}

