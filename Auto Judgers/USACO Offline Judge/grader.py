"""
Used on the airplane trip from SFO to Boston! ;)
(and back now :D)
"""

import os
import time
import subprocess
import ansi

test_path = 'Gold/prob1_gold_open22'
code_path = 'applecatchingwrong.cpp'
num_tests = len(os.listdir(test_path)) // 2
output_path = 'grader/out.txt'
compile_path = 'grader/sol.cpp'
time_limit = 4 if code_path.endswith('.py') else 2

def run_program(input_path, output_path):
    start_time = time.time()
    runner = {
        '.py': ['python3', code_path],
        '.cpp': [compile_path]
    }
    command = [v for k, v in runner.items() if code_path.endswith(k)][0]
    process = subprocess.Popen(command, stdin=open(input_path, 'r'), stdout=open(output_path, 'w'), stderr=subprocess.PIPE)
    exit_code = None
    time_elapsed = time.time() - start_time
    while time_elapsed < time_limit:
        time.sleep(0.01)
        time_elapsed = time.time() - start_time
        if process.poll() is not None:
            exit_code = process.poll()
            break
    if exit_code is None or time_elapsed > time_limit:
        # TLE
        process.terminate()
        return "t", min(time_elapsed, time_limit)
    elif exit_code != 0:
        # RE
        process.terminate()
        return "!", time_elapsed
    else:
        return 0, time_elapsed

def set_color(color_code):
    print(ansi.CSI + str(color_code), end='')

set_color(ansi.Fore.BLUE)
print("\nUSACO Auto Grader")
print("Test path:", test_path)
print("Code path:", code_path)
print("# of tests:", num_tests)
print("Time limit:", time_limit, "seconds")

if code_path.endswith('.cpp'):
    # Compile
    print("Compiling...", end=" ")
    os.system(f'g++ --std=c++17 -O2 {code_path} -o {compile_path}')
    print("Done!")

print("-"*40)

num_correct = 0
for i in range(1, num_tests+1):
    set_color(ansi.Fore.YELLOW)
    print(f'Running test {i}...', end=' '*12 if i < 10 else ' '*11)
    set_color(ansi.Fore.RESET)
    result, time_elapsed = run_program(f'{test_path}/{i}.in', output_path)
    if type(result) == str:
        set_color(ansi.Back.RED)
        print(f'{result} ({time_elapsed:.2f}s)'.center(11), end='')
        set_color(ansi.Back.RESET)
        print()
    else:
        with open(output_path, 'r') as fout, open(f'{test_path}/{i}.out') as fans:
            if [l.strip() for l in fout.readlines()] == [l.strip() for l in fans.readlines()]:
                set_color(ansi.Back.LIGHTGREEN_EX)
                print(f'* ({time_elapsed:.2f}s)'.center(11), end='')
                set_color(ansi.Back.RESET)
                print()
                num_correct += 1
            else:
                set_color(ansi.Back.RED)
                print(f'x ({time_elapsed:.2f}s)'.center(11), end='')
                set_color(ansi.Back.RESET)
                print()


set_color(ansi.Fore.BLUE)
print("-"*40)
set_color(ansi.Fore.RESET)

if num_correct == 0:
    set_color(ansi.Back.RED)
elif num_correct < num_tests:
    set_color(ansi.Back.LIGHTYELLOW_EX)
else:
    set_color(ansi.Back.LIGHTGREEN_EX)
''
print(f' Score: {num_correct}/{num_tests} '.center(40), end='')
set_color(ansi.Back.RESET)
print('\n')
