K, M = map(int, input().split())
A, B = map(int, input().split())
print(int(str(A), base=K) - int(str(B), base=M))
