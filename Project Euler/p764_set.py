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
"""

import math
import time

N = 10 ** 13
sqrtN = math.floor(math.sqrt(N))
MOD = 10 ** 9

next_prime = [-1 for _ in range(sqrtN+1)]
factor_memo = [set() for _ in range(sqrtN+1)]
curr_y = 0
answer = 0

def gen_sieve():
    for i in range(2, sqrtN+1):
        if round(i**(1/3)) ** 3 == i:
            print('On prime {}'.format(i))
        if next_prime[i] == -1:
            # This is prime
            for j in range(i, sqrtN+1, i):
                next_prime[j] = i

def try_triple(x, y, z):
    if x < 1 or x > N or y < 1 or y > N or z < 1 or z > N:
        raise Exception('Incorrect bounds!', x, y, z)
    elif 16 * (x**2) + y**4 != z**2:
        raise Exception('Incorrect equation!', x, y, z)
    # print('WORKS')

def solve():
    global next_prime, factor_memo, curr_y, answer

    # Transition from lower list
    lower_y = curr_y // next_prime[curr_y]
    factors = factor_memo[curr_y].union(factor_memo[lower_y])
    # Add new prime
    for f in factor_memo[lower_y]:
        for _ in range(4):
            f *= next_prime[curr_y]
            if f >= 2*N: break  # Will not be used
            factors.add(f)
    factor_memo[curr_y] = factors
    '''
    # Count number of factors
    factor_cnt = len(factors)
    answer += factor_cnt
    '''

    # Try each factor
    quad_y = curr_y ** 4
    for a in factors:
        b = quad_y // a
        # Generate the triple
        z = (a+b) // 2
        x = abs(b-z) // 4
        if a >= b or \
            z > N or \
            x > N or \
            abs(b-z) % 4 != 0 or \
            (a+b) % 2 != 0 or \
            math.gcd(math.gcd(x, curr_y), z) != 1: continue
        # Try this triple
        # print(a, b, ':', x, curr_y, z)
        # try_triple(x, curr_y, z)
        answer = (answer + x + curr_y + z) % MOD
    # print(curr_y, factors)

def main():
    global N, MOD, curr_y, answer

    # Try all possible values for y
    gen_sieve()
    factor_memo[1].add(1)
    start_time = time.time()
    for curr_y in range(2, sqrtN+1):
        if curr_y % 1000 == 0:
            print('On y {}'.format(curr_y))
        solve()
    end_time = time.time()
    print(answer)
    print('Time = {:.3f} seconds'.format(end_time - start_time))

if __name__ == '__main__':
    main()
