'''
USACO 2019 February Contest (Silver)
Problem 1: Sleepy Cow Herding
By Giantpizzahead

Let's go! :)
'''
import bisect


def smallest(cows):
    num_cows = len(cows)
    least = num_cows
    for cow_index, cow in enumerate(cows):
        target = cow + num_cows - 1
        # print("Target:", target)
        target_index = bisect.bisect_right(cows, target)
        # print("Index:", target_index)
        num_moves = num_cows - (target_index - cow_index)
        # print("Num moves:", num_moves)
        if num_moves == 1:
            # Special case
            need_to_add = True
            last = cows[cow_index] - 1
            for cow in cows[cow_index:target_index]:
                if abs(cow - last) == 1:
                    last = cow
                else:
                    need_to_add = False
                    break
            if need_to_add:
                # print("Added!")
                num_moves += 1
        if num_moves < least:
            least = num_moves
    return least


def longest(cows):
    # Error has something to do with this.
    num_moves = 0
    left_dist = 9999999999
    left_insert = 0
    prev = cows[1]
    for ci, cow in enumerate(cows[2:]):
        if cow == prev + 1:
            prev = cow
        else:
            left_dist = prev - cows[0] + 1
            left_insert = ci + 2
            break
    right_dist = 9999999999
    right_insert = 0
    prev = cows[-2]
    for ci, cow in enumerate(cows[-3::-1]):
        if cow == prev - 1:
            prev = cow
        else:
            right_dist = cows[-1] - prev + 1
            right_insert = ci - 2
            break
    print("Left", left_dist, left_insert)
    print("Right", right_dist, right_insert)
    if left_dist < right_dist:
        cows.insert(left_insert, cows[0] + left_dist)
        cows.pop(0)
    else:
        cows.insert(right_insert, cows[-1] - right_dist)
        cows.pop()
    num_moves += 1
    print(cows)
    num_moves += (cows[-1] - cows[0]) - (len(cows) - 1)
    if left_dist == right_dist and left_dist == 9999999999:
        num_moves = 0
    return num_moves


def main():
    # Input parsing
    cows = []
    with open("herding.in", 'r') as input:
        num_cows = int(input.readline())
        for i in range(num_cows):
            cows.append(int(input.readline()))
    cows = sorted(cows)
    least = smallest(cows)
    most = longest(cows)
    with open("herding.out", 'w') as output:
        output.write(str(least) + "\n" + str(most) + "\n")
    # print(least, most)


main()
