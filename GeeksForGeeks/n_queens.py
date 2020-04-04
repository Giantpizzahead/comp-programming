def main():
    num_tests = int(input())
    for _ in range(num_tests):
        board_size = int(input())
        answers = solve_queens(board_size)
        # Print out the answers in the right format
        output = ""
        for answer in answers:
            output += "[{} ] ".format(' '.join(map(str, answer[::-1])))

        if len(output) == 0:
            # No solution found
            print(-1)
        else:
            # Remove trailing space and print it
            print(output[:-1])

def solve_queens(n):
    return recurse_queens(n, 0, set(), set(), set())

def recurse_queens(n, curr_col, used_rows, used_diags1, used_diags2):
    # Try placing a queen in every row, and see if it works
    # used_diags1 is from top left to bottom right
    # used_diags2 is from bottom left to top right
    found_answers = []
    
    for i in range(n):
        diag1 = (n-1) + i - curr_col
        diag2 = (n-1) + curr_col - (n - i)
        if i not in used_rows and diag1 not in used_diags1 and diag2 not in used_diags2:
            # Try placing a queen here

            # If not the last column, continue DFSing
            if (curr_col != n-1):
                used_rows.add(i)
                used_diags1.add(diag1)
                used_diags2.add(diag2)
                answers = recurse_queens(n, curr_col+1, used_rows, used_diags1, used_diags2)

                # Add any found answers to the returned moves
                for answer in answers:
                    answer.append(i+1)
                    found_answers.append(answer)

                # Undo the set changes
                used_rows.remove(i)
                used_diags1.remove(diag1)
                used_diags2.remove(diag2)
            else:
                # Last column; this is an answer
                found_answers.append([i+1])
    return found_answers


if __name__ == "__main__":
    main()
