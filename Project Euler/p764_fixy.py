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

N = 10 ** 10
sqrtN = math.floor(math.sqrt(N))
MOD = 10 ** 9
answer = 0

next_prime = [-1 for _ in range(sqrtN+1)]

def gen_sieve():
    for i in range(2, sqrtN+1):
        if round(i**(1/3)) ** 3 == i:
            print('On prime {}'.format(i))
        if next_prime[i] == -1:
            # This is prime
            for j in range(i, sqrtN+1, i):
                next_prime[j] = i

factors = []
primes = {}
prime_num = []
prime_cnt = []
curr_y = 0
square_y = 0

# Generates all factors that are < sqrt(y**4) = y**2.
def gen_factors(x, i):
    global square_y

    for _ in range(prime_cnt[i]+1):
        if i == len(prime_cnt)-1: factors.append(x)
        else: gen_factors(x, i+1)
        x *= prime_num[i]
        if x >= square_y: break

def try_triple(x, y, z):
    if x < 1 or x > N or y < 1 or y > N or z < 1 or z > N:
        raise Exception('Incorrect bounds!', x, y, z)
    elif 16 * (x**2) + y**4 != z**2:
        raise Exception('Incorrect equation!', x, y, z)
    # print('WORKS')

def solve():
    global factors, primes, prime_num, prime_cnt, curr_y, square_y, answer

    # Prime factors
    primes.clear()
    tempY = curr_y
    while tempY > 1:
        p = next_prime[tempY]
        if p not in primes:
            primes[p] = 0
        primes[p] += 1
        tempY //= p
    # Sort with biggest factors first (for pruning)
    primes = dict(sorted(primes.items(), key=lambda item: -item[0]))
    '''
    # Count number of factors
    factor_cnt = 1
    for c in primes.values():
        factor_cnt *= c*4+1
    answer += factor_cnt
    '''

    # Generate all factors < 2*N and raise y to the power of 4
    prime_num = list(primes.keys())
    prime_cnt = list(map(lambda x : x*4, primes.values()))
    factors.clear()
    square_y = curr_y ** 2
    quad_y = curr_y ** 4
    gen_factors(1, 0)

    # Try each factor
    for a in factors:
        b = quad_y // a
        # Generate the triple
        z = (a+b) // 2
        x = abs(b-z) // 4
        # if a >= b: raise Exception('a >= b')
        if z > N or \
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
