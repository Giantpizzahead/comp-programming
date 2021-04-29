# https://open.kattis.com/problems/expandingrods

'''
r = radius, a = angle in radians, x = displacement

L' = r*a
(r-x)^2 + (L/2)^2 = r^2
sin(a/2) = L/(2r)

x^2 - 2rx + L^2/4 = 0
x(2r-x) = L^2/4
ra = L'

If x were fixed...
2rx = x^2 + L^2/4
r = (x^2 + L^2/4) / 2x
a = L'/r
'''

import math

def check(L, n, C, x):
    Lp = (1 + n * C) * L
    r = (x**2 + L**2/4) / (2*x)
    a = Lp / r
    left = math.sin(a/2)
    right = L / (2*r)
    # print(x, '=', left, right)
    return left > right

def solve(L, n, C):
    low = 0
    high = L / 2
    while high - low > 10 ** -4:
        mid = (low + high) / 2
        if check(L, n, C, mid):
            low = mid
        else:
            high = mid
    return (low + high) / 2

while True:
    L, n, C = map(float, input().split())
    if L == -1: break
    print('{:.9f}'.format(solve(L, n, C)))
