"""
16x^2 + y^4 = z^2
y^4 = z^2 - 16x^2
y^4 = (z-4x)(z+4x)

16x^2 = (z-y^2)(z+y^2)

For each value of y:
Find prime factorization of y and y^4
Use y^4 primes to find all factors

z^2 > y^4, so z > y^2
x varies a lot

Two factors must both be < 2*N and average must be <= N, otherwise z would exceed N which is not allowed

With the above limitation, x limit is not an issue

Only factors that are 8n apart might work

gcd(x, y, z) = 1

Could probably get O(# factors) impl per y
O(sum(# factors for all y^4))

For 10^16, sum(# factors for all y^4) = 166,051,374,751

10^9
258133745
Time = 2.786 seconds
Unique factors = 707561

10^10
51601717
Time = 12.083 seconds
Unique factors = 2690711

10^11
218092193
Time = 49.568 seconds
Unique factors = 10115276

10^12
397047378
Time = 199.458 seconds
Unique factors = 37641403

10^16 expected = 7262220944
"""

import math
import time

N = 10 ** 7
sqrtN = math.floor(math.sqrt(N))
MOD = 10 ** 9
answer = 0

primes = []

# Generates all primes up to sqrtN
def gen_primes():
    sieve = [True for _ in range(sqrtN+1)]
    for i in range(2, sqrtN+1):
        if round(i**(1/3)) ** 3 == i:
            print('On prime {}'.format(i))
        if sieve[i]:
            # This is prime
            primes.append(i)
            for j in range(i, sqrtN+1, i):
                sieve[j] = False

# Generates all factors that could occur with a valid y**4
def gen_factors(curr_x, curr_y, curr_i):
    # Next prime factor to use (must use it)
    for i in range(curr_i, len(primes)):
        p = primes[i]
        x = curr_x
        y = curr_y
        # Early cutoff
        if y * p > sqrtN or x * p >= 2*N: break
        # Factors of y
        while True:
            y *= p
            if y > sqrtN: break
            # Factors of y**4
            for _ in range(4):
                x *= p
                if x >= 2*N: break
                gen_factors(x, y, i+1)
    # Try this factor
    try_factor(curr_x, curr_y)

factor_cnt = 0

def try_factor(a, base_y):
    global answer, factor_cnt
    factor_cnt += 1
    if factor_cnt % 10000 == 0:
        print('On factor {}'.format(factor_cnt))
    # Try each y
    for y in range(base_y, sqrtN+1, base_y):
        b = (y**4) // a
        # Generate the triple
        z = (a+b) // 2
        x = abs(b-z) // 4
        # if a >= b: raise Exception('a >= b')
        if a >= b or \
            z > N or \
            x > N or \
            abs(b-z) % 4 != 0 or \
            (a+b) % 2 != 0 or \
            math.gcd(math.gcd(x, y), z) != 1: continue
        # Try this triple
        # print(a, b, ':', x, y, z)
        # try_triple(x, y, z)
        answer = (answer + x + y + z) % MOD

def try_triple(x, y, z):
    if x < 1 or x > N or y < 1 or y > N or z < 1 or z > N:
        raise Exception('Incorrect bounds!', x, y, z)
    elif 16 * (x**2) + y**4 != z**2:
        raise Exception('Incorrect equation!', x, y, z)
    # print('WORKS')

def main():
    # Try all possible factors
    gen_primes()
    start_time = time.time()
    gen_factors(1, 1, 0)
    end_time = time.time()
    print(answer)
    print('Time = {:.3f} seconds'.format(end_time - start_time))
    print('Unique factors = {}'.format(factor_cnt))

if __name__ == '__main__':
    main()
