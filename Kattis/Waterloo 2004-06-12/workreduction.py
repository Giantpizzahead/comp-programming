# https://open.kattis.com/problems/reduction

import re

C = int(input())
for c in range(C):
    print('Case', c+1)
    N, M, L = map(int, input().split())
    A = []
    for i in range(L):
        name, a, b = re.compile('(.*):(.*),(.*)').match(input()).groups()
        a = int(a)
        b = int(b)
        # print(name, a, b)
        best_c = a * (N-M)
        curr_n = N
        curr_c = 0
        while curr_n // 2 >= M:
            curr_n //= 2
            curr_c += b
            best_c = min(curr_c + a * (curr_n-M), best_c)
        A.append({'name': name, 'cost': best_c})
    A = sorted(A, key=lambda x: (x['cost'], x['name']))
    for x in A:
        print(x['name'], x['cost'])
