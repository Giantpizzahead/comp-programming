"""
USACO 2019 January Contest (Silver)
Problem 3: Mountain View
By Giantpizzahead

Done after the contest. Doing the problem again to learn a better way to do it.
Also for practice.
"""

DEBUG = False


def main():
    segments, points = parse_input()
    points = sorted(points, key=sort_point)
    answer = mountain_sweep(segments, points)
    if DEBUG:
        print(segments)
        print(points)
        print(answer)
    with open("mountains.out", 'w') as fout:
        fout.write(str(answer) + "\n")


def mountain_sweep(segments, points):
    # point[0] = X coordinate
    # point[1] = Start or end point
    # point[2] = Segment ID
    num_not_covered = 0
    tracking = {}
    max_x = -9999999999
    started_this_x = []
    last_x = -9999999999
    for point in points:
        if point[1] == "S":
            # Find the minimum x needed to not be covered
            needed_x = max_x
            if segments[point[2]][1] > max_x:
                max_x = segments[point[2]][1]
            tracking[point[2]] = needed_x
            if DEBUG:
                print("Minimum x needed for ID {}: {}".format(point[2], needed_x))
            if point[0] == last_x:
                # Special case: Two mountains started at the same time
                # Adjust earlier evaluated mountain's needed x value
                for s in started_this_x:
                    tracking[s] = max(tracking[s], segments[point[2]][1])
                    if DEBUG:
                        print("Minimum x for previous adjusted: ID {} now {}".format(s, tracking[s]))
            else:
                started_this_x.clear()
                last_x = point[0]
            started_this_x.append(point[2])
        else:
            if point[0] > tracking[point[2]]:
                num_not_covered += 1
            elif DEBUG:
                print("Mountain {} covered; didn't reach needed x of {}".format(point[2], tracking[point[2]]))
            tracking.pop(point[2])
    return num_not_covered



def sort_point(point):
    if point[1] == "S":
        return point[0] + 0.1
    else:
        return point[0]


def parse_input():
    with open("mountains.in", 'r') as fin:
        num_mountains = int(fin.readline().strip())
        segments = []
        points = []
        for i in range(num_mountains):
            x, y = [int(n) for n in fin.readline().strip().split()]
            startx = x - y
            endx = x + y
            segments.append((startx, endx))
            points.append((startx, "S", i))
            points.append((endx, "E", i))
    return segments, points


if __name__ == "__main__":
    main()
