'''
USACO 2019 January Contest (Bronze)
Problem 3: Guess the Animal
By Giantpizzahead

This is going really well! The last problem was super easy too, so
I'm confident going into this one. Let's see if I can finish this
entire contest within an hour. I think I can do it!
'''


def solve(animals):
    '''
    Method 2: Compare each pair of cows to find the maximum number
    of characteristics that one pair shares. That plus one will be
    your answer. Time complexity is n^3, but since the problem is
    limited to 100 animals / 100 characteristics, it should be fine.
    Hopefully.
    '''
    max_sharing = 0
    for i1, animal1 in enumerate(animals):
        for i2, animal2 in enumerate(animals):
            if i2 <= i1:
                continue
            current_sharing = 0
            for char in animals[animal1]:
                if char in animals[animal2]:
                    current_sharing += 1
            if current_sharing > max_sharing:
                max_sharing = current_sharing
    return max_sharing + 1


def main():
    # Input parsing
    file_in = open("guess.in", mode='r')
    input = file_in.readlines()
    file_in.close()
    num_animals = int(input[0])
    animals = {}
    # char_frequency = {}
    for a in range(1, num_animals + 1):
        input_line = input[a].split()
        animals[input_line[0]] = [input_line[c] for c in range(2, int(input_line[1]) + 2)]
        '''
        for c in animals[input_line[0]]:
            if c not in char_frequency:
                char_frequency[c] = 0
            char_frequency[c] += 1
        '''
    output = solve(animals)
    file_out = open("guess.out", mode='w')
    file_out.write(str(output))
    file_out.close()


def solve_1(animals, char_frequency):
    '''
    Solves the problem.
    Method 1: Always pick the characteristic that occurs the most
    number of times. When a characteristic is picked, remove that
    characteristic from the dictionary. Also, remove any animals
    that do not have that characteristic. Stop once there is only
    one animal left in the dictionary.
    Revised method 1: If two or more characteristics have an
    equal frequency, use recursion to check both of them.
    Result: I made a wrong assumption that you should always check
    the most common characteristic. Rip the 1 hour dream... I guess
    I'll have to start over. :(
    '''
    num_of_questions = 0
    animal_found = False
    while not animal_found:
        # Pick the most common characteristic
        most_common = None
        most_frequency = 0
        for char, frequency in char_frequency.items():
            if frequency > most_frequency:
                most_common = char
                most_frequency = frequency
        # 'Guess' that characteristic
        print("Char guessed:", most_common)
        num_of_questions += 1
        animals_to_remove = []
        for animal, chars in animals.items():
            if most_common in chars:
                chars.remove(most_common)
                char_frequency[most_common] -= 1
                if char_frequency[most_common] == 0:
                    char_frequency.pop(most_common)
            else:
                animals_to_remove.append(animal)
        for animal in animals_to_remove:
            for char in animals[animal]:
                char_frequency[char] -= 1
                if char_frequency[char] == 0:
                    char_frequency.pop(char)
            animals.pop(animal)
        print("New chars:", animals)
        if len(animals) <= 1:
            animal_found = True
    return num_of_questions


if __name__ == "__main__":
    main()
