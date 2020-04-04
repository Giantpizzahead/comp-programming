'''
USACO 2019 US Open Contest, Silver
Problem 2. Cow Steeplechase II
By Giantpizzahead
'''

def sort_help(x):
    value = x[0][0]
    if x[1] == "E": value += 0.1
    return value

# Input parsing
with open("cowjump.in", 'r') as fin:
    num_segments = int(fin.readline())
    points = []
    slopes = []
    coords = []
    for i in range(num_segments):
        x1, y1, x2, y2 = map(int, fin.readline().strip().split())
        if x2 - x1 == 0:
            slopes.append(999999999)
            coords.append((x1, y1))
            points.append(((x1, y1), "S", i))
            points.append(((x2, y2), "E", i))
        else:
            slopes.append((y2 - y1) / (x2 - x1))
            if x1 < x2:
                coords.append((x1, y1))
                points.append(((x1, y1), "S", i))
                points.append(((x2, y2), "E", i))
            else:
                coords.append((x2, y2))
                points.append(((x2, y2), "S", i))
                points.append(((x1, y1), "E", i))

# Sort points by x coordinate
points = sorted(points, key=lambda x: sort_help(x))
print(points)
print(slopes)

# Loop through all start / end points
first_intersect = False
still_in_first = False
possible_ids = []
track_ids = []
answer = -1
for p in points:
    #print("On point", p)
    print("Tracking:", track_ids)
    if p[1] == "S":
        if not first_intersect:
            print("Adding id", p[2])
            track_ids.append(p[2])
    else:
        for ti, t in enumerate(track_ids):
            if t == p[2]:
                saved_index = ti
                continue
            # Get current location of tracked segment
            curr_loc = coords[t][1] + (p[0][0] - coords[t][0]) * slopes[t]
            # If y value has crossed the segment being tested, intersection has occurred
            intersection_test = not ((coords[t][1] > coords[p[2]][1] + (coords[t][0] - coords[p[2]][0]) * slopes[p[2]] - 0.001) == (curr_loc > p[0][1] - 0.001))
            if slopes[p[2]] == 999999999:
                # Special test for vertical lines
                intersection_test = (curr_loc - 0.001 <= max(p[0][1], coords[p[2]][1] and curr_loc + 0.001 >= min(p[0][1], coords[p[2]][1])))
            if intersection_test:
                print("Intersection detected:", p[2], t)
                if not first_intersect:
                    first_intersect = True
                    still_in_first = True
                    possible_ids.append(p[2])
                    possible_ids.append(t)
                elif still_in_first:
                    answer = p[2]
                    break
                else:
                    answer = track_ids[0]
                    break
        if not first_intersect:
            print("Popping id", track_ids[saved_index])
            track_ids.pop(saved_index)
        elif still_in_first:
            track_ids = [possible_ids[1]]
    still_in_first = False
    if answer != -1: break

# If two possible ids still exist, choose the one with the least id number
if answer == -1 and possible_ids:
    answer = min(possible_ids)

print("Answer:", answer + 1)

with open("cowjump.out", 'w') as fout:
    fout.write(str(answer + 1) + "\n")
