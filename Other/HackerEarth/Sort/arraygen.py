import random

N = 30000
MIN = -9999
MAX = 9999

with open("input.txt", 'w') as fout:
    fout.write(str(N) + '\n')
    fout.write(' '.join([str(random.randint(MIN, MAX)) for _ in range(N)]) + '\n')