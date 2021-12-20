import random

def genTestCase(out):
    ROWS = random.randint(200, 300)
    COLS = random.randint(200, 300)
    SPARE_ROWS = random.randint(0, int(ROWS / 5))
    SPARE_DIODES = random.randint(0, int(ROWS * COLS / 7))
    out.write("{} {} {} {}\n".format(ROWS, COLS, SPARE_ROWS, SPARE_DIODES))
    ZERO_DENSITY = random.randint(0, 10)
    choice_arr = ['0' for _ in range(ZERO_DENSITY)]
    choice_arr.append('1')
    for i in range(ROWS):
        out.write(' '.join([random.choice(choice_arr) for _ in range(COLS)]))
        out.write('\n')
    

with open("input.txt", 'w') as out:
    for i in range(30):
        genTestCase(out)
    out.write("0 0 0 0\n")
