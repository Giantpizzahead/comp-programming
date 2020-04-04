import random

# Walk through the program step by step (using the scratchbook).
# See if you can find something wrong with its logic.
# Since it doesn't run in time anyways, try making a new method of
# solving the problem.

size = 15
random_chance = 0.8

out = open("perimeter.in", mode='w')
out.write(str(size) + "\n")
for i in range(size):
    # row = ['#' if random.random() < random_chance else '.' for i in range(size)]
    # print_row = ''.join(row)
    if i % 2 == 0:
        print_row = '#..............'
    else:
        print_row = '#.............#'
    out.write(print_row + "\n")
