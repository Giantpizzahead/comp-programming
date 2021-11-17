N = int(input())
A = list(map(int, input().split()))
B = [0 for _ in range(N)]

# Calculate effect of ith element on move count
for i in range(N-1):
    # Repeatedly move right
    j = i
    while j != N-1:
        B[j] += A[i]
        d = 1
        while j+d*2 < N:
            d *= 2
        j += d

# Get actual costs
for i in range(1, N-1):
    B[i] += B[i-1]

for i in range(N-1):
    print(B[i])