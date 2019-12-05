#include <stdio.h>

#define N 5

__global__ void vector_add(float *out, float *a, float *b, int n) {
  for (int i = 0; i < n; i++) {
    out[i] = a[i] + b[i];
  }
}

int main() {
  float *a, *b, *out;
  float *d_a;

  // Allocate memory
  a = (float *)malloc(sizeof(float) * N);
  b = (float *)malloc(sizeof(float) * N);
  out = (float *)malloc(sizeof(float) * N);

  // Allocate device memory for a
  cudaMalloc((void **)&d_a, sizeof(float) * N);

  // Transfer data from host to device memory
  cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);

  // Initialize array
  for (int i = 0; i < N; i++) {
    a[i] = 1.0f;
    b[i] = 2.0f;
  }

  // Main function
  //   vector_add(out, a, b, N);
  vector_add<<<1, 1>>>(out, d_a, b, N);

  cudaFree(d_a);

  // output
  for (int i = 0; i < N; i++) {
    printf("%.6f\n", *out);
  }
}
