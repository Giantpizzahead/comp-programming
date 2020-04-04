'''
USACO 2019 January Contest (Silver)
Problem 3: Mountain View
By Giantpizzahead

So the last problem didn't exactly go well. I've skipped it for now,
so let's try this problem first.
'''

mountain_peaks = []


def solve():
    '''
    Solving the problem.
    Method 2: Start from the smallest mountain, and go up.
    '''
    sorted_peaks = sorted(mountain_peaks, key=lambda p: p[1])
    peak1i = 1
    while peak1i < len(sorted_peaks):
        peak1 = sorted_peaks[peak1i]
        peak2i = 0
        while peak2i < peak1i:
            peak2 = sorted_peaks[peak2i]
            if abs(peak1[0] - peak2[0]) <= peak1[1] - peak2[1]:
                sorted_peaks.pop(peak2i)
                peak1i -= 1
            else:
                peak2i += 1
        peak1i += 1
    return len(sorted_peaks)


def main():
    # Input parsing
    file_in = open("mountains.in", mode='r')
    input = file_in.readlines()
    file_in.close()
    num_mountains = int(input[0])
    for i in range(num_mountains):
        mountain_peaks.append(tuple(map(int, input[i+1].split())))
    output = solve()
    file_out = open("mountains.out", mode='w')
    file_out.write(str(output))
    file_out.close()


def solve_1(mountain_peaks):
    '''
    Solving the problem.
    Method 1: Start from the tallest mountain, and go down.
    '''
    sorted_peaks = sorted(mountain_peaks, key=lambda p: p[1])
    sorted_peaks = sorted_peaks[::-1]
    bad_peaks = {}
    i = 0
    while i < len(sorted_peaks) - 1:
        j = i + 1
        while j < len(sorted_peaks):
            if abs(sorted_peaks[j][0] - sorted_peaks[i][0]) <= abs(sorted_peaks[j][1] - sorted_peaks[i][1]):
                bad_peaks[j] = True
            j += 1
            while j in bad_peaks:
                j += 1
        i += 1
    return len(sorted_peaks) - len(bad_peaks)


if __name__ == "__main__":
    main()
