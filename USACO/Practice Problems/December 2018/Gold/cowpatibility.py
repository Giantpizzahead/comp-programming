'''
USACO 2018 December Contest (Gold)
Problem 2: Cowpatibility

Hey, an efficiency problem! I love efficiency problems! Definitely!
I'm not sure this is going to go well.

Guess what? It didn't go so well.
'''


def main():
    # Input parsing
    file_in = open("cowpatibility.in", mode='r')
    input = file_in.readlines()
    file_in.close()

    # Everything is squeezed here to try and iterate over the list of
    # cows as little as possible to save time
    num_cows = int(input[0])
    cows = {}
    ftocow = {}
    ftocount = {}
    for i in range(1, num_cows + 1):
        flavors = list(map(int, input[i].split()))
        cows[i] = flavors
        # Keeping track of which flavors correspond to which cows and
        # the count of total # of flavors
        # To try and help optimize the later code
        for flavor in flavors:
            if flavor not in ftocow:
                ftocow[flavor] = []
            ftocow[flavor].append(i)
            if flavor not in ftocount:
                ftocount[flavor] = 0
            ftocount[flavor] += 1
    result = solve_2(num_cows, cows, ftocow, ftocount)

    file_out = open("cowpatibility.out", mode='w')
    file_out.write(str(result))
    file_out.close()


def solve_2(num_cows, cows, ftocow, ftocount):
    '''
    Method 2: Make a list of already found pairs using the ftocow dict.
    Then, subtract that list's length from the total # of possible pairs.
    Time complexity: n^2
    Result: Still too slow. I think I might have to do all my stuff inside
    of the input parsing part of this.
    '''
    found_pairs = {}
    compatible_pairs = 0
    for cows in ftocow.values():
        for i, cow in enumerate(cows):
            if cow not in found_pairs:
                found_pairs[cow] = []
            found_pairs[cow] += cows[i+1:]
    for cow in found_pairs:
        found_pairs[cow] = set(found_pairs[cow])
        compatible_pairs += len(found_pairs[cow])
    # print(found_pairs)
    return int(round(num_cows / 2 * (num_cows - 1), 5) - compatible_pairs)


def solve_1(num_cows, cows, ftocow, ftocount):
    '''
    Ah, optimization problems. The most annoying type of problem there
    is. Let me think a bit...
    Method 1: Make a dictionary with all the possible pairs of cows
    (key is cow, value is list of pair cows). Use the ftocow dict to
    find compatible pairs. Finally, figure out the number of pairs still
    left in the dictionary. Complexity: n^3
    Result: Well I mean I didn't expect that to work so yeah. n^3 is way
    too long.
    '''
    # Make all possible pairs
    all_pairs = {}
    for c in range(1, num_cows):
        all_pairs[c] = []
        for d in range(c + 1, num_cows + 1):
            all_pairs[c].append(d)
    # Look for pairs in the flavor to cows dictionary
    for cows in ftocow.values():
        for ci, c in enumerate(cows[:-1]):
            for d in cows[ci+1:]:
                if d in all_pairs[c]:
                    all_pairs[c].remove(d)
    # Count up total number of incompatible pairs
    incompatible_pairs = 0
    for pairs in all_pairs.values():
        incompatible_pairs += len(pairs)
    return incompatible_pairs


if __name__ == "__main__":
    main()
