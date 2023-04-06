import sys

S = input().strip()
T = input().strip()
Q = int(input())

alphabet = 'abcdefghijklmnopqr'
M = len(alphabet)

def gen_idx(s):
    idx = {c: [] for c in alphabet}
    for i, c in enumerate(s):
        idx[c].append(i)
    return idx
s_idx, t_idx = gen_idx(S), gen_idx(T)

# Gen conflicts (pairs of letters can't go together)
conflicts = []
for i in range(M):
    temp = []
    for j in range(i+1):
        a, b = alphabet[i], alphabet[j]
        def gen_str(idx_a, idx_b):
            s = ''
            ia, ib = 0, 0
            while ia != len(idx_a) or ib != len(idx_b):
                if ia != len(idx_a) and (ib == len(idx_b) or idx_a[ia] < idx_b[ib]):
                    s += 'a'
                    ia += 1
                else:
                    s += 'b'
                    ib += 1
            return s
        s_filter = gen_str(s_idx[a], s_idx[b])
        t_filter = gen_str(t_idx[a], t_idx[b])
        temp.append(s_filter != t_filter)
    conflicts.append(temp)
# print(conflicts)

# Check each query
answer = ''
for i in range(Q):
    query = input().strip()
    works = True
    for i in range(len(query)):
        x = ord(query[i]) - ord('a')
        for j in range(i, len(query)):
            y = ord(query[j]) - ord('a')
            if conflicts[y][x]:
                works = False
    answer += 'Y' if works else 'N'

print(answer)
