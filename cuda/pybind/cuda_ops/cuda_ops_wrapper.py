import numpy as np
import math
from . import cuda_ops_mod

H_default = np.array([[1, 0, 0],
                      [0, 1, 0],
                      [0, 0, 1]])
tf_params_default = H_default.flatten()[:-1]


def shift3d(data_in, shift=(0, 0, 0)):
    """
    :param data_in: input 2d layered float32 numpy array
    :param tf_params: numpy array of first 8 values of transformation matrix
    :return: data_out: output 2d layered float32 numpy array
    """
    dtype = data_in.dtype
    shift = tuple(-np.array(shift))
    shape = data_in.shape
    data_in = np.transpose(data_in)
    shape_tp = data_in.shape
    data_in = data_in.reshape(shape)
    data_out = cuda_ops_mod.shift3d(data_in, shift)  # float dtype
    data_out = data_out.reshape(shape_tp)
    data_out = np.transpose(data_out)
    data_out = data_out.astype(dtype)
    return data_out


def tf2dL(data_in, axis=0, tf_params=tf_params_default):
    """
    :param data_in: input 2d layered float32 numpy array
    :param tf_params: numpy array of first 8 values of transformation matrix
    :return: data_out: output 2d layered float32 numpy array
    """
    dtype = data_in.dtype
    shape = data_in.shape
    data_in = np.transpose(data_in)
    shape_tp = data_in.shape
    data_in = data_in.reshape(shape)
    data_out = cuda_ops_mod.transform2dL(data_in, axis, tf_params)  # float dtype
    data_out = data_out.reshape(shape_tp)
    data_out = np.transpose(data_out)
    data_out = data_out.astype(dtype)
    return data_out


# def tf2dL(data_in, axis=0, tf_params=tf_params_default):
#     """
#     :param data_in: input 2d layered float32 numpy array
#     :param tf_params: numpy array of first 8 values of transformation matrix
#     :return: data_out: output 2d layered float32 numpy array
#     """
#     print("test fortran array")
#     # shape = data_in.shape
#     # data_in = np.transpose(data_in)
#     # shape_tp = data_in.shape
#     # data_in = data_in.reshape(shape)
#     data_in = np.asfortranarray(data_in)
#     data_out = cuda_ops_mod.transform2dL(data_in, tf_params)  # float dtype
#     data_out = np.ascontiguousarray(data_out)
#     # data_out = data_out.reshape(shape_tp)
#     # data_out = np.transpose(data_out)
#     return data_out


def rotate2dL(data_in, axis=0, angle=0):
    theta = angle * math.pi / 180
    H = np.array([[math.cos(theta), math.sin(theta), 0],
                  [-math.sin(theta), math.cos(theta), 0],
                  [0, 0, 1]])
    tf_params = H.flatten()[:-1]
    data_out = tf2dL(data_in, axis=axis, tf_params=tf_params)
    return data_out


def shift2dL(data_in, axis=0, tx=0, ty=0):
    H = np.array([[1, 0, -tx],
                  [0, 1, -ty],
                  [0, 0, 1]])
    tf_params = H.flatten()[:-1]
    data_out = tf2dL(data_in, axis=axis, tf_params=tf_params)
    return data_out
