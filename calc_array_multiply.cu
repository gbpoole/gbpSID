#include <gbpCommon.h>
#include <gbpSID.h>

__global__ void calc_array_multiply_kernel_int(int *a,int *b){
   int index=blockIdx.x*blockDim.x+threadIdx.x;
   a[index]*=b[index];
}
__global__ void calc_array_multiply_kernel_float(float *a,float *b){
   int index=blockIdx.x*blockDim.x+threadIdx.x;
   a[index]*=b[index];
}

void calc_array_multiply(void         *data_1,
                         void         *data_2,
                         void         *result,
    	                 size_t        n_data,
                         SID_Datatype  type,
                         int           mode){

  // Don't do anything if there's no data
  if(n_data<1)
    return;

  // Set size of datatype
  int datatype_size;
  SID_Type_size(type,&datatype_size);

  // Define grid and block size
  int numThreadsPerBlock = SID_CUDA_IDEAL_THREADS_PER_BLOCK;
  int numBlocks          = n_data/numThreadsPerBlock;
  if((n_data%numThreadsPerBlock)!=0) numBlocks++;
  //dim3 dimGrid(  );
  //dim3 dimBlock(  );

  // Create data buffer on Device
  void   *data_1_device;
  void   *data_2_device;
  size_t  memSize = n_data*(size_t)datatype_size;
  cudaMalloc(SID_FARG data_1_device,memSize);
  cudaMalloc(SID_FARG data_2_device,memSize);

  // Load data onto device
  cudaMemcpy(data_1_device,data_1,memSize,cudaMemcpyHostToDevice);
  cudaMemcpy(data_2_device,data_2,memSize,cudaMemcpyHostToDevice);

  if(type==SID_FLOAT)
     calc_array_multiply_kernel_float<<<numBlocks,numThreadsPerBlock>>>((float *)data_1_device,(float *)data_2_device);
  else if(type==SID_INT)
     calc_array_multiply_kernel_int<<<numBlocks,numThreadsPerBlock>>>((int *)data_1_device,(int *)data_2_device);
  else
    SID_trap_error("Unknown variable type in calc_array_multiply",ERROR_LOGIC);

  // Block until the Device is done
  cudaThreadSynchronize();

  cudaError_t err = cudaGetLastError();
  if(cudaSuccess!=err)
     SID_trap_error("Cuda error: %s.", ERROR_LOGIC,cudaGetErrorString( err) );

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

