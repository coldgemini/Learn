#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// includes, cuda
#include <vector_types.h>
#include <driver_functions.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

// CUDA utilities and system includes
#include <helper_cuda.h>
#include <helper_gl.h>  //cuda10
//#include <helper_cuda_gl.h>
#include <helper_functions.h>
#include <vector_types.h>

// pybind11
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include "cuda_ops_mod.h"

namespace py = pybind11;

typedef unsigned int uint;
typedef unsigned char uchar;

#define MAX_EPSILON_ERROR 5.0f
#define THRESHOLD         0.15f

#ifndef MAX
#define MAX(a, b) ((a > b) ? a : b)
#endif

extern "C" void freeTexture();
extern "C" void setTextureFilterMode(bool bLinearFilter);
extern "C" void initCuda(const float *h_volume, cudaExtent volumeSize);

extern "C" void
render_kernel(dim3 gridSize, dim3 blockSize, float rad, float *d_output, uint imageW, uint imageH, uint imageL);

extern "C" void
render_kernel_shift(dim3 gridSize, dim3 blockSize, SHIFT_PARAMS shift, float *d_output, uint imageW, uint imageH,
                    uint imageL);

extern "C" void
render_kernel_tf2dL(dim3 gridSize, dim3 blockSize, uint axis, TF_PARAMS tf_params, float *d_output, uint imageW,
                    uint imageH,
                    uint imageL);

py::array_t<float> cuda_ops_init(uint devID) {
    devID = gpuDeviceInit(devID);
}

py::array_t<float>
shift3d(py::array_t<float> input_cube, std::vector<float> &py_shift) {
//    shift3d(py::array_t<float> input_cube, py::tuple py_shift) {
//    for (auto item : py_shift)
//        std::cout << item << " " << std::endl;
//    std::cout << "tuple [0]: " << py_shift[0] << " " << std::endl;
//    std::vector<float> v = py_shift;
//    auto buf_shift = py_shift.size();
    std::cout << "tuple size: " << py_shift.size() << " " << std::endl;
//    std::cout << "tuple size: " << py_shift[0] << " " << std::endl;

    SHIFT_PARAMS shift;
    shift.x = py_shift[0];
    shift.y = py_shift[1];
    shift.z = py_shift[2];

    auto bufinput = input_cube.request();

    size_t X = bufinput.shape[0];
    size_t Y = bufinput.shape[1];
    size_t Z = bufinput.shape[2];
    std::cout << "X: " << X << std::endl;
    std::cout << "Y: " << Y << std::endl;
    std::cout << "Z: " << Z << std::endl;

    uint width = X, height = Y, depth = Z;
//    std::cout << "width: " << width << std::endl;
//    std::cout << "height: " << height << std::endl;
//    std::cout << "depth: " << depth << std::endl;
    auto result = py::array_t<float>(width * height * depth);
    auto bufoutput = result.request();

//    dim3 blockSize(4, 3, 2);
//    dim3 blockSize(3, 4, 5);
//    dim3 blockSize(5, 4, 3);
//    dim3 blockSize(3, 3, 3);
    dim3 blockSize(16, 16, 4);
//    dim3 blockSize(512, 512, 1);
    std::cout << "blockSize.x: " << blockSize.x << std::endl;
    std::cout << "blockSize.y: " << blockSize.y << std::endl;
    std::cout << "blockSize.z: " << blockSize.z << std::endl;
    dim3 gridSize((width / blockSize.x + 1), (height / blockSize.y + 1), (depth / blockSize.z + 1));
//    dim3 gridSize((width / blockSize.x), (height / blockSize.y), (depth / blockSize.z));
    std::cout << "gridSize.x: " << gridSize.x << std::endl;
    std::cout << "gridSize.y: " << gridSize.y << std::endl;
    std::cout << "gridSize.z: " << gridSize.z << std::endl;


    cudaExtent volumeSize = make_cudaExtent(X, Y, Z);
    initCuda((float *) bufinput.ptr, volumeSize);

    bool linearFiltering = true;
    setTextureFilterMode(linearFiltering);
    float *d_output = NULL;
    checkCudaErrors(cudaMalloc((void **) &d_output, width * height * depth * sizeof(float)));

    render_kernel_shift(gridSize, blockSize, shift, d_output, width, height, depth);
    checkCudaErrors(cudaDeviceSynchronize());
    getLastCudaError("render_kernel failed");

    checkCudaErrors(
            cudaMemcpy(bufoutput.ptr, d_output, width * height * depth * sizeof(float), cudaMemcpyDeviceToHost));

    checkCudaErrors(cudaFree(d_output));
    freeTexture();

//    result.resize({X, Y, Z});
    result.resize({X * Y * Z});
    return result;
}

