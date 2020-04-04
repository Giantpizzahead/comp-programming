import random

N = 500000
MIN_NUM = 19990
MAX_NUM = 20000
with open("area2.in", 'w') as fout:
    fout.write(str(N) + '\n')
    for i in range(N):
        a = random.randint(MIN_NUM, MAX_NUM)
        b = random.randint(MIN_NUM, MAX_NUM)
        fout.write("{} {}\n".format(a, b))
