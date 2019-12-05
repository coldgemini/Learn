#!/usr/bin/env bash

g++ -O3 -Wall -shared -std=c++11 -fPIC \
    -I/usr/include/python3.7 \
    -I$HOME/.virtualenvs/py37/include/site/python3.7 \
    `python -m pybind11 --includes` \
    example.cpp -o example`python-config --extension-suffix`