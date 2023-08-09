"""
ID: sunnyky1
LANG: PYTHON3
TASK: fc
"""

import math


def almost_equal(x, y):
    """Returns True if x and y are within 10^-6 of each other."""
    return abs(x - y) < 10 ** -6


def ccw(a, b, c):
    """Returns 0 for colinear, 1 for CCW, 2 for CW."""
    result = (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0])
    return 0 if almost_equal(result, 0) else 1 if result > 0 else 2


def dist(a, b):
    return math.hypot(b[0] - a[0], b[1] - a[1])


def get_convex_hull(P):
    """Returns a list of points representing the convex hull of all points in P in CCW order."""
    # Edge case
    if len(P) <= 2:
        return P
    
    # Root at the bottommost point
    root = min(P, key=lambda c: (c[1], c[0]))
    # Remove root from P and sort by angle
    P.remove(root)
    P = [root] + sorted(P, key=lambda c: math.atan2(c[1] - root[1], c[0] - root[0]))

    # Remove unneeded colinear points
    new_P = [root]
    for i in range(1, len(P)):
        if len(new_P) >= 2 and ccw(root, new_P[-1], P[i]) == 0:
            if dist(root, P[i]) > dist(root, new_P[-1]):
                new_P.pop()
            else:
                continue
        new_P.append(P[i])
    P = new_P
    
    # Find the convex hull
    hull = []
    for i in range(len(P)):
        while len(hull) >= 2 and ccw(hull[-2], hull[-1], P[i]) != 1:
            hull.pop()
        hull.append(P[i])
    # print("Root:", root)
    # print("Points:", P)
    # print("Hull:", hull)
    return hull


def main():
    with open("fc.in", "r") as fin:
        N = int(fin.readline())
        P = []
        for _ in range(N):
            x, y = map(float, fin.readline().split())
            P.append((x, y))
    hull = get_convex_hull(P)
    total_dist = sum(dist(hull[i], hull[(i+1) % len(hull)]) for i in range(len(hull)))
    with open("fc.out", "w") as fout:
        fout.write("{:.2f}\n".format(total_dist))


if __name__ == "__main__":
    main()
