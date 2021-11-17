import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import random

fin = open('e_test.out', 'r')

n = int(fin.readline())
arr = np.zeros((n, n))
for i in range(n):
    a = list(map(int, fin.readline().split()))
    for j in range(n):
        arr[i][j] = int(a[j])

imgplot = plt.imshow(arr)
plt.show()
