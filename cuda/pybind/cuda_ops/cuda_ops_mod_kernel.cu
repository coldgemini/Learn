#ifndef _SIMPLETEXTURE3D_KERNEL_CU_
#define _SIMPLETEXTURE3D_KERNEL_CU_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>

#include <helper_cuda.h>
#include <helper_math.h>
#include "cuda_ops_mod.h"

typedef unsigned int uint;
typedef unsigned char uchar;

texture<float, cudaTextureType3D, cudaReadModeElementType> tex;  // 3D texture
cudaArray *d_volumeArray = 0;

__global__ void
d_render(float rad, float *d_output, uint imageW, uint imageH, uint imageL) {
    uint x = blockIdx.x * blockDim.x + threadIdx.x;
    uint y = blockIdx.y * blockDim.y + threadIdx.y;
    uint z = blockIdx.z * blockDim.z + threadIdx.z;

    float w = (((float) z) + 0.5f) / (float) imageL;
    float u0 = (float) (x + 0.5f) - (float) imageW / 2;
    float v0 = (float) (y + 0.5f) - (float) imageH / 2;
    float u1 = u0 / (float) imageW;
    float v1 = v0 / (float) imageH;
    float tu = u1 * cosf(rad) - v1 * sinf(rad);
    float tv = v1 * cosf(rad) + u1 * sinf(rad);
    float u2 = tu + 0.5f;
    float v2 = tv + 0.5f;

    // read from 3D texture
    float voxel = tex3D(tex, u2, v2, w);

    if ((x < imageW) && (y < imageH) && (z < imageL)) {
        uint i = x + y * imageW + z * imageW * imageH;
        d_output[i] = voxel;
    }
}


__global__ void
d_render_shift(SHIFT_PARAMS shift, float *d_output, uint imageW, uint imageH, uint imageL) {
    uint x = blockIdx.x * blockDim.x + threadIdx.x;
    uint y = blockIdx.y * blockDim.y + threadIdx.y;
    uint z = blockIdx.z * blockDim.z + threadIdx.z;

    float u = ((float) x + shift.x + 0.5f) / (float) imageW;
    float v = ((float) y + shift.y + 0.5f) / (float) imageH;
    float w = ((float) z + shift.z + 0.5f) / (float) imageL;

    // read from 3D texture
    float voxel;
    voxel = tex3D(tex, u, v, w);

    if ((x < imageW) && (y < imageH) && (z < imageL)) {
        uint i = x + y * imageW + z * imageW * imageH;
        d_output[i] = voxel;
    }
}

__global__ void
d_render_tf2dL_z(TF_PARAMS tf_params, float *d_output, uint imageW, uint imageH, uint imageL) {
    uint x = blockIdx.x * blockDim.x + threadIdx.x;
    uint y = blockIdx.y * blockDim.y + threadIdx.y;
    uint z = blockIdx.z * blockDim.z + threadIdx.z;

    // move origin to center, integer coordinates
    float w = (((float) z + 0.5f)) / (float) imageL;
    float u0 = (float) (x + 0.5f) - (float) imageW / 2;
    float v0 = (float) (y + 0.5f) - (float) imageH / 2;
    // spatial transform
    float tu = u0 * tf_params.h0 + v0 * tf_params.h1 + tf_params.h2;
    float tv = u0 * tf_params.h3 + v0 * tf_params.h4 + tf_params.h5;
    // normalize coordinates
    float u1 = tu / (float) imageW;
    float v1 = tv / (float) imageH;
    // move origin to top-left
    float u = u1 + 0.5f;
    float v = v1 + 0.5f;

    // read from 3D texture
    float voxel = tex3D(tex, u, v, w);

    if ((x < imageW) && (y < imageH) && (z < imageL)) {
        uint i = x + y * imageW + z * imageW * imageH;
        d_output[i] = voxel;
    }
}

__global__ void
d_render_tf2dL_x(TF_PARAMS tf_params, float *d_output, uint imageW, uint imageH, uint imageL) {
    uint x = blockIdx.x * blockDim.x + threadIdx.x;
    uint y = blockIdx.y * blockDim.y + threadIdx.y;
    uint z = blockIdx.z * blockDim.z + threadIdx.z;

    // move origin to center, integer coordinates
    float u = (float) (x + 0.5f) / (float) imageW;
    float v0 = (float) (y + 0.5f) - (float) imageH / 2;
    float w0 = (float) (z + 0.5f) - (float) imageL / 2;
    // spatial transform
    float tv = v0 * tf_params.h0 + w0 * tf_params.h1 + tf_params.h2;
    float tw = v0 * tf_params.h3 + w0 * tf_params.h4 + tf_params.h5;
    // normalize coordinates
    float v1 = tv / (float) imageH;
    float w1 = tw / (float) imageL;
    // move origin to top-left
    float v = v1 + 0.5f;
    float w = w1 + 0.5f;

    // read from 3D texture
    float voxel = tex3D(tex, u, v, w);

    if ((x < imageW) && (y < imageH) && (z < imageL)) {
        uint i = x + y * imageW + z * imageW * imageH;
        d_output[i] = voxel;
    }
}

