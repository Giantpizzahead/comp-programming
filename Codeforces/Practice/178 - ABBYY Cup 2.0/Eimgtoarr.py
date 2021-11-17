import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import random

img = mpimg.imread('esample3.png')
# img = mpimg.imread('esample1.png')

n = min(len(img), len(img[0]))
arr = np.zeros((n, n))
for i in range(n):
    for j in range(n):
        color = sum(img[i][j])
        if color < 2.2:
            arr[i][j] = 1
        if random.random() < 0.18:
            arr[i][j] = 1 - arr[i][j]

with open('e_test.in', 'w') as fin:
    fin.write(str(n) + '\n')
    for i in range(n):
        for j in range(n):
            fin.write(str(round(arr[i][j])))
            if j != n-1: fin.write(' ')
        fin.write('\n')

imgplot = plt.imshow(arr)
plt.show()
