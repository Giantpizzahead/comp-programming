import random

T = 30
R = 10
C = 10

with open("test.in", 'w') as fout:
    fout.write(str(T) + "\n")
    for k in range(T):
        R = random.randint(1, 7)
        C = random.randint(1, 7)
        fout.write(str(R) + " " + str(C) + "\n")
        for i in range(R):
            for j in range(C):
                if (j != 0): fout.write(" ")
                fout.write(str(random.randint(1, R * C)))
            fout.write("\n")