"""
APPC student here! :p

1, 0.01
Volume: 1856443.633991197
# points: 86040
120.38792667805012 - 2.5717272148347015e-05·x¹ - 0.012262639415897105·x²

0.5, 0.005
Volume: 1856511.3757476404
# points: 342614
120.38773732586148 - 1.6750788284963418e-05·x¹ - 0.012262439690587603·x²

0.2, 0.002
Volume: 1856529.1639389961
# points: 2132100
114.38844959827087 + 0.22741553644913318·x¹ - 0.014113462619980956·x²

# points: 86040
120.38710622330342 + 3.702775164551313e-05·x¹ - 0.012264915727175542·x² +
3.719155190218811e-08·x³ - 2.0643891350392763e-10·x⁴

Perhaps it's just the starting - ax^2?

0 = y_i + v_yi * t + 0.5at^2
x = v_xi * t
t = x/v_xi

0 = y_i + v_yi * x / v_xi + 0.5a * (x/v_xi)^2
0 = (0.5a/v_xi^2) * x^2 + (v_yi/v_xi) * x + y_i

Assuming the equation only has degree 0 and 2: y = a + bx^2
highest: 90 0 120.38735983690111 2.038735983690112
rightmost: 22.368103712796525 99.08340778978894 0 5.357261279848917

a = 120.38735983690111
b = -0.012262499999999996

y = 120.38735983690111 - 0.012262499999999996x^2
Area by cylindrical shells = 1856532.8455
CORRECT! :)
"""
from functools import cmp_to_key
import numpy as np
import numpy.polynomial.polynomial as poly
import math
import matplotlib.pyplot as plt

h_i = 100
v_i = 20
a = -9.81
angle_int = 5
time_int = 0.1

# Find highest point
high_theta = 90
high_x = 0
high_y = h_i+0.5*(v_i**2)/-a
high_t = v_i/-a
print('highest:', high_theta, high_x, high_y, high_t)
# Find lowest point
def find_x(theta_deg):
  theta = math.radians(theta_deg)
  v_xi = math.cos(theta) * v_i
  v_yi = math.sin(theta) * v_i
  quad_a = 0.5*a/(v_xi)**2
  quad_b = v_yi/v_xi
  quad_c = h_i
  x = (-quad_b - math.sqrt(quad_b**2 - 4*quad_a*quad_c)) / (2*quad_a)
  return x

low = -90
high = 90
while high-low > 10**-18:
  # 3 points
  length = high-low
  x1 = find_x(low+length*1/4)
  x2 = find_x(low+length*2/4)
  x3 = find_x(low+length*3/4)
  if x1 > x2 and x2 >= x3:
    high -= length*2/4
  elif x1 <= x2 and x2 >= x3:
    low += length*1/4
    high -= length*1/4
  else:
    low += length*2/4
right_theta = (low + high) / 2
right_x = find_x(right_theta)
right_y = 0
right_t = right_x / (math.cos(math.radians(right_theta)) * v_i)
print('rightmost:', right_theta, right_x, right_y, right_t)

print('\nEVERYTHING BELOW IS NOT NEEDED TO SOLVE THE PROBLEM\n')

class Point():
  x = 0
  y = 0
  t = 0
  def __init__(self, x, y, t):
    self.x = x
    self.y = y
    self.t = t

N = 0
points = []

theta_deg = -90
while theta_deg <= 90 + angle_int/2:
  theta = math.radians(theta_deg)
  v_xi = math.cos(theta) * v_i
  v_yi = math.sin(theta) * v_i
  t = 0
  while True:
    x = v_xi * t
    y = h_i + v_yi * t + 0.5 * a * (t**2)
    if y < 0: break
    # Only considering points on right side
    if x >= 0:
      point = Point(x, y, t)
      points.append(point)
    t += time_int
  # Add point at the very bottom
  # 0 = h_i + v_yi * t + 0.5 * a * (t**2)
  # a = 0.5*a, b=v_yi, c=h_i
  t = (-v_yi - math.sqrt(v_yi**2 - 2*a*h_i)) / a
  x = v_xi * t
  y = h_i + v_yi * t + 0.5 * a * (t**2)
  point = Point(x, y, t)
  points.append(point)
  theta_deg += angle_int
N = len(points)

# Create convex hull
# CCW function
def ccw(x1, y1, x2, y2, x3, y3):
  res = (x2-x1) * (y3-y1) - (y2-y1) * (x3-x1)
  if res < 0: return -1
  elif res == 0: return 0
  else: return 1

# Move lower-left point to first index
for i in range(1, N):
  if points[1].y < points[0].y or (points[1].y == points[0].y and points[1].x < points[0].x):
    temp_p = points[0]
    points[0] = points[1]
    points[1] = temp_p
hull = [points[0]]

# Offset a bit to make same angles less likely
def pointCompare(a, b):
  angle_a = math.atan2(a.y-points[0].y, a.x-points[0].x)
  angle_b = math.atan2(b.y-points[0].y, b.x-points[0].x)
  if abs(angle_a - angle_b) > 10**-15:
    return -(angle_a - angle_b)
  dist_a = math.hypot(a.y-points[0].y, a.x-points[0].x)
  dist_b = math.hypot(b.y-points[0].y, b.x-points[0].x)
  return dist_a - dist_b
points = [points[0]] + sorted(points[1:], key=cmp_to_key(pointCompare))

# Make the hull
for p in points:
  while len(hull) > 1 and ccw(hull[-2].x, hull[-2].y, hull[-1].x, hull[-1].y, p.x, p.y) == 1:
    hull.pop()
  hull.append(p)

# Get only the points on the curve
curve = []
curve.append(Point(0, h_i+0.5*(v_i**2)/-a, v_i/-a))
for p in hull:
  if p.x <= 10**-10 or p.y <= 10**-10: continue
  curve.append(p)

# Find polynomial fit
coefs = poly.polyfit([p.x for p in curve], [p.y for p in curve], 4)
ffit = poly.Polynomial(coefs)

# Get the volume with cross sections
volume = 0
for i in range(0, len(hull)):
  a = hull[i]
  b = hull[(i+1) % len(hull)]
  ax = (a.x + b.x) / 2
  dy = b.y - a.y
  volume += dy * math.pi * (ax**2)
volume = abs(volume)
print('Volume: {}'.format(volume))
print('# points: {}'.format(N))

# Visualize the explosion
scatter_x = []
scatter_y = []
scatter_c = []
for p in points:
  scatter_x.append(p.x)
  scatter_y.append(p.y)
  scatter_c.append(p.t)
c = 28
for p in curve:
  scatter_x.append(p.x)
  scatter_y.append(p.y)
  scatter_c.append(c)
  # print(p.x, p.y)
  c += 0.1
plt.scatter(scatter_x, scatter_y, c=scatter_c)
# Plot best fit curve
x_new = np.linspace(curve[0].x, curve[-1].x, num=len(curve)*3)
plt.plot(x_new, ffit(x_new), 'r')
# print('\n' + '-'*30 + '\n')
print(ffit)
plt.show()