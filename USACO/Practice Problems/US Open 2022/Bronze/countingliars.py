N = int(input())
A = []
L = []
for i in range(N):
    a, l = input().split()
    A.append(a == 'L')
    L.append(int(l))

best = N
for i in range(N):
    # Try placing cow at this location
    curr = 0
    for j in range(N):
        if L[i] != L[j] and A[j] != (L[i] < L[j]):
            curr += 1
    best = min(curr, best)
print(best)
