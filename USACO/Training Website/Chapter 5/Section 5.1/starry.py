"""
ID: sunnyky1
LANG: PYTHON3
TASK: starry
"""

# Clusters are represented by a set of coordinates.


def root_cluster(cluster):
    """Returns a new cluster with the leftmost and topmost stars at the 0th row/column."""
    min_i = min(c[0] for c in cluster)
    min_j = min(c[1] for c in cluster)
    return {(c[0] - min_i, c[1] - min_j) for c in cluster}


def rotate_cluster(cluster):
    """Returns a new cluster rotated clockwise by 90 degrees and rooted."""
    return root_cluster({(c[1], -c[0]) for c in cluster})


def flip_cluster(cluster):
    """Returns a new cluster flipped horizontally and rooted."""
    return root_cluster({(c[0], -c[1]) for c in cluster})


def is_similar(cluster1, cluster2):
    """Returns true if the given clusters are similar."""
    # Root both clusters for comparing
    cluster1 = root_cluster(cluster1)
    cluster2 = root_cluster(cluster2)
    # Try all rotations and flips
    for i in range(8):
        if cluster1 == cluster2:
            return True
        if i == 3:
            cluster1 = flip_cluster(cluster1)
        elif i != 7:
            cluster1 = rotate_cluster(cluster1)
    return False


def find_clusters(map):
    """Finds all clusters on the given map."""
    H, W = len(map), len(map[0])
    visited = [[False for _ in range(W)] for _ in range(H)]
    def dfs(i, j, cluster):
        visited[i][j] = True
        cluster.add((i, j))
        for ci in (-1, 0, 1):
            for cj in (-1, 0, 1):
                ni, nj = i+ci, j+cj
                if ni < 0 or nj < 0 or ni >= H or nj >= W or \
                   map[ni][nj] != '1' or visited[ni][nj]:
                    continue
                dfs(ni, nj, cluster)
    
    # DFS to find all clusters
    clusters = []
    for i in range(H):
        for j in range(W):
            if map[i][j] != '1' or visited[i][j]:
                continue
            curr_cluster = set()
            dfs(i, j, curr_cluster)
            clusters.append(curr_cluster)
    return clusters


def main():
    with open("starry.in", "r") as fin:
        W = int(fin.readline())
        H = int(fin.readline())
        A = [list(fin.readline().strip()) for _ in range(H)]
    
    clusters = find_clusters(A)
    print(clusters)
    seen_clusters = []
    for cluster1 in clusters:
        # Find a label for this cluster
        label1 = None
        for cluster2, label2 in seen_clusters:
            if is_similar(cluster1, cluster2):
                label1 = label2
                break
        if label1 is None:
            label1 = chr(ord('a') + len(seen_clusters))
            seen_clusters.append((cluster1, label1))
        # Put labels on the map
        for c in cluster1:
            A[c[0]][c[1]] = label1
    
    with open("starry.out", "w") as fout:
        fout.writelines(["".join(row) + "\n" for row in A])


if __name__ == "__main__":
    main()
