from time import time
import numpy as np
import nrrd
import math
from cuda_ops import cuda_ops_mod

mask_in_path = '/data2/home/zhouxiangyong/Tmp/cuda_rotate3d_input.nrrd'
mask_out_path = '/data2/home/zhouxiangyong/Tmp/cuda_tf2dL_mask.nrrd'
# mask_in_path = '/data2/home/zhouxiangyong/Data/aorta_seg_data/coronary/scalar_raw/1.2.156.112605.14038013507713.181219050016.3.PAohbDhK1TP7IgRc69IM1h4riK7TNA.nrrd'
# mask_out_path = '/data2/home/zhouxiangyong/Tmp/cuda_tf2dL_data.nrrd'

angle = 90
# tx, ty = 256, 256
# tx, ty = 256, 256
tx, ty = 0, 0
theta = angle * math.pi / 180
Hinv_trans = np.array([[1, 0, -tx],
                       [0, 1, -ty],
                       [0, 0, 1]])

Hinv_rotate = np.array([[math.cos(theta), math.sin(theta), 0],
                        [-math.sin(theta), math.cos(theta), 0],
                        [0, 0, 1]])
# Htot = np.matmul(Hinv_rotate, Hinv_trans)
Htot = np.matmul(Hinv_trans, Hinv_rotate)
print(Htot)
print(Htot.flatten())

tf_params = Htot.flatten()[:-1]
print(tf_params)

mask_in, _ = nrrd.read(mask_in_path)  # int32 dtype

shape = mask_in.shape
mask_in = np.transpose(mask_in)
shape_tp = mask_in.shape
mask_in = mask_in.reshape(shape)

mask_in = mask_in.astype(np.float32)
mask_in = np.ascontiguousarray(mask_in, dtype=np.float32)
print("mask_in dtype: {}".format(mask_in.dtype))

print("start cuda rotation")
start_t = time()
mask_out = cuda_ops_mod.transform2dL(mask_in, tf_params)  # float dtype
end_t = time()
print("cuda time: {}".format(end_t - start_t))
print("shape: {}".format(shape))
print("shape_tp: {}".format(shape_tp))

mask_out = mask_out.reshape(shape_tp)
mask_out = np.transpose(mask_out)

nrrd.write(mask_out_path, mask_out)
