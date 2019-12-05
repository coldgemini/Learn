from time import time
import numpy as np
# import nrrd
import math
from cuda_ops import cuda_ops_mod

# mask_in_path = '/data2/home/zhouxiangyong/Tmp/cuda_rotate3d_input.nrrd'
mask_out_path = '/data2/home/zhouxiangyong/Tmp/cuda_rotate3d_mask.nrrd'
# mask_in_path = '/data2/home/zhouxiangyong/Data/aorta_seg_data/coronary/scalar_raw/1.2.156.112605.14038013507713.181219050016.3.PAohbDhK1TP7IgRc69IM1h4riK7TNA.nrrd'
# mask_out_path = '/data2/home/zhouxiangyong/Tmp/cuda_rotate3d_data.nrrd'

# tf_params = np.array([0, 1, 2, 3, 4, 5, 6, 7])
# tf_params = np.array([1, 0, 0,
#                       0, 1, 0,
#                       0, 0])
angle = 90
theta = angle * math.pi / 180
tf_params = np.array([math.cos(theta), -math.sin(theta), 0,
                      math.sin(theta), math.cos(theta), 0,
                      0, 0])

dimX, dimY, dimZ = 3, 3, 1
mask_in = np.zeros((dimX, dimY, dimZ), dtype=np.int32)
# mask_in = np.zeros((3, 3, 3), dtype=np.float32)
count = 0
for i in range(dimX):
    for j in range(dimY):
        for k in range(dimZ):
            # mask_in[i][j][k] = (i + 1) * (j + 1) * (k + 1)
            mask_in[i][j][k] = count
            # mask_in[i][j][k] = 8
            count = count + 1

# mask_in, _ = nrrd.read(mask_in_path)  # int32 dtype

print("mask_in original")
print("mask_in dtype: {}".format(mask_in.dtype))
print("mask_in flatten")
print(mask_in.flatten())
print("mask_in shape: {}".format(mask_in.shape))
print(mask_in)
print("display in ZYX")
print(np.transpose(mask_in))

shape = mask_in.shape
mask_in = np.transpose(mask_in)
shape_tp = mask_in.shape
mask_in = mask_in.reshape(shape)

print("mask_in transposed")
print("mask_in flatten")
print(mask_in.flatten())
print("mask_in shape: {}".format(mask_in.shape))
print(mask_in)
print("display in ZYX")
print(np.transpose(mask_in))
# print(np.transpose(mask_in))
# print("mask_in transposed flatten")
# print(np.transpose(mask_in).flatten())

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

# print("mask_out dtype: {}".format(mask_out.dtype))

mask_out = mask_out.reshape(shape_tp)
print("mask_out origoutal")
print("mask_out dtype: {}".format(mask_out.dtype))
print("mask_out flatten")
print(mask_out.flatten())
print("mask_out shape: {}".format(mask_out.shape))
print(mask_out)
print("display out ZYX")
print(np.transpose(mask_out).reshape(shape_tp))
# print(mask_out.flatten())
# mask_out = mask_out.astype(np.int32)
# print("mask_out dtype: {}".format(mask_out.dtype))

# print(mask_out.reshape(shape))
# print(mask_out.flatten())
mask_out = np.transpose(mask_out)
print("mask_out transposed")
print("mask_out flatten")
print(mask_out.flatten())
print("mask_out shape: {}".format(mask_out.shape))
print(mask_out)
print("display in ZYX")
print(np.transpose(mask_out).reshape(shape_tp))
# mask_out = mask_out.reshape(shape_tp)
# mask_out = np.transpose(mask_out)
# mask_out = mask_out * 2
# mask_out = np.transpose(mask_out)

# print(np.transpose(mask_out))
# print(mask_out.flatten())
# print(mask_out.flatten())
# print(mask_out.flatten().reshape(dimX, dimY, dimZ))
# print(mask_out.flatten().reshape(dimZ, dimY, dimX))

# nrrd.write(mask_out_path, mask_out)
