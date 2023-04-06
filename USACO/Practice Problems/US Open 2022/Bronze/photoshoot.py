N = int(input())
S = input()

locs = []
for i in range(N//2):
    if S[i*2] == 'G' and S[i*2+1] == 'G':
        if locs:
            locs.append('A')
    elif S[i*2] == 'G':
        locs.append('O')
    elif S[i*2+1] == 'G':
        locs.append('E')

answer = 0
last_type = locs[0]
for l in locs:
    if l != 'A' and l != last_type:
        last_type = l
        answer += 1
if last_type == 'O':
    answer += 1
print(answer)
