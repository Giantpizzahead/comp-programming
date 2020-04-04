/*
Solution: When parsing input, answer any 1-node queries in O(1) without putting it into the actual
query edges.

Queries with ^ shape can be split into two straight line queries, so do that first using LCA. Then,
do a DFS. Starting from the leaf nodes, when you come across a query that hasn't been visited yet,
put it into the "current queries" list. At a node, mark all with that target as yes, and remove those
queries. To merge leaf query nodes, merge into larger set to keep log(N) complexity.

Order: First process leaves, then add start queries into largest set while checking if they match
this node's value. Finally, merge nodes into largest set, checking if they match this node's value,
and only adding them if their end node is NOT the current node.

Runtime: O(N * log(N)) because HashMap hopefully will help
*/

import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class milkvisitsNoMap {
    int N, M, root;
    int[] type, depth, subtreeSize;
    boolean[] answers, typeExists;
    int[][] lcaArr;
    ArrayList<Integer>[] graph;
    ArrayList<Query>[] queries, toRemove;
    final int MAX_LCA = 16, INF = 987654321;

    milkvisitsNoMap() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("milkvisits.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        type = new int[N];
        typeExists = new boolean[N];
        st = new StringTokenizer(fin.readLine());
        for (int i = 0; i < N; i++) {
            type[i] = Integer.parseInt(st.nextToken()) - 1;
            typeExists[type[i]] = true;
        }
        graph = new ArrayList[N];
        queries = new ArrayList[N];
        toRemove = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<>(2);
            queries[i] = new ArrayList<>(2);
            toRemove[i] = new ArrayList<>(2);
        }
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graph[a].add(b);
            graph[b].add(a);
        }

        depth = new int[N];
        lcaArr = new int[N][MAX_LCA];
        subtreeSize = new int[N];

        root = N/2;
        // root = findCentroid();
        genLCAInfo();

        // Parse queries / handle 1-node queries
        answers = new boolean[M];
        int c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken()) - 1;
            if (a == b) {
                answers[i] = (type[a] == c);
            } else if (typeExists[c]) {
                int lca = lca(a, b);
                if (lca != a && lca != b) {
                    // Split query up into two
                    Query q = new Query(lca, c, i);
                    queries[a].add(q);
                    queries[b].add(q);
                    toRemove[lca].add(q);
                } else {
                    // One query is enough; put it at the deepest node
                    if (depth[a] > depth[b]) {
                        Query q = new Query(b, c, i);
                        queries[a].add(q);
                        toRemove[b].add(q);
                    }
                    else {
                        Query q = new Query(a, c, i);
                        queries[b].add(q);
                        toRemove[a].add(q);
                    }
                }
            }
        }
        fin.close();

        // System.out.println(Arrays.toString(queries));
        dfsQueries(root, root);

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milkvisits.out")));
        StringBuilder sb = new StringBuilder();
        for (boolean ans : answers) {
            sb.append(ans ? '1' : '0');
        }
        fout.println(sb.toString());
        fout.close();
    }

    int findCentroid() {
        getSubtreeSums(0, 0);
        int centroid = 0, bestSTSize = N;
        Queue<Integer> q = new LinkedList<>();
        q.add(0);
        int c;
        while (!q.isEmpty()) {
            c = q.poll();
            int maxSTSize = subtreeSize[0] - subtreeSize[c];
            for (int e : graph[c]) {
                if (lcaArr[c][0] != e) {
                    maxSTSize = Math.max(subtreeSize[e], maxSTSize);
                    q.add(e);
                }
            }

            if (maxSTSize < bestSTSize) {
                // New best centroid
                centroid = c;
                bestSTSize = maxSTSize;
            }
        }
        return centroid;
    }

    int getSubtreeSums(int n, int p) {
        lcaArr[n][0] = p;
        int currSTSize = 1;
        for (int e : graph[n]) {
            if (e != p) currSTSize += getSubtreeSums(e, n);
        }
        subtreeSize[n] = currSTSize;
        return currSTSize;
    }

    TreeSet<Query> dfsQueries(int n, int p) {
        // First process leaves
        ArrayList<TreeSet<Query>> leafQueries = new ArrayList<>(2);
        int maxQueryEntries = -1, maxQueryI = -1;
        boolean isLeaf = true;
        for (int e : graph[n]) {
            if (e != p) {
                isLeaf = false;
                TreeSet<Query> newQueries = dfsQueries(e, n);
                if (newQueries.size() > maxQueryEntries) {
                    // New largest set found
                    maxQueryEntries = newQueries.size();
                    maxQueryI = leafQueries.size();
                }
                leafQueries.add(newQueries);
            }
        }

        TreeSet<Query> merged;
        if (isLeaf) {
            // Just add an empty set for easier implementation
            leafQueries.add(new TreeSet<>());
            maxQueryEntries = 0;
            maxQueryI = 0;
            merged = leafQueries.get(0);
        } else {
            // Remove any queries from biggest set that are satisfied
            // Don't update answers for any queries that have already gone out of range
            merged = leafQueries.get(maxQueryI);
            Query q = merged.floor(new Query(0, type[n], INF));
            while (q != null && q.t == type[n]) {
                answers[q.origI] = true;
                merged.remove(q);
                q = merged.floor(new Query(0, type[n], INF));
            }
        }

        // Add current queries (if there are any)
        for (Query q : queries[n]) {
            // Only add if target is not already met
            if (q.t == type[n] || answers[q.origI]) {
                // Already met
                answers[q.origI] = true;
            } else {
                // Not yet met; add it
                if (n != root) merged.add(q);
            }
        }

        // Merge previous queries
        TreeSet<Query> toMerge;
        for (int i = 0; i < leafQueries.size(); i++) {
            if (i == maxQueryI) continue;
            toMerge = leafQueries.get(i);

            // Merge all queries, checking if they've been satisfied or not
            for (Query q : toMerge) {
                if (q.t == type[n]) {
                    answers[q.origI] = true;
                } else {
                    // Not yet done; add it
                    if (n != root) merged.add(q);
                }
            }

            // Save memory?
            // toMerge.clear();
        }

        // Invalidate queries (out of query range)
        if (n != root) {
            for (Query q : toRemove[n]) merged.remove(q);
        }

        return merged;
    }

    int lca(int a, int b) {
        int n1, n2;
        if (depth[a] > depth[b]) {
            n1 = a;
            n2 = b;
        } else {
            n1 = b;
            n2 = a;
        }

        int toMove = depth[n1] - depth[n2];
        if (toMove != 0) {
            for (int i = MAX_LCA - 1; i >= 0; i--) {
                if (toMove >= 1 << i) {
                    toMove -= 1 << i;
                    n1 = lcaArr[n1][i];
                }
            }
        }

        if (n1 == n2) return n1;

        for (int i = MAX_LCA - 1; i >= 0; i--) {
            if (lcaArr[n1][i] != lcaArr[n2][i]) {
                n1 = lcaArr[n1][i];
                n2 = lcaArr[n2][i];
            }
        }

        return lcaArr[n1][0];
    }

    void genLCAInfo() {
        recurseLCA(root, root, 0);

        // Fill LCA array
        for (int i = 1; i < MAX_LCA; i++) {
            for (int n = 0; n < N; n++) lcaArr[n][i] = lcaArr[lcaArr[n][i-1]][i-1];
        }
    }

    int recurseLCA(int n, int p, int d) {
        depth[n] = d;
        lcaArr[n][0] = p;
        int currSTSize = 1;
        for (int e : graph[n]) {
            if (e != p) currSTSize += recurseLCA(e, n, d+1);
        }
        subtreeSize[n] = currSTSize;
        return currSTSize;
    }

    public static void main(String[] args) throws IOException {
        new milkvisitsNoMap();
    }

    class Query implements Comparable<Query> {
        int n, t, origI;
        Query(int n, int t, int origI) {
            this.n = n;
            this.t = t;
            this.origI = origI;
        }
        public String toString() {
            return String.format("(%d, %d, %d)", (n+1), t, origI);
        }

        @Override
        public int compareTo(Query o) {
            if (t == o.t) return origI - o.origI;
            else return t - o.t;
        }
    }
}
