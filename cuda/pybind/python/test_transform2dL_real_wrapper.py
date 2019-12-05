from time import time
import numpy as np
import nrrd
from cuda_ops.cuda_ops_wrapper import rotate2dL, shift2dL

mask_in_path = '/data2/home/zhouxiangyong/Tmp/cuda_rotate3d_input.nrrd'
mask_out_path = '/data2/home/zhouxiangyong/Tmp/cuda_tf2dL_mask.nrrd'

angle = 90
# tx, ty = 256, 256
tx, ty = 100, 100
# tx, ty = 0, 0
axis = 1

mask_in, _ = nrrd.read(mask_in_path)  # int32 dtype

mask_in = mask_in.astype(np.float32)
print("mask_in dtype: {}".format(mask_in.dtype))

print("start cuda rotation")
start_t = time()
mask_out = rotate2dL(mask_in, axis=axis, angle=angle)
# mask_out = shift2dL(mask_in, axis=axis, tx=tx, ty=ty)
end_t = time()
print("cuda time: {}".format(end_t - start_t))

mask_out = mask_out.astype(np.int32)

nrrd.write(mask_out_path, mask_out)
