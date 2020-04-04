import random

NUM_CASES = 10
N = 100000
MAX_NUM = 10000000000000
M = 100000
CHANCE_SQRT = 0.9

with open("gss4.in", 'w') as fout:
    for i in range(NUM_CASES):
        fout.write(str(N) + '\n')
        fout.write(' '.join([str(random.randint(1, MAX_NUM)) for _ in range(N)]) + '\n')
        fout.write(str(M) + '\n')
        for j in range(M):
            a = random.randint(1, N)
            b = random.randint(1, N)
            if (random.random() < CHANCE_SQRT):
                fout.write(' '.join(['0', str(min(a, b)), str(max(a, b))]) + '\n')
            else:
                fout.write(' '.join(['1', str(min(a, b)), str(max(a, b))]) + '\n')
