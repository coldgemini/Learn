#!/usr/bin/env bash
nvcc -shared -std=c++11 -Xcompiler -fPIC \
    -I/usr/include/python3.7 \
    -I$HOME/.virtualenvs/py37/include/site/python3.7 \
    `python -m pybind11 --includes` \
    dilation_mod.cu -o dilation_mod`python-config --extension-suffix`
