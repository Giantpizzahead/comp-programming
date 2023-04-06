N = int(input())
A = list(map(int, input().split()))
K = int(input())
R = {}
for i in range(K):
    temp = [x-1 for x in map(int, input().split())]
    R[temp[0]] = temp[2:]

# Binary search on max # of top metals to be made
def check(T):
    num_needed = [0 for i in range(N)]
    num_needed[N-1] = T
    for i in reversed(range(N)):
        num_needed[i] -= A[i]
        # Make this metal
        if num_needed[i] > 0:
            # print('Needed', i, num_needed[i])
            if i not in R:
                return False
            for j in R[i]:
                num_needed[j] += num_needed[i]
    return True

low = 0
high = sum(A)
while low < high:
    mid = (low+high+1) // 2
    # print('check', mid)
    if check(mid):
        low = mid
    else:
        high = mid-1
print(low)
