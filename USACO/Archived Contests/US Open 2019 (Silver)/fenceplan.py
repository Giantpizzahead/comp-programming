'''
USACO 2019 US Open Contest, Silver
Problem 3. Fence Planning
By Giantpizzahead
'''

# Input parsing
with open("fenceplan.in", 'r') as fin:
    num_cows, num_conn = map(int, fin.readline().split())
    cows = []
    cow_checked = []
    conns = {}
    for i in range(num_cows):
        cows.append(tuple(map(int, fin.readline().strip().split())))
        cow_checked.append(0)
        conns[i] = []
    for i in range(num_conn):
        cow1, cow2 = map(int, fin.readline().strip().split())
        conns[min(cow1-1, cow2-1)].append(max(cow1-1, cow2-1))
        conns[max(cow1-1, cow2-1)].append(min(cow1-1, cow2-1))

# Spider through connections to find moo networks
min_perimeter = 999999999999999
for i in range(num_cows):
    if cow_checked[i] == 0:
        # print("Checking cow", i)
        cow_checked[i] = 1
        cows_to_check = [i]
        curr_minx = cows[i][0]
        curr_maxx = cows[i][0]
        curr_miny = cows[i][1]
        curr_maxy = cows[i][1]
        while cows_to_check:
            cc = cows_to_check[0]
            cows_to_check.pop(0)
            if cows[cc][0] < curr_minx: curr_minx = cows[cc][0]
            elif cows[cc][0] > curr_maxx: curr_maxx = cows[cc][0]
            if cows[cc][1] < curr_miny: curr_miny = cows[cc][1]
            elif cows[cc][1] > curr_maxy: curr_maxy = cows[cc][1]
            for cow in conns[cc]:
                if cow_checked[cow] == 0:
                    # print("Spidered to cow", cow)
                    cows_to_check.append(cow)
                    cow_checked[cow] = 1
        # Check perimeter of moo network
        perimeter = (curr_maxx - curr_minx) * 2 + (curr_maxy - curr_miny) * 2
        if curr_maxx == curr_minx:
            perimeter = curr_maxy - curr_miny
        if curr_maxy == curr_miny:
            perimeter = curr_maxx - curr_minx
        if perimeter < min_perimeter: min_perimeter = perimeter

with open("fenceplan.out", 'w') as fout:
    fout.write(str(min_perimeter) + "\n")
        
