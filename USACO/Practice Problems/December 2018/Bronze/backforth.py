'''
USACO 2018 December Contest (Bronze)
Problem 3: Back and Forth

More practice. This one seems harder, so let's do it.
'''

possible_readings = []


def solve(left_buckets, right_buckets):
    '''
    Solve the problem.
    Method 1: Recursion (since I need practice on recursion)
    '''
    # Start recursion
    global possible_readings
    possible_readings = []
    solve_rec(left_buckets[:], right_buckets[:], 0, 1000)
    return len(possible_readings)


def solve_rec(left_buckets, right_buckets, day, tank_reading):
    '''Recursion for the current solving method.'''
    # print(left_buckets, right_buckets, day, tank_reading)
    if day % 2 == 0:
        left_set = set(left_buckets)
        for bucket in left_set:
            new_left = left_buckets[:]
            new_left.remove(bucket)
            new_right = right_buckets[:]
            new_right.append(bucket)
            solve_rec(new_left, new_right, day + 1, tank_reading - bucket)
    else:
        right_set = set(right_buckets)
        for bucket in right_set:
            new_right = right_buckets[:]
            new_right.remove(bucket)
            new_left = left_buckets[:]
            new_left.append(bucket)
            if day != 3:
                solve_rec(new_left, new_right, day + 1, tank_reading + bucket)
            else:
                if tank_reading + bucket not in possible_readings:
                    # print("New possible reading:", tank_reading + bucket)
                    possible_readings.append(tank_reading + bucket)


def main():
    # Input parsing
    file_in = open("backforth.in", mode='r')
    input = file_in.readlines()
    file_in.close()
    left_buckets = list(map(int, input[0].split()))
    right_buckets = list(map(int, input[1].split()))
    result = solve(left_buckets, right_buckets)
    file_out = open("backforth.out", mode='w')
    file_out.write(str(result))
    file_out.close()


if __name__ == "__main__":
    main()
