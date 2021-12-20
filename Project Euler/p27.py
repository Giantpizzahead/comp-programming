P = 100000
prime = [True for _ in range(P)]
for x in range(2, P):
    if prime[x]:
        for j in range(x+x, P, x):
            prime[j] = False

def is_prime(n):
    return False if n < 2 else prime[n]

def test_quadratic(a, b):
    n = 0
    while True:
        x = n**2 + a*n + b
        if not is_prime(x):
            break
        n += 1
    return n

N = 1000
best_cnt = 0
answer = None
for a in range(-N+1, N):
    for b in range(-N, N+1):
        cnt = test_quadratic(a, b)
        if cnt > best_cnt:
            answer = (a, b)
            best_cnt = cnt

print('Answer:', answer[0]*answer[1])
print(answer, best_cnt)
