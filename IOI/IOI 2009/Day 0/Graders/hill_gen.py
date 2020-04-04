import random

N = 1000
M = 1000
MAX_NUM = 9999999
used = [False for _ in range(MAX_NUM + 1)]
used[0] = True
with open("hill.in", 'w') as fout:
    fout.write(str(N) + ' ' + str(M) + '\n')
    for y in range(M):
        for x in range(N):
            if x != 0: fout.write(' ')
            r = y * N + x + 1
            # r = 0
            # while used[r]: r = random.randint(1, MAX_NUM)
            # used[r] = True
            fout.write("{:<7}".format(r))
        fout.write('\n')
