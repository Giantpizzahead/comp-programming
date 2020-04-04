import random

NUM_WORDS = 5000
NUM_LINES = 10000
NUM_SYLLABLES = 5000
NO_REPEAT_SYLLABLE_COUNT = False

with open("poetry.in", 'w') as fout:
    fout.write("{} {} {}\n".format(NUM_WORDS, NUM_LINES, NUM_SYLLABLES))
    for i in range(NUM_WORDS):
        if NO_REPEAT_SYLLABLE_COUNT:
            fout.write("{} {}\n".format(
                i+1,
                random.randrange(1, max(4, int(NUM_WORDS / 30)))
            ))
        else:
            fout.write("{} {}\n".format(
                random.randrange(1, NUM_SYLLABLES),
                random.randrange(1, max(4, int(NUM_WORDS / 30)))
            ))
    for i in range(NUM_LINES):
        fout.write("{}\n".format(chr(random.randrange(ord("A"), ord("Z") + 1))))
