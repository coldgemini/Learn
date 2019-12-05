#include <assert.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

////////////////////////////////////////////////////////////////////////////////
// Constants
const float angle = 0.5f;        // angle to rotate image by (in radians)

// Texture reference for 2D float texture
texture<float, 1, cudaReadModeElementType> tex;

// Auto-Verification Code
bool testResult = true;


__global__ void interp1d_ker(float *out, float *a, int X) {
    // block parallel version
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int tid = x + y * Y + z * Z * Y;

}

namespace py = pybind11;


py::array_t<float> interp1d(py::array_t<float> input1) {

/*  read input arrays buffer_info */
    auto bufin = input1.request();
//    if (buf1.size != buf2.size)
//        throw std::runtime_error("Input shapes must match");

/*  allocate the output buffer */
    py::array_t<float> result = py::array_t<float>(bufin.size);
    auto bufout = result.request();
    float *ptr1 = (float *) bufin.ptr, *ptr3 = (float *) bufout.ptr;
    size_t X = bufin.shape[0];
    std::cout << "X: " << X << std::endl;

    float *d_a, *d_out;

    // Allocate device memory
    cudaMalloc((void **) &d_a, sizeof(float) * X);
    cudaMalloc((void **) &d_out, sizeof(float) * X);

    // Transfer data from host to device memory
    cudaMemcpy(d_a, ptr1, sizeof(float) * X, cudaMemcpyHostToDevice);

    // Executing kernel
//    vector_add2 << < 1, X * Y >> > (d_out, d_a, d_b);
//    vector_add2 << < X, Y >> > (d_out, d_a, d_b);
    dim3 grid(1, 1, 1);
    dim3 block(X, Y, Z);
//    vector_add3 << < grid, block >> > (d_out, d_a, d_b, X);
//    vector_add3 << < grid, block >> > (d_out, d_a, d_b, Y);
    dilation_ker << < grid, block >> > (d_out, d_a, X, Y, Z);

    // Transfer data back to host memory
    cudaMemcpy(ptr3, d_out, sizeof(float) * X * Y * Z, cudaMemcpyDeviceToHost);


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
