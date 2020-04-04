/*
Solution: First, label all the nodes in DFS order to allow O(1) checking time for whether a node
is an ancestor of another node. Also track each node's depth. Then, do a single DFS to answer all
the queries at once. When at a node that contains a query, check for the closest node with the
same milk type as that query (keep a N-size stack for all milk types). If that node is not an
ancestor of the other query node, it's definitely on the path (so mark query as true). Else, if
the node directly below the top stack node is NOT an ancestor of the other query node, the top
node was the LCA of the 2 nodes, meaning that it's on the path (mark query true).

Runtime: O(N + M)
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class milkvisits {
    int N, M;
    int[] type, depth, parent, startLabel, endLabel;
    boolean[] answers;
    ArrayList<Integer>[] graph;
    ArrayList<Query>[] queries;

    milkvisits() throws IOException {
        long currTime = System.currentTimeMillis();
        BufferedReader fin = new BufferedReader(new FileReader("milkvisits.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        type = new int[N];
        st = new StringTokenizer(fin.readLine());
        for (int i = 0; i < N; i++) type[i] = Integer.parseInt(st.nextToken()) - 1;
        graph = new ArrayList[N];
        queries = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<>(2);
            queries[i] = new ArrayList<>(2);
        }
        // Parse edges
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graph[a].add(b);
            graph[b].add(a);
        }
        // Parse queries
        answers = new boolean[M];
        int c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken()) - 1;
            queries[a].add(new Query(b, c, i));
            queries[b].add(new Query(a, c, i));
        }
        fin.close();
        System.out.println("Parsed input: " + (System.currentTimeMillis() - currTime));

        depth = new int[N];
        parent = new int[N];
        startLabel = new int[N];
        endLabel = new int[N];
        genTreeInfo(0, 0, 0);

        lastSeen = new Stack[N];
        for (int i = 0; i < N; i++) lastSeen[i] = new Stack<>();
        currPath = new int[N];
        queryDFS(0);

        System.out.println("DFS done: " + (System.currentTimeMillis() - currTime));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milkvisits.out")));
        for (boolean ans : answers) fout.print(ans ? 1 : 0);
        fout.println();
        fout.close();
        System.out.println("Output done: " + (System.currentTimeMillis() - currTime));
    }

    int currLabel = 0;
    void genTreeInfo(int n, int p, int d) {
        depth[n] = d;
        parent[n] = p;
        startLabel[n] = currLabel++;
        for (int e : graph[n]) {
            if (e != p) genTreeInfo(e, n, d + 1);
        }
        endLabel[n] = currLabel - 1;
    }

    Stack<Integer>[] lastSeen;
    int[] currPath;
    void queryDFS(int n) {
        currPath[depth[n]] = n;

        // Handle queries
        for (Query q : queries[n]) {
            // Check if this node is the right type
            if (type[n] == q.t) {
                answers[q.id] = true;
                continue;
            }
            if (lastSeen[q.t].isEmpty()) continue;
            int lastID = lastSeen[q.t].peek();
            // Check if node is ancestor of other query node
            if (isAncestor(lastID, q.n)) {
                // Check if node directly below lastID is ancestor of other query node
                int belowID = currPath[depth[lastID] + 1];
                if (!isAncestor(belowID, q.n)) {
                    // lastID was the LCA
                    answers[q.id] = true;
                }
            } else {
                // On path
                answers[q.id] = true;
            }
        }

        // Add new last node
        lastSeen[type[n]].add(n);

        // DFS
        for (int e : graph[n]) {
            if (e != parent[n]) queryDFS(e);
        }

        // Backtrack
        lastSeen[type[n]].pop();
    }

    /**
     * Returns whether a is an ancestor of b.
     */
    boolean isAncestor(int a, int b) {
        return startLabel[b] >= startLabel[a] && startLabel[b] <= endLabel[a];
    }

    public static void main(String[] args) throws IOException {
        new milkvisits();
    }

    static class Query {
        int n, t, id;
        Query(int n, int t, int id) {
            this.n = n;
            this.t = t;
            this.id = id;
        }
    }
}
