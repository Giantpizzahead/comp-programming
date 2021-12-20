def get_proper_divisors(n):
    if n == 1:
        return []
    divisors = [1]
    # Check all divisors
    x = 2
    while x*x < n:
        if n % x == 0:
            divisors.append(x)
            divisors.append(n//x)
        x += 1
    # Square number
    if x*x == n:
        divisors.append(x)
    return divisors

N = 28123
abundant = []
for n in range(1, N+1):
    if sum(get_proper_divisors(n)) > n:
        abundant.append(n)

can_be_written = [False for _ in range(N+1)]
for a in abundant:
    for b in abundant:
        c = a+b
        if c <= N:
            can_be_written[a+b] = True

answer = sum(x if not can_be_written[x] else 0 for x in range(N+1))
print(answer)
