from time import time
import numpy as np
import nrrd
from cuda_ops import cuda_ops_mod

mask_in_path = '/data2/home/zhouxiangyong/Tmp/cuda_rotate3d_input.nrrd'
mask_out_path = '/data2/home/zhouxiangyong/Tmp/cuda_rotate3d_mask.nrrd'
# mask_in_path = '/data2/home/zhouxiangyong/Data/aorta_seg_data/coronary/scalar_raw/1.2.156.112605.14038013507713.181219050016.3.PAohbDhK1TP7IgRc69IM1h4riK7TNA.nrrd'
# mask_out_path = '/data2/home/zhouxiangyong/Tmp/cuda_rotate3d_data.nrrd'

mask_in, _ = nrrd.read(mask_in_path)  # int32 dtype
print("mask_in dtype: {}".format(mask_in.dtype))
shape = mask_in.shape
print("start transpose")
start_t = time()
mask_in = np.transpose(mask_in)
shape_tp = mask_in.shape
mask_in = mask_in.reshape(shape)

mask_in = mask_in.astype(np.float32)
# mask_in = np.transpose(mask_in)
mask_in = np.ascontiguousarray(mask_in, dtype=np.float32)
print("mask_in dtype: {}".format(mask_in.dtype))

end_t = time()
print("transpose time: {}".format(end_t - start_t))

print("start cuda rotation")
start_t = time()
mask_out = cuda_ops_mod.rotate3d(mask_in, 30)  # float dtype
end_t = time()
print("cuda time: {}".format(end_t - start_t))

print("start transpose")
start_t = time()
mask_out = mask_out.reshape(shape_tp)
mask_out = np.transpose(mask_out)
# mask_out = mask_out * 2
# mask_out = np.transpose(mask_out)
print("mask_out dtype: {}".format(mask_out.dtype))
mask_out = mask_out.astype(np.int32)
print("mask_out dtype: {}".format(mask_out.dtype))
end_t = time()
print("transpose time: {}".format(end_t - start_t))

nrrd.write(mask_out_path, mask_out)
