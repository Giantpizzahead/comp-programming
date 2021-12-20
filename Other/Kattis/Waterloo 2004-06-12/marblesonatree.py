# https://open.kattis.com/problems/marblestree

answer = 0

def dfs(n, adj, M):
    global answer
    curr_m = M[n]
    to_use = 1
    for e in adj[n]:
        ret = dfs(e, adj, M)
        if ret < 0:
            # Push marbles down
            to_use -= ret
        elif ret > 0:
            # More marbles up
            curr_m += ret
    # Use as many marbles as possible
    used = min(to_use, curr_m)
    curr_m -= used
    to_use -= used
    if curr_m > 0:
        # Remaining go up
        answer += curr_m
        # print(n, 'extra', curr_m)
        return curr_m
    else:
        # Look for marbles
        answer += to_use
        # print(n, 'look', to_use)
        return -to_use

def solve():
    N = int(input())
    if N == 0: return False
    adj = [[] for _ in range(N)]
    M = [0 for _ in range(N)]
    R = [True for _ in range(N)]
    for i in range(N):
        nums = list(map(int, input().split()))
        M[i] = nums[1]
        for e in nums[3:]:
            adj[i].append(e-1)
            R[e-1] = False
    global answer
    answer = 0
    for n in range(N):
        if R[n]: dfs(n, adj, M)
    print(answer)
    return True

while True:
    if not solve(): break
