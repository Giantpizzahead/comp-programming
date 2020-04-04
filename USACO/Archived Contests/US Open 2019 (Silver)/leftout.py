'''
USACO 2019 US Open Contest (Silver)
Problem 1. Left Out
By Giantpizzahead
'''

# Input parsing
with open("leftout.in", 'r') as fin:
    size = int(fin.readline())
    cows = []
    colT = []
    rowT = []
    for i in range(size):
        cow_line = fin.readline().strip()
        new_row = []
        for c in cow_line:
            new_row.append(c)
        cows.append(new_row)
        colT.append(0)
        rowT.append(0)

# Counting number of cows in rows, cols, and in total
countL = 0
countR = 0
for r, cow_row in enumerate(cows):
    for c, cow in enumerate(cow_row):
        if cow == "L":
            countL += 1
            colT[c] += 1
            rowT[r] += 1
        else:
            countR += 1

# Which one to eliminate? L or R?
target = "?"
if countL < countR:
    target = "L"
    countT = countL
else:
    target = "R"
    countT = countR
    # Change all column and row counts to be num of R cows
    for i, c in enumerate(colT):
        colT[i] = size - c
    for i, r in enumerate(rowT):
        rowT[i] = size - r

# Loop; Keep flipping rows / columns of cows until left with one cow
to_flip = "?"
lastT = countT
repeat_count = 0
while countT > 1 and repeat_count <= 20:
    '''
    print(countT)
    for row in cows:
        print(row)
    print(colT)
    print(rowT)
    '''
    # Find the column or row with the highest number of target cows
    max_indexC = 0
    max_indexR = 0
    max_index = 0
    curr_max = 0
    for i, r in enumerate(rowT):
        if r > curr_max:
            max_indexR = i
            curr_max = r
    for i, c in enumerate(colT):
        if c > curr_max:
            max_indexC = i
            curr_max = c
    if rowT[max_indexR] == curr_max:
        to_flip = "R"
    else:
        to_flip = "L"
    # Flip the cows
    if to_flip == "R":
        # Flipping a row / updating counts
        for i, cow in enumerate(cows[max_indexR]):
            if cow == "R":
                cows[max_indexR][i] = "L"
                if target == "R":
                    countT -= 1
                    colT[i] -= 1
                    rowT[max_indexR] -= 1
                else:
                    countT += 1
                    colT[i] += 1
                    rowT[max_indexR] += 1
            else:
                cows[max_indexR][i] = "R"
                if target == "L":
                    countT -= 1
                    colT[i] -= 1
                    rowT[max_indexR] -= 1
                else:
                    countT += 1
                    colT[i] += 1
                    rowT[max_indexR] += 1
    else:
        # Flipping a column / updating counts
        for i, cow_row in enumerate(cows):
            if cow_row[max_indexC] == "R":
                cows[i][max_indexC] = "L"
                if target == "R":
                    countT -= 1
                    colT[max_indexC] -= 1
                    rowT[i] -= 1
                else:
                    countT += 1
                    colT[max_indexC] += 1
                    rowT[i] += 1
            else:
                cows[i][max_indexC] = "R"
                if target == "L":
                    countT -= 1
                    colT[max_indexC] -= 1
                    rowT[i] -= 1
                else:
                    countT += 1
                    colT[max_indexC] += 1
                    rowT[i] += 1
    if countT == lastT:
        repeat_count += 1
    else:
        lastT = countT
        repeat_count = 0

if repeat_count <= 20:
    # Look for the one left out cow
    target = -1
    for i, r in enumerate(rowT):
        if r > 0:
            target = i
            break

    if target == -1:
        answer = "-1"
    else:
        for i, c in enumerate(colT):
            if c > 0:
                answer = str(target + 1) + " " + str(i + 1)
                break
else:
    answer = "-1"

# Output the answer
with open("leftout.out", 'w') as fout:
    fout.write(answer + "\n")
        
