with open("walk.in", 'r') as fin:
    num_cows, num_groups = map(int, fin.readline().split())

# Solve the problem by finding the maximum cow that is left out of the main group
max_cow = num_groups - 1

# Then, find the distance that that cow and the max cow in the group are willing to walk
dist = (2019201913 * max_cow + 2019201949 * num_cows) % 2019201997

# Finally, output that distance
with open("walk.out", 'w') as fout:
    fout.write(str(dist) + "\n")