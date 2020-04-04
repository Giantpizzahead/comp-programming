/*
Solution: Keep a segment tree, along with the start and end ranges for each node. To update, update the range that
the node contains in the segment tree (log N). To query enjoyment from node a to b, do query(a) ^ query(b) ^ LCA(a, b).
This works due to the properties of XOR (log N).

Runtime: O(N * log(N))
*/

import javax.swing.text.Segment;
import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class cowland {
    int N, Q, currGenIndex;
    int[] enjoyment, nodeDepth, segSRange, segERange;
    int[][] lcaArr;
    boolean[] visited;
    ArrayList<Integer>[] graph;
    SegmentTree segTree;

    cowland() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cowland.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());

        enjoyment = new int[N];
        st = new StringTokenizer(fin.readLine());
        for (int i = 0; i < N; i++) {
            enjoyment[i] = Integer.parseInt(st.nextToken());
        }

        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        int n1, n2;
        for (int i = 0; i < N - 1; i++) {
            st = new StringTokenizer(fin.readLine());
            n1 = Integer.parseInt(st.nextToken()) - 1;
            n2 = Integer.parseInt(st.nextToken()) - 1;
            graph[n1].add(n2);
            graph[n2].add(n1);
        }

        // Root the graph at node 0, and generate the segment tree using a DFS
        nodeDepth = new int[N];
        segSRange = new int[N];
        segERange = new int[N];
        visited = new boolean[N];
        visited[0] = true;
        currGenIndex = 1;
        lcaArr = new int[20][N];
        genSegTree(0, 0, 0);

        // Now fill the segment tree with values
        /*
        System.out.println(Arrays.toString(segSRange));
        System.out.println(Arrays.toString(segERange));
        System.out.println("segTree size: " + currGenIndex);
         */
        segTree = new SegmentTree(currGenIndex);
        for (int i = 0; i < N; i++) {
            segTree.update(segSRange[i], segERange[i], enjoyment[i]);
            /*
            for (int j = 0; j < N; j++) System.out.print(segTree.query(j) + " ");
            System.out.println("update");
            System.out.println(Arrays.toString(segTree.vals));
            System.out.println(Arrays.toString(segTree.delta));
             */
        }

        // Gen LCA array
        for (int i = 1; i < 20; i++) {
            for (int j = 0; j < N; j++) {
                lcaArr[i][j] = lcaArr[i-1][lcaArr[i-1][j]];
            }
        }

        // Handle queries
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("cowland.out")));
        int a, b, c;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken());
            if (a == 1) {
                // Update
                b = Integer.parseInt(st.nextToken()) - 1;
                c = Integer.parseInt(st.nextToken());
                segTree.update(segSRange[b], segERange[b], enjoyment[b] ^ c);
                enjoyment[b] = c;
            } else {
                // Query
                b = Integer.parseInt(st.nextToken()) - 1;
                c = Integer.parseInt(st.nextToken()) - 1;
                int result = segTree.query(segSRange[b]) ^ segTree.query(segSRange[c]) ^ enjoyment[findLCA(b, c)];
                fout.println(result);
            }
        }
        fin.close();
        fout.close();
    }

    int findLCA(int a, int b) {
        int n1 = (nodeDepth[a] < nodeDepth[b]) ? b : a;
        int n2 = (nodeDepth[a] < nodeDepth[b]) ? a : b;

        // First, move both nodes to an equal depth
        // n1 might need to move up
        int toMove = nodeDepth[n1] - nodeDepth[n2];
        for (int i = 19; i >= 0; i--) {
            if (toMove >= 1 << i) {
                n1 = lcaArr[i][n1];
                toMove -= 1 << i;
            }
        }

        // Special case: They're on the same branch
        if (n1 == n2) {
            return n1;
        }

        // Find LCA
        for (int i = 19; i >= 0; i--) {
            if (lcaArr[i][n1] != lcaArr[i][n2]) {
                n1 = lcaArr[i][n1];
                n2 = lcaArr[i][n2];
            }
        }

        return lcaArr[0][n1];
    }

    void genSegTree(int node, int parent, int depth) {
        // Neighbors
        for (int n : graph[node]) {
            if (!visited[n]) {
                // Go down this branch
                segSRange[n] = currGenIndex++;
                visited[n] = true;
                genSegTree(n, node, depth + 1);
            }
        }

        segERange[node] = currGenIndex - 1;
        lcaArr[0][node] = parent;
        nodeDepth[node] = depth;
    }

    public static void main(String[] args) throws IOException {
        new cowland();
    }
}

class SegmentTree {
    int size;
    int[] lb, ub, vals, delta;

    SegmentTree(int size) {
        this.size = size;
        lb = new int[size * 4 + 1];
        ub = new int[size * 4 + 1];
        vals = new int[size * 4 + 1];
        delta = new int[size * 4 + 1];
        initTree(1, 0, size - 1);
    }

    void update(int min, int max, int value) {
        update(1, min, max, value);
    }

    void update(int node, int min, int max, int value) {
        if (lb[node] > max || ub[node] < min) return;
        else if (lb[node] >= min && ub[node] <= max) {
            // Completely in range
            delta[node] ^= value;
            return;
        }

        // Partially in range
        update(node * 2, min, max, value);
        update(node * 2 + 1, min, max, value);
    }

    int query(int i) {
        return query(1, i, i);
    }

    int query(int min, int max) {
        return query(1, min, max);
    }

    int query(int node, int min, int max) {
        // First, propagate changes
        if (lb[node] != ub[node]) {
            delta[node * 2] ^= delta[node];
            delta[node * 2 + 1] ^= delta[node];
        }
        vals[node] ^= delta[node];
        delta[node] = 0;

        if (lb[node] > max || ub[node] < min) return 0;
        else if (lb[node] >= min && ub[node] <= max) {
            // Completely in range
            return vals[node];
        }

        // Partially in range
        return query(node * 2, min, max) ^ query(node * 2 + 1, min, max);
    }

    void initTree(int node, int lower, int upper) {
        lb[node] = lower;
        ub[node] = upper;
        if (lower != upper) {
            initTree(node * 2, lower, (lower + upper) / 2);
            initTree(node * 2 + 1, (lower + upper) / 2 + 1, upper);
        }
    }
}