denoms = [1, 2, 5, 10, 20, 50, 100, 200]
dp = [0 for _ in range(201)]
dp[0] = 1
for x in denoms:
    for i in range(x, 201):
        dp[i] += dp[i-x]
print(dp[200])
