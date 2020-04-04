'''
USACO 2019 January Contest (Silver)
Problem 2: Icy Perimeter
By Giantpizzahead

The first problem took about as long as the first problem in the
bronze divison did. I know the later problems are harder though,
so hopefully they aren't too bad this time.
This one already looks hard, so I guess we'll see. Good luck me!
'''

next_free_blob = 1
connected_blobs = []
blobs = {}
evaluated = {}
board = []


def combined_solve():
    '''Combines input parsing and solving.'''
    file_in = open("perimeter.in", mode='r')
    input = file_in.readlines()
    file_in.close()
    size = int(input[0])
    for row in range(size):
        board.append([])
        for col, cell in enumerate(input[row+1][:-1].strip()):
            board[row].append(cell)
            if cell == '#':
                combined_handle(row, col, size)
            else:
                handle_empty(row, col, size)
    # Combine blobs that should be combined
    print(blobs)
    didDo = True
    while didDo:
        didDo = False
        print("hi")
        for combine in connected_blobs[::-1]:
            combine1 = min(combine)
            combine2 = max(combine)
            if blobs[combine2][0] != 0 or blobs[combine2][1] != 0:
                didDo = True
            blobs[combine1][0] += blobs[combine2][0]
            blobs[combine1][1] += blobs[combine2][1]
            blobs[combine2][0] = 0
            blobs[combine2][1] = 0
    # Look for biggest / lowest perimeter blob
    print(blobs)
    max_area = 0
    best_blobs = []
    for blob in blobs.values():
        if blob[0] > max_area:
            max_area = blob[0]
            best_blobs = [blob]
        elif blob[0] == max_area:
            best_blobs.append(blob)
    best_blob = min(best_blobs, key=lambda b: b[1])
    output = str(int(best_blob[0])) + ' ' + str(int(best_blob[1]))
    # print(output)
    file_out = open("perimeter.out", mode='w')
    file_out.write(output + "\n")
    file_out.close()


def handle_empty(row, col, board_size):
    # Only used to add perimeter if needed
    if (row, col-1) in evaluated:
        blobs[evaluated[(row, col-1)]][1] += 1
    if (row-1, col) in evaluated:
        blobs[evaluated[(row-1, col)]][1] += 1


def combined_handle(row, col, board_size):
    global next_free_blob

    blob = 0
    if (row-1, col) in evaluated:
        # If cell on top is evaluated, join the current cell with it
        blob = evaluated[(row-1, col)]
        # print("Top blob of", blob)
    if (row, col-1) in evaluated:
        if blob != 0:
            # Combine the two blobs if they are different
            other_blob = evaluated[(row, col-1)]
            # print("Combining blob", blob, "with", other_blob)
            if other_blob != blob:
                connected_blobs.append((blob, other_blob))
        else:
            blob = evaluated[(row, col-1)]
            # print("Left blob of", blob)
    if blob == 0:
        # Not connected to any other #s; create a new blob
        # print("New blob")
        blob = next_free_blob
        next_free_blob += 1
        blobs[blob] = [0, 0]
    evaluated[(row, col)] = blob
    # Add to area and perimeter of current blob
    blobs[blob][0] += 1
    if row == 0 or board[row-1][col] == '.':
        blobs[blob][1] += 1
    if col == 0 or board[row][col-1] == '.':
        blobs[blob][1] += 1
    if col == board_size - 1:
        blobs[blob][1] += 1
    if row == board_size - 1:
        blobs[blob][1] += 1


def handle_hashtag(row, col):
    global next_free_blob

    blob = 0
    if (row-1, col) in evaluated:
        # If cell on top is evaluated, join the current cell with it
        blob = evaluated[(row-1, col)]
    if (row, col-1) in evaluated:
        if blob != 0:
            # Combine the two blobs if they are different
            other_blob = evaluated[(row, col-1)]
            if other_blob != blob:
                connected_blobs.append((blob, other_blob))
        else:
            blob = evaluated[(row, col-1)]
    if blob == 0:
        # Not connected to any other #s; create a new blob
        blob = next_free_blob
        next_free_blob += 1
        blobs[blob] = [0, 0]
    evaluated[(row, col)] = blob
    # Add to area and perimeter of current blob
    blobs[blob][0] += 1
    if row == 0 or board[row-1][col] == '.':
        blobs[blob][1] += 1
    if row == len(board) - 1 or board[row+1][col] == '.':
        blobs[blob][1] += 1
    if col == 0 or board[row][col-1] == '.':
        blobs[blob][1] += 1
    if col == len(board) - 1 or board[row][col+1] == '.':
        blobs[blob][1] += 1


