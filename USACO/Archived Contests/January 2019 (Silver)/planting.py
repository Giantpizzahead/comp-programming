'''
USACO 2019 January Contest (Silver)
Problem 1: Grass Planting
By Giantpizzahead

Guess what? I got promoted! Yay!
Now we're on to harder (but still pretty easy imo) problems.
Let's go! :)
'''


def main():
    # Input parsing
    file_in = open("planting.in", mode='r')
    input = file_in.readlines()
    file_in.close()
    num_fields = int(input[0])
    fields = {}
    for i in range(1, num_fields):
        pathway1, pathway2 = map(int, input[i].split())
        if pathway1 not in fields:
            fields[pathway1] = []
        if pathway2 not in fields:
            fields[pathway2] = []
        fields[pathway1].append(pathway2)
        fields[pathway2].append(pathway1)
    # Solving problem
    # Find the field with the most connections
    # Use that + 1 as the answer
    max_connections = 0
    for connected_to in fields.values():
        if len(connected_to) > max_connections:
            max_connections = len(connected_to)
    output = max_connections + 1
    file_out = open("planting.out", mode='w')
    file_out.write(str(output))
    file_out.close()


if __name__ == "__main__":
    main()
