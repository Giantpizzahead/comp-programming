# https://open.kattis.com/problems/threepowers

def solve(N):
    N -= 1
    nums = []
    curr = 1
    while N > 0:
        if N % 2 == 1:
            nums.append(str(curr))
        N //= 2
        curr *= 3
    print('{ ' + ', '.join(nums) + ' }')

while True:
    N = int(input())
    if N == 0: break
    solve(N)
