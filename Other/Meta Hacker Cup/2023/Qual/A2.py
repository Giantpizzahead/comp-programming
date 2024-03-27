"""
Solution: Greedy.
"""
def check(A, B, C, K):
    # All singles or all doubles
    total_cost = min(K * A, (K+1+1) // 2 * B)
    # Exactly 1 single
    if K >= 1:
        total_cost = min(total_cost, A + (K-1+1) // 2 * B)
    # Exactly 2 singles
    if K >= 2:
        total_cost = min(total_cost, 2 * A + (K-2+1) // 2 * B)
    return total_cost <= C


def solve(A, B, C):
    low, high = 0, 10 ** 18
    while low < high:
        mid = (low + high + 1) // 2
        if check(A, B, C, mid):
            low = mid
        else:
            high = mid - 1
    return low


with open("test.in", "r") as fin, open("test.out", "w") as fout:
    T = int(fin.readline())
    for i in range(T):
        A, B, C = map(int, fin.readline().strip().split())
        fout.write(f"Case #{i+1}: {solve(A, B, C)}\n")
