'''
USACO 2019 January Contest (Bronze)
Problem 2: Sleepy Cow Sorting
By Giantpizzahead

Alright, first one went super smoothly. Next problem, here I come!
'''


def main():
    # Input parsing
    file_in = open("sleepy.in", mode='r')
    input = file_in.readlines()
    file_in.close()
    num_cows = int(input[0])
    cows = list(map(int, input[1].split()))
    # Method: Find # of cows sorted at end of line
    # Number of cows - Number sorted at end = Answer
    cows = cows[::-1]
    last_cow = cows[0]
    num_sorted = 1
    for cow in cows[1:]:
        if last_cow > cow:
            last_cow = cow
            num_sorted += 1
        else:
            break
    output = num_cows - num_sorted
    file_out = open("sleepy.out", mode='w')
    file_out.write(str(output))
    file_out.close()


if __name__ == "__main__":
    main()
