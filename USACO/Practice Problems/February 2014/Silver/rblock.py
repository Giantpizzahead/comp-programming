"""
USACO 2014 February Contest (Silver)
Problem 2: Roadblock
By Giantpizzahead

This is for the AlphaStar self test.
"""

from collections import deque


def main():
    with open("rblock.in", 'r') as fin:
        fields = make_graph_dict(fin)
    # print(fields)
    shortest = find_shortest_path(fields)
    min_remove = 0
    # print(shortest)
    for p in range(1, len(shortest[0])):
        fields[shortest[0][p]][shortest[0][p-1]] *= 2
        fields[shortest[0][p-1]][shortest[0][p]] *= 2
        edited_shortest = find_shortest_path(fields)
        # print("Doubling {}: {}".format((shortest[0][p], shortest[0][p-1]), edited_shortest))
        if edited_shortest[1] - shortest[1] > min_remove:
            min_remove = edited_shortest[1] - shortest[1]
        fields[shortest[0][p]][shortest[0][p - 1]] = round(fields[shortest[0][p]][shortest[0][p - 1]] / 2)
        fields[shortest[0][p - 1]][shortest[0][p]] = round(fields[shortest[0][p - 1]][shortest[0][p]] / 2)
    # print(min_remove)
    with open("rblock.out", 'w') as fout:
        fout.write(str(min_remove))

'''
def find_all_paths(fields):
    # Make a priority queue
    queue = deque([1])
    # Keep track of all paths
    paths = {}
    # Keep track of all evaluated nodes
    evaluated = set()
    target = len(fields)
    while queue:
        # Get the next node to check
        f = queue.pop()
        for of, dist in fields[f].items():
            # Check if other node has been evaluated
            # If not, evaluate it
            if of not in evaluated:
                # Add this path to the node
                    best_dist[of] = (curr_dist + dist, f)
                    # Also add it to the queue
                    queue.append(of)
                    # Remove it from evaluated since it needs to be reevaluated
                    evaluated.discard(of)
        # Current node has been evaluated
        evaluated.add(f)
    # Guaranteed path found once loop has been exited
    # Trace the shortest path back to the start
    path = [target]
    next = best_dist[target][1]
    while next != -1:
        path.append(next)
        next = best_dist[next][1]
    return path[::-1]
'''

def find_shortest_path(fields):
    # Make a priority queue
    queue = deque([1])
    # Keep track of the best distance found for each node
    # and which node that distance came from
    best_dist = {1: (0, -1)}
    # Keep track of all evaluated nodes
    evaluated = set()
    target = len(fields)
    final_dist = 999999999
    while queue:
        # Get the next node to check
        f = queue.pop()
        # If the next node is the ending node, we're done
        curr_dist = best_dist[f][0]
        # If current distance is greater than already found distance,
        # there's no point in checking further
        if curr_dist >= final_dist:
            continue
        for of, dist in fields[f].items():
            # Check if other node has been evaluated
            # If not, evaluate it
            # if of not in evaluated:
            # Check if any path has been found to the other node yet
            # If path is already there, check if this one is better
            if of not in best_dist or best_dist[of][0] > curr_dist + dist:
                # Add this path to the node
                best_dist[of] = (curr_dist + dist, f)
                # If node is ending node, track the best distance to end
                if of == target:
                    if curr_dist + dist < final_dist:
                        final_dist = curr_dist + dist
                else:
                    # Also add it to the queue
                    queue.append(of)
                    # Remove it from evaluated since it needs to be reevaluated
                    evaluated.discard(of)
        # Current node has been evaluated
        evaluated.add(f)
    # Guaranteed path found once loop has been exited
    # Trace the shortest path back to the start
    path = [target]
    next = best_dist[target][1]
    while next != -1:
        path.append(next)
        next = best_dist[next][1]
    return path[::-1], final_dist


def make_graph_dict(fin):
    n, m = [int(i) for i in fin.readline().strip().split()]
    fields = {}
    for i in range(n):
        fields[i+1] = {}
    for i in range(m):
        a, b, l = [int(x) for x in fin.readline().strip().split()]
        fields[a][b] = l
        fields[b][a] = l
    return fields


if __name__ == "__main__":
    main()