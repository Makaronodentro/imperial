#include <stdio.h>

__global__ // declares kernels, variables declared here are device variables
void saxpy(int n, float a, float *x, float *y) 
// n, a, i will be stored in registers by each thread
// *x and *y must be pointers to device memory space
{
  // blockDim = dimensions of each block (256)
  // threadIdx - index of thread, blockIdx - index of block
  // i becomes a global index that can be used to access array elements 
  int i = blockIdx.x*blockDim.x + threadIdx.x;
  if (i < n) y[i] = a*x[i] + y[i];
}

int main(void)
{
  int N = 1<<20;
  
  printf("%i \n" , N);
  
  // Host Code
  float *x, *y, *d_x, *d_y; 
  
  // x & y are host arrays 
  x = (float*)malloc(N*sizeof(float));
  y = (float*)malloc(N*sizeof(float));

  // D_x & d_y point to device arrays, allocated with cudaMalloc
  cudaMalloc(&d_x, N*sizeof(float)); 
  cudaMalloc(&d_y, N*sizeof(float));

  // Initialize x to array of ones. y to arrays of twos
  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  // destination, source, size, direction of copy
  cudaMemcpy(d_x, x, N*sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(d_y, y, N*sizeof(float), cudaMemcpyHostToDevice);

  // Perform SAXPY on 1M elements
  // triple chevrons define execution configuration
  // <<<grid of thread blocks, threads>>> 
  saxpy<<<(N+255)/256, 256>>>(N, 2.0f, d_x, d_y);

  // Copy back to host after kernel has been run
  cudaMemcpy(y, d_y, N*sizeof(float), cudaMemcpyDeviceToHost);

  float maxError = 0.0f;
  for (int i = 0; i < N; i++)
    maxError = max(maxError, abs(y[i]-4.0f));
  printf("Max error: %fn", maxError);
}
