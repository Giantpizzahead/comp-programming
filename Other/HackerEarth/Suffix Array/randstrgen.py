import random

N = 200000
ALPHABET_SIZE = 9
with open("..\suffixarr.in", 'w') as fout:
    [fout.write(chr(random.randrange(ord('a'), ord('a') + ALPHABET_SIZE))) for _ in range(N)]
    fout.write('\n')