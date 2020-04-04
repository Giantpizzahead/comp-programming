/*
Solution: HLD practice.
Runtime: O(N * log(N) + Q * log(N)^2)
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class cowland {
    final int MAX_LCA = 18;
    int N, Q;
    int[] enjoyment, hldLoc, hldStartNode, stSize, depth;
    int[][] lcaArr;
    ArrayList<Integer>[] adj;
    SegmentTree segt;

    cowland(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        enjoyment = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) enjoyment[i] = Integer.parseInt(st.nextToken());
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            adj[a].add(b);
            adj[b].add(a);
        }

        // Generate info
        stSize = new int[N];
        depth = new int[N];
        lcaArr = new int[MAX_LCA][N];
        genInfo(0, 0, 0);
        genLCAArr();

        // Generate HLD segment tree
        segt = new SegmentTree(N);
        hldLoc = new int[N];
        hldStartNode = new int[N];
        genHLD(0, 0, 0);

        // Now, handle all the queries
        int c;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken());
            if (a == 1) {
                // Update
                enjoyment[b] = c;
                segt.update(hldLoc[b], c);
            } else {
                // Query
                c--;
                out.println(query(b, c));
            }
        }
    }

    int query(int a, int b) {
        int lca = getLCA(a, b);
        return queryLine(a, lca) ^ queryLine(b, lca) ^ enjoyment[lca];
    }

    // Query must be a striaght line up!
    int queryLine(int a, int b) {
        int distTraveled = depth[a] - depth[hldStartNode[a]];
        int depthDiff = depth[a] - depth[b];
        if (depthDiff <= distTraveled) {
            // Target is within this range
            return segt.query(hldLoc[b], hldLoc[a]);
        } else {
            // Traverse to the next set of edges
            return segt.query(hldLoc[hldStartNode[a]], hldLoc[a]) ^ queryLine(lcaArr[0][hldStartNode[a]], b);
        }
    }

    void genInfo(int n, int p, int d) {
        int currSTSize = 1;
        lcaArr[0][n] = p;
        depth[n] = d;
        for (int e : adj[n]) {
            if (e != p) {
                genInfo(e, n, d+1);
                currSTSize += stSize[e];
            }
        }
        stSize[n] = currSTSize;
    }

    void genLCAArr() {
        for (int i = 1; i < MAX_LCA; i++) {
            for (int n = 0; n < N; n++) {
                lcaArr[i][n] = lcaArr[i-1][lcaArr[i-1][n]];
            }
        }
    }

    int getLCA(int a, int b) {
        int n1, n2;
        if (depth[a] < depth[b]) {
            n1 = a;
            n2 = b;
        } else {
            n1 = b;
            n2 = a;
        }

        int toMove = depth[n2] - depth[n1];
        for (int i = MAX_LCA - 1; i >= 0; i--) {
            if (toMove >= (1 << i)) {
                toMove -= 1 << i;
                n2 = lcaArr[i][n2];
            }
        }

        if (n1 == n2) return n1;
        for (int i = MAX_LCA - 1; i >= 0; i--) {
            if (lcaArr[i][n1] != lcaArr[i][n2]) {
                n1 = lcaArr[i][n1];
                n2 = lcaArr[i][n2];
            }
        }
        return lcaArr[0][n1];
    }

    int currLoc = 0;
    void genHLD(int n, int p, int start) {
        // Fill in current location with XOR value
        hldLoc[n] = currLoc;
        hldStartNode[n] = start;
        segt.update(currLoc++, enjoyment[n]);

        // Find heavy edge
        int maxSTSize = -1, heavyI = -1;
        for (int e : adj[n]) {
            if (e == p) continue;
            if (stSize[e] > maxSTSize) {
                maxSTSize = stSize[e];
                heavyI = e;
            }
        }

        // Traverse down heavy edge first
        if (heavyI != -1) genHLD(heavyI, n, start);

        // Start new ranges in light edges
        for (int e : adj[n]) {
            if (e == p || e == heavyI) continue;
            genHLD(e, n, e);
        }
    }

    static class SegmentTree {
        int size;
        int[] vals;

        SegmentTree(int size) {
            this.size = size;
            vals = new int[size * 4 + 1];
        }

        int query(int l, int r) {
            return query(1, 0, size - 1, l, r);
        }

        int query(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return 0;
            else if (lb >= l && ub <= r) return vals[n];
            else return query(n*2, lb, (lb+ub)/2, l, r) ^ query(n*2+1, (lb+ub)/2+1, ub, l, r);
        }

        void update(int i, int v) {
            update(1, 0, size - 1, i, v);
        }

        void update(int n, int lb, int ub, int i, int v) {
            if (lb == ub) {
                vals[n] = v;
                return;
            } else if (i > (lb+ub)/2) {
                update(n*2+1, (lb+ub)/2+1, ub, i, v);
            } else {
                update(n*2, lb, (lb+ub)/2, i, v);
            }
            vals[n] = vals[n*2] ^ vals[n*2+1];
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("cowland.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cowland.out")));
        new cowland(in, out);
        in.close();
        out.close();
    }
}
