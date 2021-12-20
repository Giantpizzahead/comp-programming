digits = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine', 'ten', 'eleven', 'twelve',
          'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen']
tens = ['N/A', 'N/A', 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety']
def get_words(x, is_first = False):
    words = []
    if x == 0 and not is_first:
        # Blank number
        pass
    elif x >= 10**6:
        words += get_words(x // (10**6))
        words += ['million']
        words += get_words(x % (10**6))
    elif x >= 10**3:
        words += get_words(x // (10**3))
        words += ['thousand']
        words += get_words(x % (10**3))
    elif x >= 10**2:
        words += [digits[x // (10**2)]]
        words += ['hundred']
        if x % (10**2) != 0:
            words += ['and']
            words += get_words(x % (10**2))
    elif x >= 20:
        if x % 10 == 0:
            words += [tens[x // 10]]
        else:
            words += [tens[x // 10] + '-' + digits[x % 10]]
    else:
        words += [digits[x]]
    return words

def get_word(x):
    return ' '.join(get_words(x, True))

cnt = 0
for i in range(1, 1001):
    word = get_word(i)
    curr_cnt = len(list(filter(lambda x: x not in ' -', word)))
    cnt += curr_cnt
    print(i, curr_cnt, word)
print(cnt)
