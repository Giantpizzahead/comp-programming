"""
USACO 2014 February Contest (Silver)
Problem 3: Secret Code
By Giantpizzahead

For AlphaStar self-test
"""

from collections import deque


def main():
    '''
    while True:
        encrypted = input("-> ")
        print(backtrack(encrypted))
        print(backtrack_smarter(encrypted))
    '''
    with open("scode.in", 'r') as fin:
        encrypted = fin.readline().strip()
    answer = backtrack_amazing(encrypted) % 2014
    with open("scode.out", 'w') as fout:
        fout.write(str(answer) + "\n")


def backtrack_amazing(start):
    # Make a dictionary containing all encrypted strings
    strings = {start: 1}
    num_ways = 0
    # found = False
    while strings:
        # print(strings)
        new_strings = {}
        for string in strings:
            length = len(string)
            if length < 2:
                continue
            # Check for ways involving adding substring to left or right of the original string
            for i in range((length-1)//2):
                cut1 = string[:i+1]
                cut2 = string[-i-1:]
                cut3 = string[i+1:]
                cut4 = string[:-i-1]
                num = strings[string] % 2014
                # found = False
                if cut1 == string[i+1:(i+1)*2]:
                    # Substring taken from left, added to left
                    # print("{} taken left added left {}".format(string, string[i+1:]))
                    if cut3 not in new_strings:
                        new_strings[cut3] = 0
                    new_strings[cut3] += num
                    num_ways += num
                    # found = True
                if cut1 == cut2:
                    # Substring taken from right, added to left
                    if cut3 not in new_strings:
                        new_strings[cut3] = 0
                    new_strings[cut3] += num
                    # Also possibly substring taken from left, added to right
                    if cut4 not in new_strings:
                        new_strings[cut4] = 0
                    new_strings[cut4] += num
                    # print("{} taken right added left {}".format(string, string[i+1:]))
                    # print("{} taken left added right {}".format(string, string[:-i-1]))
                    num_ways += 2 * num
                    # found = True
                if cut2 == string[(-i-1)*2:-i-1]:
                    # Substring taken from right, added to right
                    # print("{} taken right added right {}".format(string, string[:-i-1]))
                    if cut4 not in new_strings:
                        new_strings[cut4] = 0
                    new_strings[cut4] += num
                    num_ways += num
                    # found = True
                '''
                if not found:
                    # No more can exist; stop checking further
                    break
                '''
        strings = new_strings
    # print(num_ways)
    return num_ways


def add_to_dict(new_strings, string, num):
    if string not in new_strings:
        new_strings[string] = 0
    new_strings[string] += num


def backtrack_smarter(start):
    # Make a dictionary containing all encrypted strings
    strings = {start: 1}
    num_ways = 0
    while strings:
        # print(strings)
        new_strings = {}
        for string in strings:
            if len(string) < 2:
                continue
            # Check for ways involving adding substring to left or right of the original string
            for i in range((len(string)-1)//2):
                if string[:i+1] == string[i+1:(i+1)*2]:
                    # Substring taken from left, added to left
                    # print("{} taken left added left {}".format(string, string[i+1:]))
                    add_to_dict(new_strings, string[i+1:], strings[string])
                    num_ways += 1 * strings[string]
                if string[:i+1] == string[-i-1:]:
                    # Substring taken from right, added to left
                    add_to_dict(new_strings, string[i+1:], strings[string])
                    # Also possibly substring taken from left, added to right
                    add_to_dict(new_strings, string[:-i-1], strings[string])
                    # print("{} taken right added left {}".format(string, string[i+1:]))
                    # print("{} taken left added right {}".format(string, string[:-i-1]))
                    num_ways += 2 * strings[string]
                if string[-i-1:] == string[(-i-1)*2:-i-1]:
                    # Substring taken from right, added to right
                    # print("{} taken right added right {}".format(string, string[:-i-1]))
                    add_to_dict(new_strings, string[:-i-1], strings[string])
                    num_ways += 1 * strings[string]
        strings = new_strings
    # print(num_ways)
    return num_ways


def backtrack(start):
    # Make a queue containing all encrypted strings
    strings = deque([start])
    num_ways = 0
    while strings:
        # Evaluate the next string
        string = strings.pop()
        if len(string) < 2:
            continue
        # Check for ways involving adding substring to left or right of the original string
        for i in range((len(string)-1)//2):
            if string[:i+1] == string[i+1:(i+1)*2]:
                # Substring taken from left, added to left
                # print("{} taken left added left {}".format(string, string[i+1:]))
                strings.append(string[i+1:])
                num_ways += 1
            if string[:i+1] == string[-i-1:]:
                # Substring taken from right, added to left
                strings.append(string[i+1:])
                # Also possibly substring taken from left, added to right
                strings.append(string[:-i-1])
                # print("{} taken right added left {}".format(string, string[i+1:]))
                # print("{} taken left added right {}".format(string, string[:-i-1]))
                num_ways += 2
            if string[-i-1:] == string[(-i-1)*2:-i-1]:
                # Substring taken from right, added to right
                # print("{} taken right added right {}".format(string, string[:-i-1]))
                strings.append(string[:-i-1])
                num_ways += 1
    # print(num_ways)
    return num_ways


if __name__ == "__main__":
    main()
