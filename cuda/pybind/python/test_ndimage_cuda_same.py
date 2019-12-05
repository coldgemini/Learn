from time import time
import numpy as np
import nrrd
import scipy.ndimage as ndimage
from cuda_ops.cuda_ops_wrapper import rotate2dL, shift2dL, shift3d

mask_in_path = '/data2/home/zhouxiangyong/Tmp/cuda_rotate3d_input.nrrd'
cuda_mask_out_path = '/data2/home/zhouxiangyong/Tmp/cuda_tf2dL_mask.nrrd'
ndimage_mask_out_path = '/data2/home/zhouxiangyong/Tmp/ndimage_tf2dL_mask.nrrd'

angle = 45
# tx, ty = 256, 256
tx, ty = 100, 100
# tx, ty = 0, 0
cuda_axis = 2
ndimage_axis = (0, 1)
shift = (100, 100, 100)

########################################
# read data
########################################
mask_in, _ = nrrd.read(mask_in_path)  # int32 dtype
mask_in = mask_in.astype(np.float32)
print("mask_in dtype: {}".format(mask_in.dtype))

########################################
# cuda ops
########################################
print("start cuda ops")
start_t = time()
# mask_out = rotate2dL(mask_in, axis=cuda_axis, angle=angle)
# mask_out = shift2dL(mask_in, axis=cuda_axis, tx=tx, ty=ty)
mask_out = shift3d(mask_in, shift=shift)
end_t = time()
print("cuda time: {}".format(end_t - start_t))

mask_out = mask_out.astype(np.int32)
nrrd.write(cuda_mask_out_path, mask_out)

########################################
#  ndimage ops
########################################
print("start ndimage ops")
start_t = time()
# mask_out = ndimage.rotate(mask_in, angle=angle, axes=ndimage_axis,
#                           reshape=False, order=1, mode='nearest', cval=0)
mask_out = ndimage.shift(mask_in, shift=shift, order=1, mode='nearest', cval=0)
end_t = time()
print("ndimage time: {}".format(end_t - start_t))

mask_out = mask_out.astype(np.int32)
nrrd.write(ndimage_mask_out_path, mask_out)