py::array_t<float>
rotate3d(py::array_t<float> input_cube, float angle) {
//    rotate3d(py::array_t<float> input_cube, float angle, uint w, uint h, uint l, uint inw, uint inh, uint inl) {
    float rad = angle * M_PI / 180;
    std::cout << "rad: " << rad << std::endl;

    auto bufinput = input_cube.request();

    size_t X = bufinput.shape[0];
    size_t Y = bufinput.shape[1];
    size_t Z = bufinput.shape[2];
    std::cout << "X: " << X << std::endl;
    std::cout << "Y: " << Y << std::endl;
    std::cout << "Z: " << Z << std::endl;

    uint width = X, height = Y, depth = Z;
    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "depth: " << depth << std::endl;
    auto result = py::array_t<float>(width * height * depth);
    auto bufoutput = result.request();

//    dim3 blockSize(16, 16, 4);
    dim3 blockSize(3, 3, 1);
//    dim3 blockSize(5, 5, 1);
//    dim3 blockSize(4, 4, 4);
//    dim3 blockSize(512, 512, 1);
    std::cout << "blockSize.x: " << blockSize.x << std::endl;
    std::cout << "blockSize.y: " << blockSize.y << std::endl;
    std::cout << "blockSize.z: " << blockSize.z << std::endl;
//    dim3 gridSize((width / blockSize.x + 1), (height / blockSize.y + 1), (depth / blockSize.z + 1));
    dim3 gridSize((width / blockSize.x), (height / blockSize.y), (depth / blockSize.z));
    std::cout << "gridSize.x: " << gridSize.x << std::endl;
    std::cout << "gridSize.y: " << gridSize.y << std::endl;
    std::cout << "gridSize.z: " << gridSize.z << std::endl;


    cudaExtent volumeSize = make_cudaExtent(X, Y, Z);
    initCuda((float *) bufinput.ptr, volumeSize);

    bool linearFiltering = true;
    setTextureFilterMode(linearFiltering);
    float *d_output = NULL;
    checkCudaErrors(cudaMalloc((void **) &d_output, width * height * depth * sizeof(float)));

    render_kernel(gridSize, blockSize, rad, d_output, width, height, depth);
    checkCudaErrors(cudaDeviceSynchronize());
    getLastCudaError("render_kernel failed");

    checkCudaErrors(
            cudaMemcpy(bufoutput.ptr, d_output, width * height * depth * sizeof(float), cudaMemcpyDeviceToHost));

    checkCudaErrors(cudaFree(d_output));
    freeTexture();

//    result.resize({X, Y, Z});
    result.resize({X * Y * Z});
    return result;
}


py::array_t<float>
transform2dL(py::array_t<float> input_cube, uint axis, py::array_t<float> tf_params_array) {

    TF_PARAMS tf_params;
    auto buf_params = tf_params_array.request();
    size_t params_size = buf_params.shape[0];
    float *ptr_params = (float *) buf_params.ptr;
    tf_params.h0 = ptr_params[0];
    tf_params.h1 = ptr_params[1];
    tf_params.h2 = ptr_params[2];
    tf_params.h3 = ptr_params[3];
    tf_params.h4 = ptr_params[4];
    tf_params.h5 = ptr_params[5];
    tf_params.h6 = ptr_params[6];
    tf_params.h7 = ptr_params[7];
//    for (size_t idp = 0; idp < params_size; idp++) {
//        std::cout << "tf param [" << idp << "]: " << ptr_params[idp] << std::endl;
//    }

    auto bufinput = input_cube.request();

    size_t X = bufinput.shape[0];
    size_t Y = bufinput.shape[1];
    size_t Z = bufinput.shape[2];
    std::cout << "X: " << X << std::endl;
    std::cout << "Y: " << Y << std::endl;
    std::cout << "Z: " << Z << std::endl;

    uint width = X, height = Y, depth = Z;
//    std::cout << "width: " << width << std::endl;
//    std::cout << "height: " << height << std::endl;
//    std::cout << "depth: " << depth << std::endl;
    auto result = py::array_t<float>(width * height * depth);
    auto bufoutput = result.request();

    dim3 blockSize(16, 16, 4);
//    std::cout << "blockSize.x: " << blockSize.x << std::endl;
//    std::cout << "blockSize.y: " << blockSize.y << std::endl;
//    std::cout << "blockSize.z: " << blockSize.z << std::endl;
    dim3 gridSize((width / blockSize.x + 1), (height / blockSize.y + 1), (depth / blockSize.z + 1));
//    dim3 gridSize((width / blockSize.x), (height / blockSize.y), (depth / blockSize.z));
//    std::cout << "gridSize.x: " << gridSize.x << std::endl;
//    std::cout << "gridSize.y: " << gridSize.y << std::endl;
//    std::cout << "gridSize.z: " << gridSize.z << std::endl;


    cudaExtent volumeSize = make_cudaExtent(X, Y, Z);
    initCuda((float *) bufinput.ptr, volumeSize);

    bool linearFiltering = true;
    setTextureFilterMode(linearFiltering);
    float *d_output = NULL;
    checkCudaErrors(cudaMalloc((void **) &d_output, width * height * depth * sizeof(float)));

    render_kernel_tf2dL(gridSize, blockSize, axis, tf_params, d_output, width, height, depth);
    checkCudaErrors(cudaDeviceSynchronize());
    getLastCudaError("render_kernel failed");

    checkCudaErrors(
            cudaMemcpy(bufoutput.ptr, d_output, width * height * depth * sizeof(float), cudaMemcpyDeviceToHost));

    checkCudaErrors(cudaFree(d_output));
    freeTexture();

    result.resize({X * Y * Z});
    return result;
}

PYBIND11_MODULE(cuda_ops_mod, m
) {
m.

doc() = "3d operations on numpy array using cuda pybind11"; // optional module docstring
m.def("cuda_ops_init", &cuda_ops_init, "cube cuda_ops init");
m.def("rotate3d", &rotate3d, "rotate3d");
m.def("shift3d", &shift3d, "shift3d");
m.def("transform2dL", &transform2dL, "transform2dL");
}
