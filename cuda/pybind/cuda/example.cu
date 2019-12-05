#include <assert.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>


__global__ void vector_add(float *out, float *a, float *b, int n) {
    // serial version
    for (int i = 0; i < n; i++) {
        out[i] = a[i] + b[i];
    }
}

__global__ void vector_add2(float *out, float *a, float *b) {
    // linear parallel version
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < 4)
        out[tid] = a[tid] + b[tid];
}

__global__ void vector_add3(float *out, float *a, float *b, int n) {
    // block parallel version
//    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    int tid = x + y * n;
    if (tid < 10)
//        out[tid] = a[tid] + b[tid];
        out[tid] = tid;
}

namespace py = pybind11;


py::array_t<float> add_arrays(py::array_t<float> input1, py::array_t<float> input2) {

/*  read input arrays buffer_info */
    auto buf1 = input1.request(), buf2 = input2.request();
    if (buf1.size != buf2.size)
        throw std::runtime_error("Input shapes must match");

/*  allocate the output buffer */
    py::array_t<float> result = py::array_t<float>(buf1.size);
    auto buf3 = result.request();

    float *ptr1 = (float *) buf1.ptr, *ptr2 = (float *) buf2.ptr, *ptr3 = (float *) buf3.ptr;
    size_t X = buf1.shape[0];
    size_t Y = buf1.shape[1];
    std::cout << "X: " << X << std::endl;
    std::cout << "Y: " << Y << std::endl;


    float *d_a, *d_b, *d_out;


    // Allocate device memory
    cudaMalloc((void **) &d_a, sizeof(float) * X * Y);
    cudaMalloc((void **) &d_b, sizeof(float) * X * Y);
    cudaMalloc((void **) &d_out, sizeof(float) * X * Y);

    // Transfer data from host to device memory
    cudaMemcpy(d_a, ptr1, sizeof(float) * X * Y, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, ptr2, sizeof(float) * X * Y, cudaMemcpyHostToDevice);

    // Executing kernel
//    vector_add2 << < 1, X * Y >> > (d_out, d_a, d_b);
//    vector_add2 << < X, Y >> > (d_out, d_a, d_b);
    dim3 grid(2, 2);
    dim3 block(X / 2, Y / 2);
    vector_add3 << < grid, block >> > (d_out, d_a, d_b, X);
//    vector_add3 << < grid, block >> > (d_out, d_a, d_b, Y);

    // Transfer data back to host memory
    cudaMemcpy(ptr3, d_out, sizeof(float) * X * Y, cudaMemcpyDeviceToHost);


    // Deallocate device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_out);


// reshape result
    result.resize({X, Y});

    return result;
}


PYBIND11_MODULE(example, m
) {
m.

doc() = "Add two vectors using pybind11"; // optional module docstring
m.def("add_arrays", &add_arrays, "Add two NumPy arrays");
}
