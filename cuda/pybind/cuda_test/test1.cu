//
// Created by xiang on 19-7-9.
//

#include <cstdio>
//#include "handle.h"
#include <helper_cuda.h>

using namespace std;

texture<float, 2> tex_w;

__global__ void kernel(int imax, float(*w)[3], float (*f)[3]) {
    int i = threadIdx.x;
    int j = threadIdx.y;

    if (i < imax)
        f[i][j] = tex2D(tex_w, i, j);
}

void print_to_stdio(int imax, float (*w)[3]) {
    for (int i = 0; i < imax; i++) {
        printf("%2d  %3.6f\t  %3.6f\t %3.6f\n", i, w[i][0], w[i][1], w[i][2]);
    }
}

int main(void) {
    int imax = 8;
    float (*w)[3];
    float (*d_w)[3], (*d_f)[3];
    dim3 grid(imax, 3);

    w = (float (*)[3]) malloc(imax * 3 * sizeof(float));

    for (int i = 0; i < imax; i++) {
        for (int j = 0; j < 3; j++) {
            w[i][j] = i + 0.01f * j;
        }
    }

    print_to_stdio(imax, w);

    cudaMalloc((void **) &d_w, 3 * imax * sizeof(float));
    cudaMalloc((void **) &d_f, 3 * imax * sizeof(float));

    cudaChannelFormatDesc desc = cudaCreateChannelDesc<float>();
//    HANDLE_ERROR(cudaBindTexture2D(NULL, tex_w, d_w, desc, imax, 3, sizeof(float) * imax));
    checkCudaErrors(cudaBindTexture2D(NULL, tex_w, d_w, desc, imax, 3, sizeof(float) * imax));

    cudaMemcpy(d_w, w, 3 * imax * sizeof(float), cudaMemcpyHostToDevice);

    // just use threads for simplicity
    kernel << < 1, grid >> > (imax, d_w, d_f);

    cudaMemcpy(w, d_f, 3 * imax * sizeof(float), cudaMemcpyDeviceToHost);

    cudaUnbindTexture(tex_w);
    cudaFree(d_w);
    cudaFree(d_f);

    print_to_stdio(imax, w);

    free(w);
    return 0;
}