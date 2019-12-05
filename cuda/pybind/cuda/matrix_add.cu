#include <assert.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define N 4
#define BLOCK_DIM 4

__global__ void matrixAdd(int *a, int *b, int *c);

int main() {
    int a[N][N], b[N][N], c[N][N];
    int *dev_a, *dev_b, *dev_c;
    int size = N * N * sizeof(int);

    for (size_t idx = 0; idx < N; idx++)
        for (size_t idy = 0; idy < N; idy++) {
            a[idx][idy] = idx;
            b[idx][idy] = idy;
        }
    // initialize a and b with real values (NOT SHOWN)
    cudaMalloc((void **) &dev_a, size);
    cudaMalloc((void **) &dev_b, size);
    cudaMalloc((void **) &dev_c, size);
    cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, size, cudaMemcpyHostToDevice);
    dim3 dimBlock(BLOCK_DIM, BLOCK_DIM);
    dim3 dimGrid((int) ceil(N / dimBlock.x), (int) ceil(N / dimBlock.y));
    matrixAdd << < dimGrid, dimBlock >> > (dev_a, dev_b, dev_c);
    cudaMemcpy(c, dev_c, size, cudaMemcpyDeviceToHost);
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);

    for (size_t idx = 0; idx < N; idx++)
        for (size_t idy = 0; idy < N; idy++)
            std::cout << c[idx][idy] << std::endl;
}

__global__ void matrixAdd(int *a, int *b, int *c) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int index = col + row * N;
    if (col < N && row < N) {
        c[index] = a[index] + b[index];
    }
}