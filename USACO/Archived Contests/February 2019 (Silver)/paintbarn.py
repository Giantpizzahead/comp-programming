"""
USACO 2019 February Contest (Silver)
Problem 2: Painting the Barn
By Giantpizzahead
"""

def main():
    with open("paintbarn.in", 'r') as input:
        num_rects, target_num = map(int, input.readline().strip().split())
        rects = []
        for i in range(num_rects):
            x1, y1, x2, y2 = map(int, input.readline().strip().split())
            rects.append(((x1, y1), (x2, y2)))
    answer = 0
    for x in range(1000):
        for y in range(1000):
            count = 0
            for r in rects:
                if x - r[0][0] >= 0 and r[1][0] - x > 0 and y - r[0][1] >= 0 and r[1][1] - y > 0:
                    count += 1
                if count > target_num:
                    break
            if count == target_num:
                answer += 1
    with open("paintbarn.out", 'w') as output:
        output.write(str(answer))


points = {}


def old_main():
    with open("paintbarn.in", 'r') as input:
        num_rects, target_num = map(int, input.readline().strip().split())
        for i in range(num_rects):
            x1, y1, x2, y2 = map(int, input.readline().strip().split())
            for x in range(x1, x2):
                for y in range(y1, y2):
                    if x*1001+y not in points:
                        points[x*1001+y] = 0
                    points[x*1001+y] += 1
    answer = 0
    for num in points.values():
        if num == target_num:
            answer += 1
    with open("paintbarn.out", 'w') as output:
        output.write(str(answer))


main()
