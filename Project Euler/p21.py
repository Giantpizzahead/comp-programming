import math

def get_divisors(n):
    divisors = []
    x = 1
    while x*x < n:
        if n % x == 0:
            divisors.append(x)
            divisors.append(n // x)
        x += 1
    if x*x == n:
        divisors.append(x)
    return divisors

N = 10000
max_divisor_sum = 0
x = 1
n_to_divisor_sum = {}
while x <= max(N, max_divisor_sum):
    divisor_sum = sum(get_divisors(x)) - x
    n_to_divisor_sum[x] = divisor_sum
    if x <= N:
        max_divisor_sum = max(divisor_sum, max_divisor_sum)
    x += 1

print(N, max_divisor_sum)
num_amicable = 0
amicable = []
for n in range(1, N+1):
    d = n_to_divisor_sum[n]
    if d != n and d in n_to_divisor_sum and n_to_divisor_sum[d] == n:
        num_amicable += n
        amicable.append(n)
print(amicable)
print('Answer:', num_amicable)