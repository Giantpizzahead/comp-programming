from collections import deque


board = []
evaluated = set()
to_check = deque()
board_size = 0
curr_perimeter = 0
curr_area = 0

def check_neighbors(r, c):
    '''
    Kinda 'parent' function that keeps track of all neighbors it needs
    to check.
    '''
    global to_check
    to_check.append((r, c))
    while to_check:
        checking = to_check.pop()
        check_neighbors_ind(checking[0], checking[1])


def check_neighbors_ind(r, c):
    if r * board_size + c in evaluated:
        return
    global curr_perimeter, curr_area, to_check
    '''Check neighbor cells for #s using recursion. Update perim and area.'''
    evaluated.add(r * board_size + c)
    curr_area += 1
    if r != 0:
        check = board[r-1][c]
        if check == '#':
            to_check.append((r-1, c))
        else:
            curr_perimeter += 1
    else:
        curr_perimeter += 1
    if r != board_size - 1:
        check = board[r+1][c]
        if check == '#':
            to_check.append((r+1, c))
        else:
            curr_perimeter += 1
    else:
        curr_perimeter += 1
    if c != 0:
        check = board[r][c-1]
        if check == '#':
            to_check.append((r, c-1))
        else:
            curr_perimeter += 1
    else:
        curr_perimeter += 1
    if c != board_size - 1:
        check = board[r][c+1]
        if check == '#':
            to_check.append((r, c+1))
        else:
            curr_perimeter += 1
    else:
        curr_perimeter += 1


def solve():
    global curr_perimeter, curr_area, board
    greatest_area = 0
    greatest_perimeter = 0
    for r, row in enumerate(board):
        for c, cell in enumerate(row):
            if r * board_size + c not in evaluated and cell == '#':
                curr_perimeter = 0
                curr_area = 0
                check_neighbors(r, c)
                if curr_area > greatest_area:
                    greatest_area = curr_area
                    greatest_perimeter = curr_perimeter
                elif curr_area == greatest_area and curr_perimeter < greatest_perimeter:
                    greatest_perimeter = curr_perimeter
    return (greatest_area, greatest_perimeter)


def main():
    global board_size, board
    # Input parsing
    with open("perimeter.in", 'r') as input:
        board_size = int(input.readline().strip())
        '''
        for i in range(board_size):
            line = []
            eval_line = []
            for j in input.readline().strip():
                line.append(j)
                eval_line.append(0)
            board.append(line)
            evaluated.append(eval_line)
        '''
        board = [l.strip() for l in input.readlines()]

    # print(board)
    # print(evaluated)
    answer = solve()
    with open("perimeter.out", 'w') as output:
        output.write(str(answer[0]) + ' ' + str(answer[1]) + "\n")


main()
