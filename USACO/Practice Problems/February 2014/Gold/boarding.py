"""
USACO 2014 February Contest (Gold)
Problem 3: Airplane Boarding
***CHALLENGE PROBLEM***
By Giantpizzahead

For myself. Apparently this was an extremely hard problem in the actual contest...
So naturally I'm trying it by myself. :D
Let's do this.
"""

import bisect
import math

DEBUG = False

def main():
    with open("boarding.in", 'r') as fin:
        cows = get_cow_list(fin)
    cows = cows[::-1]
    answer = step_through(cows)
    if DEBUG:
        print(cows)
        answer1 = simulate(cows)
        if answer1 != answer:
            raise Exception("Wrong answer! {} (Wrong) != {} (Correct)".format(answer, answer1))
    with open("boarding.out", 'w') as fout:
        fout.write(str(answer) + "\n")


def smart_insert(delay, delays):
    left = 0
    right = len(delays)
    while right - left > 0:
        if delays[(left + right) // 2][0] < delay[0]:
            left += math.ceil((right - left) / 2)
        elif delays[(left + right) // 2][0] > delay[0]:
            right -= math.ceil((right - left) / 2)
        else:
            left = (left + right) // 2
            right = (left + right) // 2
            break
    delays.insert(left, delay)
    if DEBUG:
        print("Before deletion: {}".format(delays))
    to_delete = delay[1] + 1
    to_remove = []
    for i, d in enumerate(delays[left+1:]):
        if d[1] <= to_delete:
            to_remove.append(left+1+i-len(to_remove))
        to_delete += 1
    for i in to_remove:
        delays.pop(i)


def step_through(cows):
    delays = []
    for i, cow in enumerate(cows):
        # Calculate the raw time for the cow without any delays
        cow_time = i + cow[0] + cow[1]
        if DEBUG:
            print("Cow {} raw time: {}".format(i, cow_time))
        # Find the maximum delay caused by any cow
        max_added_delay = 0
        to_insert = []
        for d in range(len(delays)):
            if delays[d][0] > cow[0]:
                break
            if delays[d][1] > i + delays[d][0]:
                max_added_delay = max(max_added_delay, delays[d][1] - i - delays[d][0])
                if DEBUG:
                    print("Delayed {} seconds by {}".format(delays[d][1] - i - delays[d][0], delays[d][0]))
                to_insert.append([delays[d][0] - 1, delays[d][1]])
        for t in to_insert:
            smart_insert(t, delays)
        smart_insert([cow[0], cow_time + max_added_delay], delays)
        if DEBUG:
            print("After cow {}, delays: {}".format(i, delays))
    return max([x[1] for x in delays]) + 1


def print_simulation(timer, size, airplane):
    print("Time: {} seconds".format(timer))
    output = ""
    for v in airplane:
        if v != -1:
            output += str(v["id"]) + " "
        else:
            output += "- "
    print(output)
    output = "  " * size + "S " * size
    print(output, "\n")


def simulate(cows):
    seconds = 0
    airplane = []
    for i in range(0, len(cows) * 2):
        airplane.append(-1)
    for i in range(len(cows)):
        airplane[i] = {"status":"moving", "id":-i-1+len(cows)}
    moved_cow = True
    while moved_cow:
        moved_cow = False
        for i in range(len(cows)*2-1, -1, -1):
            # print("Evaluate", i)
            if airplane[i] != -1 and airplane[i]["status"] == "moving":
                moved_cow = True
                if airplane[i+1] == -1:
                    airplane[i+1] = airplane[i]
                    airplane[i] = -1
                    if i+1 == cows[airplane[i+1]["id"]][0] + len(cows) - 1:
                        airplane[i+1]["status"] = cows[airplane[i+1]["id"]][1]
                        print_simulation(seconds, len(cows), airplane)
                        print("Sit {}".format(airplane[i+1]["id"]))
            elif airplane[i] != -1:
                moved_cow = True
                airplane[i]["status"] -= 1
                if airplane[i]["status"] == 0:
                    print("Done {} at {} seconds".format(airplane[i]["id"], seconds+1))
                    airplane[i] = -1
        seconds += 1
    print_simulation(seconds, len(cows), airplane)
    print("Total time taken: {} seconds".format(seconds))
    return seconds


def get_cow_list(fin):
    num_cows = int(fin.readline().strip())
    cows = []
    for i in range(num_cows):
        cows.append(tuple([int(n) for n in fin.readline().strip().split()]))
    return cows


if __name__ == "__main__":
    main()