def solve():
    '''
    Method 1: Look through the entire board. When a # is found,
    look for the adjacent #s, and recursively go through all the
    connected ones to find the whole blob. While looking at the
    cells adjacent to the #, if a . is found, add 1 to that
    individual cell's perimeter. Once a cell is evaluated, don't
    look at it again. Store dictionaries for each cell's perimeter,
    whether each cell has been evaluated, and store a list of
    blobs, with their total area / perimeter. Return the blob
    with the greatest area (if same area, one with lowest perimeter).
    Revised: No need to store each cell's perimeter.
    Revised: Instead of using recursion (since that has a max recursion
    limit issue), keep track of which blob each cell is in, and record
    each blob's current area and perimeter. Add to these as new neighbor
    cells are found.
    '''
    for row, raw_row in enumerate(board):
        for col, cell in enumerate(raw_row):
            if cell == '#':
                handle_hashtag(row, col)
    # print(blobs)
    # print(evaluated)
    # print(connected_blobs)
    # Combine blobs that should be combined
    for combine in connected_blobs[::-1]:
        combine1 = min(combine)
        combine2 = max(combine)
        blobs[combine1][0] += blobs[combine2][0]
        blobs[combine1][1] += blobs[combine2][1]
        blobs[combine2][0] = 0
        blobs[combine2][1] = 0
    # Look for biggest / lowest perimeter blob
    max_area = 0
    best_blobs = []
    for blob in blobs.values():
        if blob[0] > max_area:
            max_area = blob[0]
            best_blobs = [blob]
        elif blob[0] == max_area:
            best_blobs.append(blob)
    best_blob = min(best_blobs, key=lambda b: b[1])
    # print(blobs)
    return str(best_blob[0]) + ' ' + str(best_blob[1])


'''
def __handle_hashtag(row, col):
    ''Handles a hashtag.''
    global blob_area
    global blob_perimeter
    blob_area = 0
    blob_perimeter = 0
    __hashtag_rec(row, col)
    # print("Starting at", row, col, "\nStats:", blob_area, blob_perimeter)
    blobs.append((blob_area, blob_perimeter))


def __hashtag_rec(row, col):
    ''Recursion for hashtag handling.''
    global blob_area
    global blob_perimeter
    has_been_evaluated[(row, col)] = True
    blob_area += 1
    if (row-1, col) not in has_been_evaluated:
        if row != 0 and board[row-1][col] == '#':
            hashtag_rec(row-1, col)
        else:
            blob_perimeter += 1
    if (row+1, col) not in has_been_evaluated:
        if row != len(board) - 1 and board[row+1][col] == '#':
            hashtag_rec(row+1, col)
        else:
            blob_perimeter += 1
    if (row, col-1) not in has_been_evaluated:
        if col != 0 and board[row][col-1] == '#':
            hashtag_rec(row, col-1)
        else:
            blob_perimeter += 1
    if (row, col+1) not in has_been_evaluated:
        if col != len(board) - 1 and board[row][col+1] == '#':
            hashtag_rec(row, col+1)
        else:
            blob_perimeter += 1
'''


def main():
    # Possible speedup: Combine input parsing and solving
    # method to avoid looping through all cells twice
    # Input parsing
    file_in = open("perimeter.in", mode='r')
    input = file_in.readlines()
    file_in.close()
    size = int(input[0])
    for i in range(1, size+1):
        board.append([c for c in input[i][:-1]])
    output = solve()
    print(output)
    file_out = open("perimeter.out", mode='w')
    file_out.write(output)
    file_out.close()


def format_board():
    '''Format the board into a nice grid shape.'''
    formatted_board = ''
    for index, row in enumerate(board):
        formatted_board += ''.join(row)
        if index != len(board) - 1:
            formatted_board += "\n"
    return formatted_board


if __name__ == "__main__":
    combined_solve()
