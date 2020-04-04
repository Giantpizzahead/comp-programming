Q = 100000

with open("newbarn.in", 'w') as fout:
    fout.write(str(Q) + '\n')
    fout.write("B -1\n")
    for i in range(Q-1):
        fout.write("B -1\n")