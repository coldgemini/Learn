# -*- coding:utf-8 -*-

import simpleTexture3D
import numpy as np
import time
from scipy import ndimage as ndi

def test0():
    cube = np.array(range(6))
    cube0 = cube.reshape(1, 2, 3)
    print(cube)

    cube = cube0
    cube = simpleTexture3D.resize(cube.flatten(), 6, 2, 1, 3, 2, 1)
    cube = cube.reshape(1, 2, 6)
    print(cube)

    print(ndi.interpolation.zoom(cube0, [1,1,2]))

def test1():
    t0 = time.time()
    for i in range(100):
        cube = np.random.randint(1, 2048, 30*30*30)
        cube = cube.reshape(30, 30, 30)
    
        cube1 = simpleTexture3D.resize(cube.flatten(), 30, 45, 15, 30, 30, 30)
        cube1 = cube1.reshape(30,45,15)
    
        cube2 = ndi.interpolation.zoom(cube, [1,1.5,0.5])
    
        print(np.mean((cube1 - cube2)**2))
    t1 = time.time()
    print(t1 - t0)

test0()
