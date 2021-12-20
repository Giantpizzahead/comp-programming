with open('triangle.txt', 'r') as fin:
    triangle = fin.readlines()
    while not triangle[-1].strip():
        triangle.pop()
    triangle = [list(map(int, x.split())) for x in triangle]

N = len(triangle)
dp = [[0 for _ in range(i+1)] for i in range(N)]
dp[0][0] = triangle[0][0]
for i in range(N):
    for j in range(i+1):
        if i != 0 and j != i:
            dp[i][j] = max(dp[i-1][j] + triangle[i][j], dp[i][j])
        if i != 0 and j != 0:
            dp[i][j] = max(dp[i-1][j-1] + triangle[i][j], dp[i][j])
print(max(dp[N-1]))