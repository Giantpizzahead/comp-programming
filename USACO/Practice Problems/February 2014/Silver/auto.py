"""
USACO 2014 February Contest (Silver)
Problem 1: Autocomplete
By Giantpizzahead

This is for the AlphaStar self evaluation thing.
"""

import bisect


def main():
    with open("auto.in", 'r') as fin:
        words, orig_locations, n = make_list_from_input(fin)
        targets = fin.readlines()
        print(targets)
    with open("auto.out", 'w') as fout:
        for target in targets:
            loc, target_word = target.strip().split()
            loc = int(loc)
            output = find_word(target_word, loc, words)
            if output == -1:
                fout.write("-1\n")
            else:
                fout.write(str(orig_locations[output]) + "\n")


def make_list_from_input(fin):
    w, n = [int(n) for n in fin.readline().strip().split()]
    words = []
    orig_locs = {}
    for i in range(w):
        word = fin.readline().strip()
        words.insert(bisect.bisect_left(words, word), word)
        orig_locs[word] = i + 1
    return words, orig_locs, n


def find_word(target, loc, words):
    start = bisect.bisect_left(words, target)
    if start + loc - 1 >= len(words):
        return -1
    if words[start + loc - 1][:len(target)] == target:
        return words[start + loc - 1]
    else:
        return -1


if __name__ == "__main__":
    main()