import re

# Both arguments should be positive integers
def precise_division(dividend, divisor):
    n = dividend // divisor
    whole_part = str(n)
    dividend -= n * divisor
    dividend *= 10

    # Stop when the dividend starts looping
    curr_time = 0
    decimal_part = ''
    prev_states = {}
    while dividend != 0 and dividend not in prev_states:
        prev_states[dividend] = curr_time
        curr_time += 1
        n = dividend // divisor
        decimal_part += str(n)
        dividend -= n * divisor
        dividend *= 10
    
    if dividend == 0:
        return whole_part + (('.' + decimal_part) if decimal_part else '')
    else:
        repeat_time = prev_states[dividend]
        nonrepeating_part = decimal_part[:repeat_time]
        repeating_part = decimal_part[repeat_time:]
        return whole_part + '.' + nonrepeating_part + '(' + repeating_part + ')'

def solve_euler():
    N = 1000
    answer = 0
    max_repeat_len = -1
    for d in range(1, N):
        res = precise_division(1, d)
        # Find repeat length using regex
        m = re.search(r"\((\d*)\)", res)
        repeat_len = len(m.group(1)) if m else 0
        if repeat_len > max_repeat_len:
            answer = d
            max_repeat_len = repeat_len
        # print(1, '/', d, '=', precise_division(1, d))
    print('Answer:', answer)
    print('Repeat length:', max_repeat_len)

def experiment():
    N = 250
    answer = (0, 0)
    max_repeat_len = -1
    for a in range(1, N):
        for b in range(1, N):
            res = precise_division(a, b)
            # Find repeat length using regex
            m = re.search(r"\((\d*)\)", res)
            repeat_len = len(m.group(1)) if m else 0
            if repeat_len > max_repeat_len:
                answer = (a, b)
                max_repeat_len = repeat_len
            # print(a, '/', b, '=', precise_division(a, b))
    print(answer[0], '/', answer[1], '=', precise_division(answer[0], answer[1]))
    print('Answer:', answer)
    print('Repeat length:', max_repeat_len)

solve_euler()