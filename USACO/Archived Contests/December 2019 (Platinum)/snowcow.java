/*
Solution: Do lazy propagation on the tree, only pulling down colors / queries when needed. Track
the colorfulness values at each node, along with the # of nodes colored with each color.

Runtime: O(N^2 + Q^2) worst case, hopefully better in average?
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class snowcow {
    int N, Q;
    int[] stSize, parent;
    long[] colorfulness;
    HashMap<Integer, Integer>[] numColored;
    ArrayList<Integer>[] graph;
    Stack<Integer>[] lazyProp;

    snowcow() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("snowcow.in"));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("snowcow.out")));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        lazyProp = new Stack[N];
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<>(2);
            lazyProp[i] = new Stack<>();
        }
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graph[a].add(b);
            graph[b].add(a);
        }

        // Find subtree info
        stSize = new int[N];
        parent = new int[N];
        genTreeInfo(0, -1);

        // Handle queries in realtime
        numColored = new HashMap[N];
        colorfulness = new long[N];
        for (int i = 0; i < N; i++) numColored[i] = new HashMap<>(2);
        int c;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken());
            if (a == 1) {
                // New nodes colored
                b = Integer.parseInt(st.nextToken()) - 1;
                c = Integer.parseInt(st.nextToken()) - 1;
                findPathColor(b, b, c);
            } else {
                // Query colorfulness value
                b = Integer.parseInt(st.nextToken()) - 1;
                fout.println(findPathQuery(b, b));
            }
        }

        fin.close();
        fout.close();
    }

    // Finds path from n to root, then calls query at every node (starting from top).
    long findPathQuery(int n, int targetNode) {
        if (n != 0) findPathQuery(parent[n], targetNode);
        return query(n, targetNode);
    }

    long query(int n, int targetNode) {
        if (n == targetNode) {
            return colorfulness[n];
        } else {
            // Propagate
            propagateDown(n);
            return -1;
        }
    }

    // Finds path from n to root, then calls colorNodes at every node (starting from top).
    void findPathColor(int n, int coloredNode, int color) {
        if (n != 0) findPathColor(parent[n], coloredNode, color);
        colorNodes(n, coloredNode, color);
    }

    void colorNodes(int n, int coloredNode, int color) {
        if (n == coloredNode) {
            // Mark subtree as colored with lazy prop & update colorfulness
            lazyProp[n].push(color);
            int change = stSize[n] - numColored[n].getOrDefault(color, 0);
            if (change == 0) return;
            colorfulness[n] += change;
            numColored[n].put(color, stSize[n]);

            // Propagate info to upper nodes
            propagateUp(parent[n], color, change);
        } else {
            // Propagate down if needed
            propagateDown(n);
        }
    }

    void propagateUp(int n, int color, int change) {
        if (n == -1) return;
        int currColor = numColored[n].getOrDefault(color, 0);
        colorfulness[n] += change;
        numColored[n].put(color, currColor + change);
        // Continue propagating up
        propagateUp(parent[n], color, change);
    }

    void propagateDown(int n) {
        // Propagate colored subtrees
        while (!lazyProp[n].isEmpty()) {
            int toProp = lazyProp[n].pop();
            for (int e : graph[n]) {
                if (e == parent[n]) continue;
                lazyProp[e].push(toProp);
                int change = stSize[e] - numColored[e].getOrDefault(toProp, 0);
                colorfulness[e] += change;
                numColored[e].put(toProp, stSize[e]);
            }
        }
    }

    int genTreeInfo(int n, int p) {
        parent[n] = p;
        int currSTSize = 1;
        for (int e : graph[n]) {
            if (e != p) currSTSize += genTreeInfo(e, n);
        }
        stSize[n] = currSTSize;
        return currSTSize;
    }

    public static void main(String[] args) throws IOException {
        new snowcow();
    }
}
