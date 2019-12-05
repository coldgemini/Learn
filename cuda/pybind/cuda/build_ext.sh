#!/usr/bin/env bash
nvcc -shared -std=c++11 -Xcompiler -fPIC \
    -I/usr/include/python3.7 \
    -I$HOME/.virtualenvs/py37/include/site/python3.7 \
    `python -m pybind11 --includes` \
    example.cu -o example`python-config --extension-suffix`