__global__ void
d_render_tf2dL_y(TF_PARAMS tf_params, float *d_output, uint imageW, uint imageH, uint imageL) {
    uint x = blockIdx.x * blockDim.x + threadIdx.x;
    uint y = blockIdx.y * blockDim.y + threadIdx.y;
    uint z = blockIdx.z * blockDim.z + threadIdx.z;

    // move origin to center, integer coordinates
    float v = (float) (y + 0.5f) / (float) imageH;
    float w0 = (float) (z + 0.5f) - (float) imageL / 2;
    float u0 = (float) (x + 0.5f) - (float) imageW / 2;
    // spatial transform
    float tw = w0 * tf_params.h0 + u0 * tf_params.h1 + tf_params.h2;
    float tu = w0 * tf_params.h3 + u0 * tf_params.h4 + tf_params.h5;
    // normalize coordinates
    float w1 = tw / (float) imageL;
    float u1 = tu / (float) imageW;
    // move origin to top-left
    float w = w1 + 0.5f;
    float u = u1 + 0.5f;

    // read from 3D texture
    float voxel = tex3D(tex, u, v, w);

    if ((x < imageW) && (y < imageH) && (z < imageL)) {
        uint i = x + y * imageW + z * imageW * imageH;
        d_output[i] = voxel;
    }
}

extern "C"
void setTextureFilterMode(bool bLinearFilter) {
    tex.filterMode = bLinearFilter ? cudaFilterModeLinear : cudaFilterModePoint;
//    tex.filterMode = cudaFilterModeLinear;
}

extern "C"
void freeTexture() {
    checkCudaErrors(cudaFreeArray(d_volumeArray));
    d_volumeArray = 0;
}

extern "C"
void initCuda(const float *h_volume, cudaExtent volumeSize) {
    // create 3D array
    cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float>();
    checkCudaErrors(cudaMalloc3DArray(&d_volumeArray, &channelDesc, volumeSize));

    // copy data to 3D array
    cudaMemcpy3DParms copyParams = {0};
    copyParams.srcPtr = make_cudaPitchedPtr((void *) h_volume, volumeSize.width * sizeof(float), volumeSize.width,
                                            volumeSize.height);
    copyParams.dstArray = d_volumeArray;
    copyParams.extent = volumeSize;
    copyParams.kind = cudaMemcpyHostToDevice;
    checkCudaErrors(cudaMemcpy3D(&copyParams));

    // set texture parameters
    tex.normalized = true;                      // access with normalized texture coordinates
    tex.filterMode = cudaFilterModeLinear;      // linear interpolation
//    tex.addressMode[0] = cudaAddressModeClamp;   // wrap texture coordinates
//    tex.addressMode[1] = cudaAddressModeClamp;
//    tex.addressMode[2] = cudaAddressModeClamp;
//    tex.addressMode[0] = cudaAddressModeWrap;   // wrap texture coordinates
//    tex.addressMode[1] = cudaAddressModeWrap;
//    tex.addressMode[2] = cudaAddressModeWrap;
    tex.addressMode[0] = cudaAddressModeBorder;   // wrap texture coordinates
    tex.addressMode[1] = cudaAddressModeBorder;
    tex.addressMode[2] = cudaAddressModeBorder;

    // bind array to 3D texture
    checkCudaErrors(cudaBindTextureToArray(tex, d_volumeArray, channelDesc));
}

extern "C"
void render_kernel(dim3 gridSize, dim3 blockSize, float rad, float *d_output, uint imageW, uint imageH, uint imageL) {
    d_render << < gridSize, blockSize >> > (rad, d_output, imageW, imageH, imageL);
}

extern "C"
void render_kernel_shift(dim3 gridSize, dim3 blockSize, SHIFT_PARAMS shift, float *d_output, uint imageW, uint imageH,
                         uint imageL) {
    d_render_shift << < gridSize, blockSize >> > (shift, d_output, imageW, imageH, imageL);
}

extern "C"
void render_kernel_tf2dL(dim3 gridSize, dim3 blockSize, uint axis, TF_PARAMS tf_params, float *d_output, uint imageW,
                         uint imageH,
                         uint imageL) {
    switch (axis) {
        case 0 :
            std::cout << "axis = 0\n";
            d_render_tf2dL_x << < gridSize, blockSize >> > (tf_params, d_output, imageW, imageH, imageL);
            break;       // and exits the switch
        case 1 :
            std::cout << "axis = 1\n";
            d_render_tf2dL_y << < gridSize, blockSize >> > (tf_params, d_output, imageW, imageH, imageL);
            break;       // and exits the switch
        case 2 :
            std::cout << "axis = 2\n";
            d_render_tf2dL_z << < gridSize, blockSize >> > (tf_params, d_output, imageW, imageH, imageL);
            break;
        default: // compilation error: jump to default: would enter the scope of 'x'
            std::cerr << "Error: axis not in [0,1,2] !!!\n";
            break;
    }
}

#endif // #ifndef _SIMPLETEXTURE3D_KERNEL_CU_
