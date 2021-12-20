# All my original work, not copied at all :)

import math
import numpy as np
import matplotlib.pyplot as plt


plt.figure()
x = np.linspace(-11, 11, 1000)
y = np.linspace(-11, 11, 1000)
X, Y = np.meshgrid(x,y)
F = 4 * X * X + Y * Y - 100
plt.contour(X,Y,F,[0])


x0 = 1.4
y0 = -9.6
m = (-9.6-10.1) / (1.4-0)
xlines = [0.0, x0]
ylines = [10.1, y0]


def intersection(x0, y0, m):
    disc = m * m * (-(x0 * x0 - 25)) + 2 * m * x0 * y0 - y0 * y0 + 100
    sqdisc = np.sqrt(disc)
    prod = 2 * sqdisc
    x = (m * m * x0 - m * y0 + prod) / (m * m + 4)
    if abs(x - x0) < 1e-7:
        x = (m * m * x0 - m * y0 - prod) / (m * m + 4)
    return (x, m * (x - x0) + y0)


n = int(input("number of lines? "))

result = 0

for i in range(n - 1):
    normalm = y0 / (4 * x0)
    a = np.arctan(m)
    if a < 0:
        a = np.pi + a
    b = np.arctan(normalm)
    if b < 0:
        b = np.pi + b
    theta = b + (b - a)
    m = np.tan(theta)
    x0, y0 = intersection(x0, y0, m)
    xlines.append(x0)
    ylines.append(y0)
    if -0.01 <= x0 <= 0.01 and 9.99 <= y0 <= 10.01:
        result = i + 1
        #break

# print(result)

plt.plot(xlines, ylines, c='r')
plt.show()