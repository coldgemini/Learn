from skimage.morphology import ball, dilation
from time import time
import numpy as np
import nrrd
from cuda import dilation_mod

mask_path = '/data2/home/zhouxiangyong/Tmp/dilation.nrrd'
mask_cuda_path = '/data2/home/zhouxiangyong/Tmp/dilation_cuda.nrrd'

# mask = np.zeros((3, 3, 3), dtype=np.uint8)
# mask[1, 1, 1] = 1
mask = np.zeros((555, 555, 555), dtype=np.uint8)
mask[2, 2, 2] = 1

print("start skimage dilation")
start_t = time()
selem = ball(1)
mask_sk = dilation(mask, selem).astype(np.uint8)
end_t = time()
print("skimage time: {}".format(end_t - start_t))

print("start cuda dilation")
start_t = time()
mask_cuda = dilation_mod.dilation(mask.astype(np.bool)).astype(np.uint8)
end_t = time()
print("cuda time: {}".format(end_t - start_t))

nrrd.write(mask_path, mask_sk)
nrrd.write(mask_cuda_path, mask_cuda)
