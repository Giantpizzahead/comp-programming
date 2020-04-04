/*
Solution: Label the nodes in DFS order (1-indexed). Iterate through all must-leave-before edges.
1st node = One that must leave before the 2nd node
If LCA of the 2 nodes is equal to one of the nodes (same subtree):
    If height of 1st node > 2nd node, set the range [1, 1st node's ID] and (max label in 1st node's
    subtree, N) to 0 (increment "zero flag" in those ranges using a BIT).
    Else: Set "subtree 0" mark on 1st node to true
Else:
    Set "subtree 0" mark on 1st node to true

Do a final DFS to find all 0s and 1s, querying the "zero flag" BIT and checking whether subtree 0
mark has been set for each node.

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class gathering {
    int N, M;
    ArrayList<Integer>[] graph;
    HashSet<Integer>[] mustLeaveGraph;
    Edge[] mustLeaveEdges;
    int[] iToLabel, iToMaxLabel, depth, visitedCycles;
    int[][] lcaArr;
    boolean[] subTree0, visited, canBeLast;
    BIT range0;
    final int LCA_ARR_SIZE = 17;

    gathering() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("gathering.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        mustLeaveGraph = new HashSet[N];
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<>(2);
            mustLeaveGraph[i] = new HashSet<>(2);
        }
        mustLeaveEdges = new Edge[M];
        int a, b;
        for (int i = 0; i < N - 1; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graph[a].add(b);
            graph[b].add(a);
        }
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            mustLeaveEdges[i] = new Edge(a, b);
            mustLeaveGraph[a].add(b);
        }
        fin.close();

        // First, check if there are cycles in the given must leave edges
        // If any cycles exist, then everything is false
        if (cyclesExist()) {
            // Print false for everything
            PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("gathering.out")));
            for (int i = 0; i < N; i++) fout.println(0);
            fout.close();
            return;
        }

        // Generate labels / LCA array
        iToLabel = new int[N];
        iToMaxLabel = new int[N];
        depth = new int[N];
        lcaArr = new int[LCA_ARR_SIZE][N];
        labelNodes(0, 1, 0, 0);
        genLCAArray();

        // System.out.println(Arrays.toString(iToLabel));

        // Handle each must-leave-before edge
        handleEdges();

        // Do a final DFS
        canBeLast = new boolean[N];
        visited = new boolean[N];
        visited[0] = true;
        finalDFS(0, false);

        /*
        System.out.println(Arrays.toString(subTree0));
        for (int i = 1; i <= N; i++) {
            System.out.print(range0.query(i) + " ");
        }
        System.out.println();
        System.out.println("Answers:");
        System.out.println(Arrays.toString(canBeLast));
        */

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("gathering.out")));
        for (boolean bool : canBeLast) fout.println(bool ? 1 : 0);
        fout.close();
    }

    boolean cyclesExist() {
        visitedCycles = new int[N];
        int currCycle = 1;
        for (int i = 0; i < N; i++) {
            if (visitedCycles[i] == 0) {
                visitedCycles[i] = currCycle;
                if (dfsCycles(i, currCycle, new HashSet<Integer>())) return true;
            }
        }
        return false;
    }

    boolean dfsCycles(int n, int currCycle, HashSet<Integer> intVisited) {
        if (intVisited.contains(n)) return true;
        intVisited.add(n);
        for (int o : mustLeaveGraph[n]) {
            if (intVisited.contains(o)) return true;
            else if (visitedCycles[o] != 0) continue;
            visitedCycles[o] = currCycle;
            if (dfsCycles(o, currCycle, intVisited)) return true;
        }
        intVisited.remove(n);
        return false;
    }

    void finalDFS(int currN, boolean subtreeIs0) {
        if (subTree0[iToLabel[currN]]) subtreeIs0 = true;

        if (!subtreeIs0 && range0.query(iToLabel[currN]) == 0) {
            // Can be last
            canBeLast[currN] = true;
        }

        for (int o : graph[currN]) {
            if (!visited[o]) {
                visited[o] = true;
                finalDFS(o, subtreeIs0);
            }
        }
    }

    /*
    If LCA of the 2 nodes is equal to one of the nodes (same subtree):
        If height of 1st node > 2nd node, set the range [1, 1st node's ID] and (max label in 1st node's
        subtree, N) to 0 (increment "zero flag" in those ranges using a BIT).
        Else: Set "subtree 0" mark on 1st node to true
    Else:
        Set "subtree 0" mark on 1st node to true
     */
    void handleEdges() {
        subTree0 = new boolean[N + 1];
        range0 = new BIT(N);
        for (Edge e : mustLeaveEdges) {
            int lca = findLCA(e.a, e.b);
            // System.out.println("LCA of " + e.a + " and " + e.b + " is " + lca);
            if (lca == e.a || lca == e.b) {
                // Nodes are in same subtree
                if (depth[e.a] < depth[e.b]) {
                    // 1st node is higher; set all subtrees to be 0 except for the one containing
                    // the 2nd node
                    int nonLCA = (lca == e.a) ? e.b : e.a;
                    int containNode = findContaining(lca, nonLCA);
                    range0.increment(1, iToLabel[containNode] - 1);
                    range0.increment(iToMaxLabel[containNode] + 1, N);
                } else {
                    // 2nd node is higher; set subtree0 mark
                    subTree0[iToLabel[e.a]] = true;
                }
            } else {
                // Nodes not in same subtree
                subTree0[iToLabel[e.a]] = true;
            }
        }
    }

    int findContaining(int lca, int o) {
        // Move the other node up until it's 1 apart from the LCA
        int toMove = depth[o] - depth[lca];
        for (int i = LCA_ARR_SIZE - 1; i >= 0; i--) {
            if (toMove - 1 >= 1 << i) {
                o = lcaArr[i][o];
                toMove -= 1 << i;
            }
        }
        return o;
    }

    int findLCA(int a, int b) {
        // Get both nodes on the same height first
        int n1 = (depth[a] > depth[b]) ? a : b;
        int n2 = (depth[a] > depth[b]) ? b : a;

        // n1 might need to move up
        int toMove = depth[n1] - depth[n2];
        for (int i = LCA_ARR_SIZE - 1; i >= 0; i--) {
            if (toMove >= 1 << i) {
                n1 = lcaArr[i][n1];
                toMove -= 1 << i;
            }
        }

        // Find LCA
        if (n1 == n2) return n1;
        for (int i = LCA_ARR_SIZE - 1; i >= 0; i--) {
            if (lcaArr[i][n1] != lcaArr[i][n2]) {
                n1 = lcaArr[i][n1];
                n2 = lcaArr[i][n2];
            }
        }
        return lcaArr[0][n1];
    }

    int labelNodes(int currN, int currLabel, int parent, int currD) {
        iToLabel[currN] = currLabel++;
        depth[currN] = currD;
        lcaArr[0][currN] = parent;
        for (int o : graph[currN]) {
            if (iToLabel[o] != 0) continue;
            currLabel = labelNodes(o, currLabel, currN, currD + 1);
        }
        iToMaxLabel[currN] = currLabel - 1;
        return currLabel;
    }

    void genLCAArray() {
        for (int i = 1; i < LCA_ARR_SIZE; i++) {
            for (int j = 0; j < N; j++) lcaArr[i][j] = lcaArr[i-1][lcaArr[i-1][j]];
        }
    }

    public static void main(String[] args) throws IOException {
        new gathering();
    }
}

class BIT {
    int size;
    int[] v;

    BIT(int size) {
        this.size = size;
        v = new int[size + 1];
    }

    void increment(int lb, int ub) {
        if (lb > ub) return;
        update(lb, 1);
        update(ub + 1, -1);
    }

    void update(int end, int val) {
        while (end <= size) {
            v[end] += val;
            end += Integer.lowestOneBit(end);
        }
    }

    int query(int i) {
        int result = 0;
        while (i != 0) {
            result += v[i];
            i -= Integer.lowestOneBit(i);
        }
        return result;
    }
}

class Edge {
    int a, b;
    Edge(int a, int b) {
        this.a = a;
        this.b = b;
    }
}