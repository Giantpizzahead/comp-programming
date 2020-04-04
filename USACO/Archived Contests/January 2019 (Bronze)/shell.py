'''
USACO 2019 January Contest (Bronze)
Problem 1: Shell Game
By Giantpizzahead

Here we go! :)
'''


def main():
    # Input parsing
    file_in = open("shell.in", mode='r')
    input = file_in.readlines()
    file_in.close()
    num_swaps = int(input[0])
    # Keep track of total number of points for each of the
    # starting shell locations
    # Output the one with the highest score at the end
    shells = {1: 1, 2: 2, 3: 3}
    shell1_points = 0
    shell2_points = 0
    shell3_points = 0
    for swap in range(1, num_swaps + 1):
        swap1, swap2, guess = map(int, input[swap].split())
        temp = shells[swap1]
        shells[swap1] = shells[swap2]
        shells[swap2] = temp
        if shells[guess] == 1:
            shell1_points += 1
        elif shells[guess] == 2:
            shell2_points += 1
        else:
            shell3_points += 1
    # print([shell1_points, shell2_points, shell3_points])
    output = max([shell1_points, shell2_points, shell3_points])
    file_out = open("shell.out", mode='w')
    file_out.write(str(output))
    file_out.close()


if __name__ == "__main__":
    main()
