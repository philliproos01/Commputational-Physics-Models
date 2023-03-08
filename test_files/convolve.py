import numpy as np
import matplotlib.pyplot as plt

#h1 = np.random.rand();
#print(h1)
#if h1 <= 0.5:
#    h1 = -1
#elif h1 > 0.51:
#    h1 = 1

#print(h1)

#a = np.array([[1, 2, 0, 0],
#              [5, 3, 0, 4],
#              [0, 0, 0, 7],
#              [9, 3, 0, 0]])
def init(n):
    lattice = 2 * np.random.randint(2, size=(n,n)) - 1
    return lattice

a = init(4)
k = np.array([[0,1,0],[1,0,1],[0,1,0]])
from scipy import ndimage
l = ndimage.convolve(a, k, mode='constant', cval=0.0)
print(l)
plt.imshow(l)
plt.colorbar()
plt.show()
