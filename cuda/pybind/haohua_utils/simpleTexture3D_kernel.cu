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

#ifndef _SIMPLETEXTURE3D_KERNEL_CU_
#define _SIMPLETEXTURE3D_KERNEL_CU_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <helper_cuda.h>
#include <helper_math.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

texture<float, cudaTextureType3D, cudaReadModeElementType> tex;  // 3D texture
cudaArray *d_volumeArray = 0;

__global__ void
d_render(float *d_output, uint imageW, uint imageH, uint imageL)
{
    uint x = blockIdx.x * blockDim.x + threadIdx.x;
    uint y = blockIdx.y * blockDim.y + threadIdx.y;
    uint z = blockIdx.z * blockDim.z + threadIdx.z;

    float u = (float)(x + 0.5f) / imageW;
    float v = (float)(y + 0.5f) / imageH;
    float w = (float)(z + 0.5f) / imageL;

    // read from 3D texture
    float voxel = tex3D(tex, u, v, w);

    if ((x < imageW) && (y < imageH) && (z < imageL))
    {
        uint i = y * imageW + x + z * imageW * imageH;
        d_output[i] = voxel;
    }
}

extern "C"
void setTextureFilterMode(bool bLinearFilter)
{
    tex.filterMode = bLinearFilter ? cudaFilterModeLinear : cudaFilterModePoint;
}

extern "C"
void freeTexture()
{
    checkCudaErrors(cudaFreeArray(d_volumeArray));
    d_volumeArray = 0;
}

extern "C"
void initCuda(const float *h_volume, cudaExtent volumeSize)
{
    // create 3D array
    cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float>();
    checkCudaErrors(cudaMalloc3DArray(&d_volumeArray, &channelDesc, volumeSize));

    // copy data to 3D array
    cudaMemcpy3DParms copyParams = {0};
    copyParams.srcPtr   = make_cudaPitchedPtr((void *)h_volume, volumeSize.width*sizeof(float), volumeSize.width, volumeSize.height);
    copyParams.dstArray = d_volumeArray;
    copyParams.extent   = volumeSize;
    copyParams.kind     = cudaMemcpyHostToDevice;
    checkCudaErrors(cudaMemcpy3D(&copyParams));

    // set texture parameters
    tex.normalized = true;                      // access with normalized texture coordinates
    tex.filterMode = cudaFilterModeLinear;      // linear interpolation
    tex.addressMode[0] = cudaAddressModeClamp;   // wrap texture coordinates
    tex.addressMode[1] = cudaAddressModeClamp;
    tex.addressMode[2] = cudaAddressModeClamp;

    // bind array to 3D texture
    checkCudaErrors(cudaBindTextureToArray(tex, d_volumeArray, channelDesc));
}

extern "C"
void render_kernel(dim3 gridSize, dim3 blockSize, float *d_output, uint imageW, uint imageH, uint imageL)
{
    d_render<<<gridSize, blockSize>>>(d_output, imageW, imageH, imageL);
}

#endif // #ifndef _SIMPLETEXTURE3D_KERNEL_CU_
