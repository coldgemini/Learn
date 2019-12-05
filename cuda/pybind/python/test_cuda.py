import numpy as np
from cuda import example

a = np.ones((4, 6))
b = np.ones((4, 6)) * 3
c = example.add_arrays(a, b)

print(c)
