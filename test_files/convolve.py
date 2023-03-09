import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import convolve2d

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

size = 10

latticeUse = init(size)
print("Default Lattice")
print(latticeUse)

print("                     ")

k = np.array([[0,1,0],[1,0,1],[0,1,0]])
from scipy import ndimage
convolvedMatrix = convolve2d(latticeUse, k, mode='same')
print("Apply convolution")
print(convoledMatrix)


#use whatever lattice you want for "latticeUse"... 
#latticeXconvolved = np.matmul(latticeUse, convoledMatrix)
energy = 0
for l in range(size):
    for n in range(size):
        energy = energy + convolvedMatrix[l, n] * latticeUse[l, n]

print("Lattice[i, j] * convolved[i, j] for the total energy: ")
print(energy)


plt.imshow(convoledMatrix)
plt.colorbar()
plt.show()


#plt.imshow(latticeXconvolved)
#plt.colorbar()
#plt.show()
