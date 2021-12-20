a = 1
b = 1
n = 2
while len(str(b)) != 1000:
    a, b = b, a+b
    n += 1

print(n)