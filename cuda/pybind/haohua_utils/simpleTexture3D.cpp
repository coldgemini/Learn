/*
 * Copyright 1993-2015 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 */

/*
    3D texture sample

    This sample loads a 3D volume from disk and displays slices through it
    using 3D texture lookups.
*/

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
//#include <helper_gl.h>  #cuda10
#include <helper_cuda_gl.h>
#include <helper_functions.h>
#include <vector_types.h>

// pybind11
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

typedef unsigned int  uint;
typedef unsigned char uchar;

#define MAX_EPSILON_ERROR 5.0f
#define THRESHOLD         0.15f

#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

extern "C" void freeTexture();
extern "C" void setTextureFilterMode(bool bLinearFilter);
extern "C" void initCuda(const float *h_volume, cudaExtent volumeSize);
extern "C" void render_kernel(dim3 gridSize, dim3 blockSize, float *d_output, uint imageW, uint imageH, uint imageL);

py::array_t<float> resize_init(uint devID)
{
    devID = gpuDeviceInit(devID);
}

py::array_t<float> resize(py::array_t<float> input_cube, uint w, uint h, uint l, uint inw, uint inh, uint inl)
{
    uint width = w, height = h, depth = l;
    dim3 blockSize(16, 16, 4);
    dim3 gridSize((width / blockSize.x + 1), (height / blockSize.y + 1), (depth / blockSize.z + 1));

    auto result = py::array_t<float>(width * height * depth);
    auto bufoutput = result.request();
    auto bufinput = input_cube.request();

    bool linearFiltering = true;

    cudaExtent volumeSize = make_cudaExtent(inw, inh, inl);
    initCuda((float *)bufinput.ptr, volumeSize);

    setTextureFilterMode(linearFiltering);
    float* d_output = NULL;
    checkCudaErrors(cudaMalloc((void **)&d_output, width*height*depth*sizeof(float)));

    render_kernel(gridSize, blockSize, d_output, width, height, depth);
    checkCudaErrors(cudaDeviceSynchronize());
    getLastCudaError("render_kernel failed");

    checkCudaErrors(cudaMemcpy(bufoutput.ptr, d_output, width*height*depth*sizeof(float), cudaMemcpyDeviceToHost));

    checkCudaErrors(cudaFree(d_output));
    freeTexture();
    return result;
}

PYBIND11_PLUGIN(simpleTexture3D) {
    py::module m("simpleTexture3D");
    m.def("resize", &resize, "cube resize");
    m.def("resize_init", &resize_init, "cube resize init");
    return m.ptr();
}
