import itertools

products = set()
for perm in itertools.permutations(str(x) for x in range(1, 10)):
    for i in range(7):
        for j in range(i+1, 8):
            a = int(''.join(perm[:i+1]))
            b = int(''.join(perm[i+1:j+1]))
            c = int(''.join(perm[j+1:]))
            if a * b == c:
                products.add(int(c))

print(products)
print(sum(products))
