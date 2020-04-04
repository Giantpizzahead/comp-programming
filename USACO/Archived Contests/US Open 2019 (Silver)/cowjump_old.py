def check_intersection(seg1a, seg1b, seg2a, seg2b):
    '''
    Checks if two line segments intersect using a very complex formula.
    Takes in 4 tuples as input (the 4 endpoints).
    Passes all the test cases I gave it.
    '''
    # Very complex formula :(
    if seg1b[0] - seg1a[0] == 0:
        slope1 = 9999999
        part2 = 0
    else:
        slope1 = (seg1b[1] - seg1a[1]) / (seg1b[0] - seg1a[0])
        part2 = (seg1b[0] * seg1a[1] - seg1b[1] * seg1a[0]) / (seg1b[0] - seg1a[0])
    if seg2b[0] - seg2a[0] == 0:
        slope2 = 9999999
        part1 = 0
    else:
        slope2 = (seg2b[1] - seg2a[1]) / (seg2b[0] - seg2a[0])
        part1 = (seg2b[0] * seg2a[1] - seg2b[1] * seg2a[0]) / (seg2b[0] - seg2a[0])
    part3 = slope1 - slope2
    if part3 == 0:
        # Special case: Lines are parallel
        # Check if lines intersect using special code
        dist = abs(seg1a[1] - seg1b[1]) + 0.001
        if slope1 == 9999999 and seg1a[0] == seg2a[0] and (
           (abs(seg1a[1] - seg2a[1]) <= dist and abs(seg1b[1] - seg2a[1]) <= dist) or
           (abs(seg1a[1] - seg2b[1]) <= dist and abs(seg1b[1] - seg2b[1]) <= dist)):
            return True
        dist = abs(seg1a[0] - seg1b[0]) + 0.001
        if slope1 == 0 and seg1a[1] == seg2a[1] and (
           (abs(seg1a[0] - seg2a[0]) <= dist and abs(seg1b[0] - seg2a[0]) <= dist) or
           (abs(seg1a[0] - seg2b[0]) <= dist and abs(seg1b[0] - seg2b[0]) <= dist)):
            return True
        return False
    intersectx = (part1 - part2) / part3
    # print(intersectx)
    # Check if x intersection point is within the endpoint x's
    # Decide whether the lines intersect based on that
    # 0.001 is for rounding errors caused by float division
    dist = abs(seg1a[0] - seg1b[0]) + 0.001
    if not (abs(seg1a[0] - intersectx) <= dist and abs(seg1b[0] - intersectx) <= dist):
        return False
    dist = abs(seg2a[0] - seg2b[0]) + 0.001
    if not (abs(seg2a[0] - intersectx) <= dist and abs(seg2b[0] - intersectx) <= dist):
        return False
    return True

# Input parsing
with open("cowjump.in", 'r') as fin:
    num_segments = int(fin.readline())
    segments = []
    for i in range(num_segments):
        x1, y1, x2, y2 = map(int, fin.readline().split())
        segments.append(((x1, y1), (x2, y2)))

# Check if segments intersect
index_against = []
check_against = []
intersection = False
found_intersection = -1
answer = -1
for i1, s1 in enumerate(segments):
    #print(i1)
    #print(check_against)
    for i2, s2 in enumerate(check_against):
        if check_intersection(s1[0], s1[1], s2[0], s2[1]):
            # print(i1, "and", i2, "intersect")
            if found_intersection != -1:
                answer = i1
                found_intersection = -1
                break
            found_intersection = i2
    if found_intersection != -1:
        if not intersection:
            check_against = []
            check_against.append(segments[found_intersection])
            index_against.append(found_intersection)
            check_against.append(s1)
            index_against.append(i1)
            intersection = True
            found_intersection = -1
        else:
            answer = index_against[i2]
    elif not intersection:
        check_against.append(s1)
    if answer != -1:
        break

if answer == -1:
    raise Exception("what")

with open("cowjump.out", 'w') as fout:
    fout.write(str(answer + 1) + "\n")
