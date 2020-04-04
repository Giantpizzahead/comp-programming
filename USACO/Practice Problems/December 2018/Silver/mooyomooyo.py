'''
USACO 2018 December Contest (Silver)
Problem 3: Mooyo Mooyo
By Giantpizzahead

So, the bronze problems were too easy. Guess what?
We're going to silver! :)
This still looks easy though. Oh well. Let's give it a shot!

Ok, it was easy, but very time consuming. I mean, you only have 4 hours
for the actual thing, and this problem took me about 50 minutes. Soooo
that's a bit worrying. Still, it was easy, so I might try one in the gold
division.
'''


def solve(board, needed_cells):
    '''
    Solves the problem.
    Method 1: Use [x][y], [x][y+1], [x+1][y], etc. to check
    if same color haybales are next to each other. Use
    recursion to find all linked ones. Gravity should start from
    the bottom, and go up, moving the entire column above the 0
    downwards.
    Actually it doesn't matter where gravity starts from, so it's
    going to start from the top.
    '''
    something_happened = True
    # print("Starting board:")
    # print_board(board)
    while something_happened:
        something_happened = False
        # Step 1: Remove connected cells
        cells_to_remove = check_matches(board, needed_cells)
        for cell in cells_to_remove:
            board[cell[0]][cell[1]] = 'X'
        # print("Board after removing cells:")
        # print_board(board)
        # Step 2: Gravity
        gravity_changed = board_gravity(board)
        # print("Board after gravity:")
        # print_board(board)
        if gravity_changed:
            something_happened = True
    # print("Final board:")
    # print_board(board)


def check_matches(board, needed_cells):
    '''
    Checks to see if there are any groups of connected cells
    that need to be removed. Returns every x/y coordinate of
    cells that need to be removed (in a tuple of tuples).
    '''
    cells_to_remove = []
    # Iterate through every cell
    for row_i, row in enumerate(board):
        for col_i, cell in enumerate(row):
            if cell != 0 and (row_i, col_i) not in cells_to_remove:
                connected_cells = [(row_i, col_i)]
                look_for_connected(board, row_i, col_i, cell, connected_cells)
                if len(connected_cells) >= needed_cells:
                    cells_to_remove += connected_cells
    # print("Cells to remove:", cells_to_remove)
    return cells_to_remove


def look_for_connected(board, row_i, col_i, color, connected_cells):
    '''
    Uses recursion / [x][y] to look for connected cells.
    Adds x and y coordinates of found connected cells to the
    connected_cells list.
    '''
    # Up
    if row_i != 0 and board[row_i-1][col_i] == color:
        if (row_i-1, col_i) not in connected_cells:
            connected_cells.append((row_i-1, col_i))
            look_for_connected(board, row_i-1, col_i, color, connected_cells)
    # Down
    if row_i != len(board) - 1 and board[row_i+1][col_i] == color:
        if (row_i+1, col_i) not in connected_cells:
            connected_cells.append((row_i+1, col_i))
            look_for_connected(board, row_i+1, col_i, color, connected_cells)
    # Left
    if col_i != 0 and board[row_i][col_i-1] == color:
        if (row_i, col_i-1) not in connected_cells:
            connected_cells.append((row_i, col_i-1))
            look_for_connected(board, row_i, col_i-1, color, connected_cells)
    # Right
    if col_i != 9 and board[row_i][col_i+1] == color:
        if (row_i, col_i+1) not in connected_cells:
            connected_cells.append((row_i, col_i+1))
            look_for_connected(board, row_i, col_i+1, color, connected_cells)


def board_gravity(board):
    '''Makes gravity affect the board.'''
    did_something = False
    for row_i, row in enumerate(board):
        for col_i, cell in enumerate(row):
            if cell == 'X':
                did_something = True
                move_column_down(board, row_i, col_i)
    return did_something


def move_column_down(board, row_i, col_i):
    '''Moves a column of the board down, starting from the given row.'''
    if row_i != 0:
        board[row_i][col_i] = board[row_i-1][col_i]
        if row_i != 1 and board[row_i-2][col_i] != 0:
            board[row_i-1][col_i] = 'X'
        else:
            board[row_i-1][col_i] = 0
        move_column_down(board, row_i-1, col_i)


def print_board(board):
    '''Prints the format board.'''
    print(format_board(board))


def format_board(board):
    '''Makes the board look nice.'''
    output = ""
    for row_num, row in enumerate(board):
        output += ''.join(map(str, row))
        if not row_num == len(board) - 1:
            output += "\n"
    return output


def main():
    # Input parsing
    file_in = open("mooyomooyo.in", mode='r')
    input = file_in.readlines()
    file_in.close()
    board_height, needed_cells = map(int, input[0].split())
    board = []
    for row in range(1, board_height + 1):
        board.append([int(n) for n in input[row][:-1]])
    solve(board, needed_cells)
    output = format_board(board)
    file_out = open("mooyomooyo.out", mode='w')
    file_out.write(output)
    file_out.close()


if __name__ == "__main__":
    main()
