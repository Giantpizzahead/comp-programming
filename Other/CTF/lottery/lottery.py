import random, os


def init_random():
    random.seed(os.urandom(64))


def get_answer():
    return random.randrange(10**9) + 1


def print_flag():
    print("Impressive... looks like it's your lucky day(s)! Here's your reward:")
    with open("flag.txt", 'r') as flag:
        print(flag.read())
    print()


print("""
Welcome to the daily PRNG lottery!
Guess a number between 1 and 10^9 each day.
Get 5 correct guesses within 18 years (~6570 days) to win.
""")

init_random()
num_correct = 0
for day in range(6570):
    print(f"Day {day+1}")
    guess = input("Your guess: ")
    answer = get_answer()
    if guess == str(answer):
        num_correct += 1
        print(f"Correct! You now have {num_correct} correct guesses.\n")
        if num_correct >= 5:
            print_flag()
            exit(0)
    else:
        print(f"Wrong. The correct number was {answer}\n")

print(f"""The lottery is now closed.
You got {num_correct} correct guesses.
Better luck next time...
""")
