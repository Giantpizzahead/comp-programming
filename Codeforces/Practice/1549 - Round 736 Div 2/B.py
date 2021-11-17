T = int(input())
for i in range(T):
    N = int(input())
    E = input()
    G = input()
    U = ['0' for _ in range(N)]
    ans = 0
    for j in range(N):
        if G[j] == '0': continue
        elif E[j] == '0':
            U[j] = '1'
            ans += 1
        elif j != 0 and E[j-1] == '1' and U[j-1] == '0':
            U[j-1] = '1'
            ans += 1
        elif j != N-1 and E[j+1] == '1' and U[j+1] == '0':
            U[j+1] = '1'
            ans += 1
    print(ans)
