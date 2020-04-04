"""
USACO 2019 January Contest (Gold)
Problem 1: Cow Poetry
By Giantpizzahead

Practice for the USACO gold division.
Looks kinda hard, but I'm sure I can do it. :)
"""

import bisect
import time
# import poetry_input


DEBUG = False
to_sum_lookup = []
to_rhyme_lookup = {}
# A dictionary of the syllables in each word
numbers = []
# A dictionary, key is the rhyme class, value is a list containing the syllables
# for each word in that rhyme class
words = {}
# The number of syllables in each line
syllable_count = 0
# The rhyme scheme of the poem
rhyme_scheme = {}
# The set of syllable lengths seen
lengths_seen = set()


def main():
    global numbers, words, syllable_count, rhyme_scheme, to_sum_lookup
    if DEBUG:
        start_time = time.time()
    with open("poetry.in", 'r') as fin:
        numbers, words, syllable_count, rhyme_scheme = parse_input(fin)
    to_sum_lookup = [1 for _ in range(syllable_count + 1)]
    # Generate the number of ways to make a line given the number of syllables allowed
    if DEBUG:
        print("Parsing done at {} seconds".format(time.time() - start_time))
    evaluate_sums(numbers, syllable_count)
    # efficient_sum(numbers, syllable_count)
    # Generate the number of ways to make a line given the rhyme class the line's from
    if DEBUG:
        print("Sums done at {} seconds".format(time.time() - start_time))
    sum_rhymes(words, syllable_count)
    # Generate the number of ways to make all the lines given the rhyme scheme
    if DEBUG:
        print("Rhymes done at {} seconds".format(time.time() - start_time))
    answer = eval_rhyme_scheme(rhyme_scheme)
    if DEBUG:
        print("Number list: {}".format(numbers))
        print("Word list: {}".format(words))
        print("Rhyme scheme: {}".format(rhyme_scheme))
        print("Sum lookup: {}".format(to_sum_lookup))
        print("Rhyme lookup: {}".format(to_rhyme_lookup))
        print("Answer: {}".format(answer))
    with open("poetry.out", 'w') as fout:
        fout.write(str(answer) + "\n")


def parse_input(fin):
    num_words, num_lines, total_syllables = [int(n) for n in fin.readline().strip().split()]
    word_nums = [0 for _ in range(total_syllables + 1)]
    words = {}
    for i in range(num_words):
        syl, cla = [int(n) for n in fin.readline().strip().split()]
        if cla not in words:
            words[cla] = []
        words[cla].append(syl)
        word_nums[syl] += 1
        if syl not in lengths_seen:
            lengths_seen.add(syl)
    scheme = {}
    for c in range(num_lines):
        rhyme = fin.readline().strip()
        if rhyme not in scheme:
            scheme[rhyme] = 0
        scheme[rhyme] += 1
    return word_nums, words, total_syllables, scheme


def eval_rhyme_scheme(rhyme_scheme):
    global to_rhyme_lookup
    total_ways = 1
    num_ways = 0
    for r in rhyme_scheme.values():
        num_ways = 0
        # Find the number of ways to generate the given number of lines using each rhyme class
        for c in to_rhyme_lookup.values():
            num_ways += c ** r
        total_ways *= num_ways
        total_ways %= 1000000007
    return total_ways


def sum_rhymes(words, syllable_count):
    global to_rhyme_lookup
    # Do the evaluation separately for each rhyme class
    for word_list in words:
        # Iterate through each word (syllable count),
        # and add the # of ways that the line could be made
        num_ways = 0
        for s in words[word_list]:
            target_syllables = syllable_count - s
            if target_syllables > -1:
                num_ways += to_sum_lookup[target_syllables]
                num_ways = num_ways % 1000000007
        to_rhyme_lookup[word_list] = num_ways


def ways_to_sum(nums, nums_sort, target):
    """
    nums is a dictionary
    nums_sort is a sorted list containing the keys in nums
    """
    global to_sum_lookup
    num_ways = 0
    for n in nums_sort:
        if n > target:
            break
        else:
            num_ways += to_sum_lookup[target - n] * nums[n]
    to_sum_lookup[target] = num_ways % 1000000007


def in_one_sum(nums, syllable_count):
    """
    nums is a dictionary
    nums_sort is a sorted list containing the keys in nums
    """
    global to_sum_lookup
    nums_sort = sorted(nums.keys())
    for target in range(1, syllable_count + 1):
        if DEBUG and target % 100 == 0:
            print("On {}".format(target))
        num_ways = 0
        for n in nums_sort:
            if n > target:
                break
            else:
                num_ways += (to_sum_lookup[target - n]) * nums[n]
        to_sum_lookup[target] = num_ways % 1000000007


def efficient_sum(nums, syll_count):
    """
    nums is a dictionary
    nums_sort is a sorted list containing the keys in nums
    This program calculates all the sums at once, instead
    of running 5000 separate times
    """
    global to_sum_lookup
    for i in range(1, syll_count + 1):
        to_sum_lookup[i] = 0
    for n in range(0, syll_count):
        if DEBUG and n % 100 == 0:
            print("On {}".format(n))
        for i in range(n + 1, syll_count + 1):
            to_sum_lookup[i] += to_sum_lookup[n] * nums[i - n]
        to_sum_lookup[n + 1] %= 1000000007


def evaluate_sums(nums, syllable_count):
    """
    Preevaluates all the ways to sum from 1 to the max syllable count.
    """
    global to_sum_lookup
    nums_sort = sorted(lengths_seen)
    for i in range(1, syllable_count + 1):
        #if DEBUG and i % 100 == 0:
        #    print("On {}".format(i))
        ways_to_sum(nums, nums_sort, i)


if __name__ == "__main__":
    main()
