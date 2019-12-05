#!/usr/bin/env bash

rsync -avuhP  -e 'ssh -p 10822' * zhouxiangyong@s108:~/Dev/cuda/pybind
