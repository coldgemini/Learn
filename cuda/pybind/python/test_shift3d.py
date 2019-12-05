from time import time
import numpy as np
import nrrd
from cuda_ops import cuda_ops_mod

# mask_in_path = '/data2/home/zhouxiangyong/Tmp/cuda_rotate3d_input.nrrd'
mask_out_path = '/data2/home/zhouxiangyong/Tmp/cuda_shift3d_mask.nrrd'
# mask_in_path = '/data2/home/zhouxiangyong/Data/aorta_seg_data/coronary/scalar_raw/1.2.156.112605.14038013507713.181219050016.3.PAohbDhK1TP7IgRc69IM1h4riK7TNA.nrrd'
# mask_out_path = '/data2/home/zhouxiangyong/Tmp/cuda_rotate3d_data.nrrd'

# mask_in, _ = nrrd.read(mask_in_path)  # int32 dtype
# print("mask_in dtype: {}".format(mask_in.dtype))
# mask_in = mask_in.astype(np.float32)
# mask_in = np.transpose(mask_in)
# mask_in = np.ascontiguousarray(mask_in, dtype=np.float32)
# print("mask_in dtype: {}".format(mask_in.dtype))
dimX, dimY, dimZ = 4, 3, 2
mask_in = np.zeros((dimX, dimY, dimZ), dtype=np.int32)
# mask_in = np.zeros((3, 3, 3), dtype=np.float32)
count = 0
for i in range(dimX):
    for j in range(dimY):
        for k in range(dimZ):
            # mask_in[i][j][k] = (i + 1) * (j + 1) * (k + 1)
            mask_in[i][j][k] = count
            count = count + 1
            # if i == j and j == k:
            #     mask_in[i][j][k] = 8
# mask_in += 1
print(mask_in)
print("mask_in flatten")
print(mask_in.flatten())
print("mask_in transposed flatten")
print(np.transpose(mask_in).flatten())
# mask_in = np.transpose(mask_in)
mask_in = mask_in.astype(np.float32)

print("start cuda rotation")
start_t = time()
# mask_out = mask_in
mask_out = cuda_ops_mod.shift3d(mask_in)  # float dtype
# mask_out = np.transpose(mask_out)
# mask_out = mask_out * 2
# mask_out = np.transpose(mask_out)
print("mask_out dtype: {}".format(mask_out.dtype))
mask_out = mask_out.astype(np.int32)
print("mask_out dtype: {}".format(mask_out.dtype))
end_t = time()
print("cuda time: {}".format(end_t - start_t))

print(mask_out)
print(mask_out.flatten())
# print(mask_out.flatten().reshape(dimX, dimY, dimZ))
print(mask_out.flatten().reshape(dimZ, dimY, dimX))
# print(np.transpose(mask_out))

# nrrd.write(mask_out_path, mask_out)
