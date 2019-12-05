#!/usr/bin/env bash
#nvcc -shared -std=c++11 -Xcompiler -fPIC \
#    -I/usr/include/python3.7 \
#    -I/data2/home/zhouxiangyong/NVIDIA_CUDA-10.0_Samples/common/inc \
#    -I$HOME/.virtualenvs/py37/include/site/python3.7 \
#    -L/usr/lib/x86_64-linux-gnu \
#    -lGL -lGLU \
#    `python -m pybind11 --includes` \
#    cuda_ops_mod.cpp cuda_ops_mod_kernel.cu \
#    -o cuda_ops_mod`python-config --extension-suffix`

#nvcc -shared -std=c++11 -Xcompiler -fPIC \
#    -I/usr/include/python3.7 \
#    -I/data2/home/zhouxiangyong/NVIDIA_CUDA-10.0_Samples/common/inc \
#    -I$HOME/.virtualenvs/py37/include/site/python3.7 \
#    -L/usr/lib/x86_64-linux-gnu \
#    -lGL -lGLU \
#    `python -m pybind11 --includes` \
#    cuda_ops_mod.cpp cuda_ops_mod.cu \
#    -o cuda_ops_mod`python-config --extension-suffix`

export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
export PATH=/usr/local/cuda/bin:$PATH

rm *.o *.so
nvcc -O3 -shared -std=c++11 \
    -I /usr/local/cuda/include/ \
    -I /usr/local/cuda/samples/common/inc/ \
    -c -Xcompiler -fPIC \
    -Wno-deprecated-gpu-targets \
    cuda_ops_mod_kernel.cu

g++ -O3 -shared -std=c++11 -fPIC \
    -I /usr/local/python3/include/python3.7m/ \
    -I /usr/local/python3/include/python3.7m/pybind11/ \
    -I /usr/local/cuda/include/ \
    -I /usr/local/cuda/samples/common/inc/ \
    `python-config --cflags --ldflags` -c \
    cuda_ops_mod.cpp

g++ -shared -fPIC  \
    cuda_ops_mod.o cuda_ops_mod_kernel.o \
    -o cuda_ops_mod.so \
    -L /usr/local/cuda/lib64/ -lcuda -lcudart \
    -L/usr/lib/x86_64-linux-gnu \
    -lGL -lGLU
