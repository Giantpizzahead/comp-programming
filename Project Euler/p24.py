from itertools import permutations

perms = permutations(range(10))
N = 1000000
for i in range(N-1):
    perms.__next__()
print(''.join(str(x) for x in perms.__next__()))
