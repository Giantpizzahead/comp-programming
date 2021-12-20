with open('names.txt', 'r') as fin:
    names = eval('[' + fin.read() + ']')

names = sorted(names)

def get_score(name, pos):
    score = sum(ord(c)-ord('A')+1 for c in name)
    score *= pos
    return score

total_score = sum(get_score(name, i+1) for i, name in enumerate(names))
print(total_score)
