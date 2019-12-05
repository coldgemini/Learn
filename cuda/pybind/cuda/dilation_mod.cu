#include <assert.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>


__global__ void dilation_ker(bool *out, bool *a, int X, int Y, int Z) {
    // block parallel version
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    int z = blockIdx.z * blockDim.z + threadIdx.z;
    int tid = x + y * Y + z * Z * Y;

    if (a[tid])
        out[tid] = 1;
    else
        return;

    if (x - 1 >= 0) {
        int x_t = x - 1;
        int oid = x_t + y * Y + z * Z * Y;
        out[oid] = 1;
    }
    if (x + 1 <= X) {
        int x_t = x + 1;
        int oid = x_t + y * Y + z * Z * Y;
        out[oid] = 1;
    }
    if (y - 1 >= 0) {
        int y_t = y - 1;
        int oid = x + y_t * Y + z * Z * Y;
        out[oid] = 1;
    }
    if (y + 1 <= Y) {
        int y_t = y + 1;
        int oid = x + y_t * Y + z * Z * Y;
        out[oid] = 1;
    }
    if (z - 1 >= 0) {
        int z_t = z - 1;
        int oid = x + y * Y + z_t * Z * Y;
        out[oid] = 1;
    }
    if (z + 1 <= Z) {
        int z_t = z + 1;
        int oid = x + y * Y + z_t * Z * Y;
        out[oid] = 1;
    }
}

namespace py = pybind11;


py::array_t<bool> dilation(py::array_t<bool> input1) {

/*  read input arrays buffer_info */
    auto buf1 = input1.request();
//    if (buf1.size != buf2.size)
//        throw std::runtime_error("Input shapes must match");

/*  allocate the output buffer */
    py::array_t<bool> result = py::array_t<bool>(buf1.size);
    auto buf3 = result.request();

    bool *ptr1 = (bool *) buf1.ptr, *ptr3 = (bool *) buf3.ptr;
    size_t X = buf1.shape[0];
    size_t Y = buf1.shape[1];
    size_t Z = buf1.shape[2];
    std::cout << "X: " << X << std::endl;
    std::cout << "Y: " << Y << std::endl;
    std::cout << "Z: " << Z << std::endl;


    bool *d_a, *d_out;


    // Allocate device memory
    cudaMalloc((void **) &d_a, sizeof(bool) * X * Y * Z);
    cudaMalloc((void **) &d_out, sizeof(bool) * X * Y * Z);

    // Transfer data from host to device memory
    cudaMemcpy(d_a, ptr1, sizeof(bool) * X * Y * Z, cudaMemcpyHostToDevice);

    // Executing kernel
//    vector_add2 << < 1, X * Y >> > (d_out, d_a, d_b);
//    vector_add2 << < X, Y >> > (d_out, d_a, d_b);
    dim3 grid(1, 1, 1);
    dim3 block(X, Y, Z);
//    vector_add3 << < grid, block >> > (d_out, d_a, d_b, X);
//    vector_add3 << < grid, block >> > (d_out, d_a, d_b, Y);
    dilation_ker << < grid, block >> > (d_out, d_a, X, Y, Z);

    // Transfer data back to host memory
    cudaMemcpy(ptr3, d_out, sizeof(bool) * X * Y * Z, cudaMemcpyDeviceToHost);


    // Deallocate device memory
    cudaFree(d_a);
    cudaFree(d_out);


// reshape result
    result.resize({X, Y, Z});

    return result;
}


PYBIND11_MODULE(dilation_mod, m
) {
m.

doc() = "dilation using cuda pybind11"; // optional module docstring
m.def("dilation", &dilation, "dilation");
}
