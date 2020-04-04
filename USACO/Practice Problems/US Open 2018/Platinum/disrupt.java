/*
Solution: The pathways that can be used to reconnect the farm must create a cycle containing
the edge to be blocked. So, you can find the edges in the cycle created by each replacement
pathway, and update the min cost of those pathways. In a tree, this can be done using the LCA
of the two nodes the pathway connects. Use heavy-light decomposition to update the min cost
of each pathway in logarithmic time. Do a linear scan at the end to find the minimum costs.

Runtime: O(M * log(N))
*/

import javax.swing.text.Segment;
import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class disrupt {
    int N, M;
    int[] childrenCount, depth, lcaSteps;
    int[][] lcaArr;
    boolean[] visited;
    Edge[] treeUp;
    HashMap<Long, Integer> edgeToIndex;
    ArrayList<Integer>[] unrooted;
    ArrayList<Edge>[] treeDown;
    ArrayList<SegmentTree> heavySegTrees;
    Replacement[] replacements;
    final int INF = 1000000007;

    disrupt() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("disrupt.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        unrooted = new ArrayList[N];
        edgeToIndex = new HashMap<>();
        for (int i = 0; i < N; i++) unrooted[i] = new ArrayList<>(3);
        int a, b;
        for (int i = 0; i < N-1; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            unrooted[a].add(b);
            unrooted[b].add(a);
            edgeToIndex.put(hash(a, b), i);
        }
        replacements = new Replacement[M];
        int c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken());
            replacements[i] = new Replacement(a, b, c);
        }
        fin.close();

        // Root the tree at 0 & Generate heavy and light edges
        childrenCount = new int[N];
        depth = new int[N];
        visited = new boolean[N];
        visited[0] = true;
        treeDown = new ArrayList[N];
        for (int i = 0; i < N; i++) treeDown[i] = new ArrayList<>(3);
        treeUp = new Edge[N];
        heavySegTrees = new ArrayList<>();
        generateTree(0, 0, 0);
        generateEdges(0, 0, 0, 0);

        /*
        System.out.println(Arrays.toString(childrenCount));
        System.out.println(heavySegTrees);
        System.out.println(Arrays.toString(treeDown));
        System.out.println(Arrays.toString(treeUp));
        */

        /*
        SegmentTree stree = new SegmentTree(11);
        stree.update(0, 6, 8);
        stree.update(2, 9, 6);
        stree.update(4, 7, 3);
        for (int i = 0; i < 11; i++) System.out.println(stree.query(i));
         */

        // Find cycles formed by each edge
        // First, generate an LCA array to find the LCA of two nodes quickly
        genLCAArray();
        
        // Now, find cycles formed by each edge, updating the segment trees after each one
        findCycles();

        // if (N > 100) treeUp[-2] = null;

        // Finally, fill the final min array, and print the answers
        int[] minCost = new int[N-1];
        getAnswers(0, minCost);

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("disrupt.out")));
        for (int n : minCost) fout.println((n == INF) ? -1 : n);
        fout.close();
    }

    void getAnswers(int node, int[] minCost) {
        for (Edge edge : treeDown[node]) {
            int index = edgeToIndex.get(hash(node, edge.n));
            SegmentTree stree = heavySegTrees.get(edge.sid);
            minCost[index] = stree.query(stree.tailDepth - depth[node] - 1);
            getAnswers(edge.n, minCost);
        }
    }

    long hash(int a, int b) {
        return (long) Math.min(a, b) * 50001 + Math.max(a, b);
    }
    
    void findCycles() {
        Replacement r;
        for (int i = 0; i < M; i++) {
            r = replacements[i];
            int lca = findLCA(r.n1, r.n2);
            // Update all edges on the path from each node to the LCA
            int numIters = 0;
            while (r.n1 != -1 && r.n1 != lca) {
                r.n1 = updatePath(r.n1, lca, r.c);
                numIters++;
                if (numIters > 50000) replacements[-2] = null;
            }
            numIters = 0;
            while (r.n2 != -1 && r.n2 != lca) {
                r.n2 = updatePath(r.n2, lca, r.c);
                numIters++;
                if (numIters > 50000) replacements[-2] = null;
            }
        }
    }

    int updatePath(int curr, int end, int cost) {
        // Traverse the segment trees, updating each one as needed
        SegmentTree currSTree = heavySegTrees.get(treeUp[curr].sid);
        if (currSTree.rootDepth <= depth[end]) {
            // Don't need to go all the way; only update partial
            // System.out.printf("Updating from %d to %d on sid %d\n", depth[currSTree.tailNode] - depth[curr], currSTree.size + depth[currSTree.rootNode] - depth[end] - 1, treeUp[curr].sid);
            currSTree.update(currSTree.tailDepth - depth[curr], currSTree.size + currSTree.rootDepth - depth[end] - 1, cost);
            return -1;
        } else {
            // Go to the next segment tree
            currSTree.update(currSTree.tailDepth - depth[curr], currSTree.size - 1, cost);
            return currSTree.rootNode;
        }
    }

    int findLCA(int a, int b) {
        // First, move both to the same height
        // n1 will need to move up
        int n1 = (depth[a] > depth[b]) ? a : b;
        int n2 = (depth[a] > depth[b]) ? b : a;

        int toMove = depth[n1] - depth[n2];
        for (int i = 17; i >= 0; i--) {
            if (lcaSteps[i] <= toMove) {
                n1 = lcaArr[i][n1];
                toMove -= lcaSteps[i];
            }
        }

        // Find LCA
        if (n1 == n2) return n1;
        else {
            for (int i = 17; i >= 0; i--) {
                if (lcaArr[i][n1] != lcaArr[i][n2]) {
                    n1 = lcaArr[i][n1];
                    n2 = lcaArr[i][n2];
                }
            }
        }

        return lcaArr[0][n1];
    }

    void genLCAArray() {
        lcaArr = new int[18][N];
        lcaSteps = new int[18];
        for (int j = 0; j < N; j++) lcaArr[0][j] = treeUp[j].n;
        lcaSteps[0] = 1;

        // lcaArr[i][j] = lcaArr[lcaArr[i][j-1]][j-1]
        for (int i = 1; i < 18; i++) {
            lcaSteps[i] = lcaSteps[i-1] * 2;
            for (int j = 0; j < N; j++) {
                lcaArr[i][j] = lcaArr[i-1][lcaArr[i-1][j]];
            }
        }

        // System.out.println(Arrays.deepToString(lcaArr));
    }

    int generateEdges(int node, int sTreeID, int rootSTreeNode, int dep) {
        treeUp[node].sid = sTreeID;
        if (treeDown[node].size() == 0) {
            // Leaf reached; generate segment tree
            SegmentTree stree = new SegmentTree(dep);
            stree.rootNode = rootSTreeNode;
            stree.rootDepth = depth[rootSTreeNode];
            stree.tailDepth = depth[node];
            heavySegTrees.add(stree);
            return sTreeID + 1;
        }
        // Find the child with the most nodes to extend a segment tree to
        int maxEdgeCount = -1;
        int maxChild = -1;

        for (Edge edge : treeDown[node]) {
            if (childrenCount[edge.n] > maxEdgeCount) {
                maxEdgeCount = childrenCount[edge.n];
                maxChild = edge.n;
            }
        }

        // Extend current segment tree to the chosen node
        // Start new segment trees in all other nodes
        int newSTreeID = generateEdges(maxChild, sTreeID, rootSTreeNode, dep + 1);
        for (Edge edge : treeDown[node]) {
            edge.sid = newSTreeID;
            if (maxChild != edge.n) {
                newSTreeID = generateEdges(edge.n, newSTreeID, node, 1);
            } else {
                edge.sid = sTreeID;
            }
        }

        return newSTreeID;
    }

    int generateTree(int node, int par, int dep) {
        treeUp[node] = new Edge(par, -1);
        childrenCount[node] = 1;
        depth[node] = dep;

        for (int neighbor : unrooted[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                treeDown[node].add(new Edge(neighbor, -1));
                int numChildren = generateTree(neighbor, node, dep + 1);
                childrenCount[node] += numChildren;
            }
        }

        return childrenCount[node];
    }

    public static void main(String[] args) throws IOException {
        new disrupt();
    }

    static class Replacement {
        int n1, n2, c;
        Replacement(int n1, int n2, int c) {
            this.n1 = n1;
            this.n2 = n2;
            this.c = c;
        }
    }

    static class Edge {
        int n, sid;
        Edge(int n, int sid) {
            this.n = n;
            this.sid = sid;
        }

        @Override
        public String toString() {
            return "(" + n + ", " + sid + ")";
        }
    }

    class SegmentTree {
        int size, rootNode, rootDepth, tailDepth;
        int[] values, delta, lb, ub;

        SegmentTree(int size) {
            this.size = size;
            values = new int[size * 4 + 1];
            delta = new int[size * 4 + 1];
            for (int i = 0; i < size * 4 + 1; i++) {
                values[i] = INF;
                delta[i] = INF;
            }
            lb = new int[size * 4 + 1];
            ub = new int[size * 4 + 1];
            initTree(0, size - 1, 1);
            /*
            System.out.println(Arrays.toString(values));
            System.out.println(Arrays.toString(delta));
            System.out.println(Arrays.toString(lb));
            System.out.println(Arrays.toString(ub));
             */
        }

        void initTree(int min, int max, int node) {
            lb[node] = min;
            ub[node] = max;
            if (min != max) {
                // Init left and right children
                initTree(min, (min + max) / 2, node * 2);
                initTree((min + max) / 2  + 1, max, node * 2 + 1);
            }
        }

        void update(int min, int max, int value) {
            update(min, max, value, 1);
        }

        void update(int min, int max, int value, int node) {
            if (min > ub[node] || max < lb[node]) return;
            else if (min <= lb[node] && max >= ub[node]) {
                // Lazy propagation
                delta[node] = Math.min(value, delta[node]);
                return;
            }

            // Check intervals below this one (half covered)
            /*
            // First, propagate any changes
            delta[node * 2] = Math.min(delta[node], delta[node * 2]);
            delta[node * 2 + 1] = Math.min(delta[node], delta[node * 2 + 1]);
            delta[node] = INF;
             */
            // Now, recurse on lower intervals
            update(min, max, value, node * 2);
            update(min, max, value, node * 2 + 1);
        }

        int query(int index) {
            return query(index, 1);
        }

        int query(int index, int node) {
            if (lb[node] > index || ub[node] < index) return INF;
            else if (lb[node] == index && ub[node] == index) return Math.min(values[node], delta[node]);

            // Check intervals below this one (half covered)
            // First, propagate any changes
            delta[node * 2] = Math.min(delta[node], delta[node * 2]);
            delta[node * 2 + 1] = Math.min(delta[node], delta[node * 2 + 1]);
            delta[node] = INF;
            // Now, recurse on lower intervals
            return Math.min(query(index, node * 2), query(index, node * 2 + 1));
        }

        @Override
        public String toString() {
            return "STree[" + size + "]";
        }
    }
}
