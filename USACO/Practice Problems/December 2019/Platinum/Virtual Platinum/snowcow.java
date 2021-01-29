/*
Solution: Each splash is either completely disjoint from, or completely enclosed by another
splash of the same color. So, track previous splashes, removing them when this one encloses
them (or not adding this one if it's already enclosed). Track # of distinct colors in a
segment tree (tree ranges with pre-order labeling).

Runtime: O((N + Q) * log(N))
*/

import javax.swing.text.Segment;
import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class snowcow {
    int N, Q;
    int[] start, end;
    ArrayList<Integer>[] adj;
    TreeSet<Query>[] queries;
    final int NUM_COLORS = 100000;

    snowcow(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
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

        start = new int[N];
        end = new int[N];
        labelNodes(0, 0);

        SegmentTree seg = new SegmentTree(N);
        queries = new TreeSet[NUM_COLORS];
        for (int i = 0 ; i < NUM_COLORS; i++) queries[i] = new TreeSet<>();

        // Handle queries online
        int t;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            t = Integer.parseInt(st.nextToken());
            a = Integer.parseInt(st.nextToken()) - 1;
            if (t == 1) {
                // Splash
                b = Integer.parseInt(st.nextToken()) - 1;
                Query curr = new Query(start[a], end[a]);
                // If this query is enclosed, don't add it
                Query floor = queries[b].floor(curr);
                if (floor != null && floor.r >= curr.r) {
                    // Completely enclosed; ignore query
                    continue;
                }

                // Remove any queries that this one completely encloses
                Query ceil = queries[b].ceiling(curr);
                while (ceil != null && ceil.r <= curr.r) {
                    // Remove enclosed query
                    seg.increment(ceil.l, ceil.r, -1);
                    queries[b].remove(ceil);
                    ceil = queries[b].ceiling(curr);
                }

                // Add this query
                seg.increment(curr.l, curr.r, 1);
                queries[b].add(curr);
            } else {
                // Query
                out.println(seg.query(start[a], end[a]));
            }
        }
    }

    int currLabel = 0;
    void labelNodes(int n, int p) {
        start[n] = currLabel++;
        for (int e : adj[n]) {
            if (e != p) labelNodes(e, n);
        }
        end[n] = currLabel - 1;
    }

    static class SegmentTree {
        int size;
        long[] vals, delta;

        SegmentTree(int size) {
            this.size = size;
            vals = new long[size * 4 + 1];
            delta = new long[size * 4 + 1];
        }

        void increment(int l, int r, int v) {
            increment(1, 0, size - 1, l, r, v);
        }

        void increment(int n, int lb, int ub, int l, int r, int v) {
            if (lb > r || ub < l) return;
            else if (lb >= l && ub <= r) {
                vals[n] += v * (ub - lb + 1);
                delta[n] += v;
                return;
            }

            propagate(n, lb, ub);
            increment(n*2, lb, (lb+ub)/2, l, r, v);
            increment(n*2+1, (lb+ub)/2+1, ub, l, r, v);
            vals[n] = vals[n*2] + vals[n*2+1];
        }

        long query(int l, int r) {
            return query(1, 0, size - 1, l, r);
        }

        long query(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return 0;
            else if (lb >= l && ub <= r) {
                return vals[n];
            }

            propagate(n, lb, ub);
            return query(n*2, lb, (lb+ub)/2, l, r) + query(n*2+1, (lb+ub)/2+1, ub, l, r);
        }

        void propagate(int n, int lb, int ub) {
            if (delta[n] != 0) {
                vals[n*2] += delta[n] * ((lb+ub)/2 - lb + 1);
                vals[n*2+1] += delta[n] * (ub - ((lb+ub)/2+1) + 1);
                delta[n*2] += delta[n];
                delta[n*2+1] += delta[n];
                delta[n] = 0;
            }
        }
    }

    static class Query implements Comparable<Query> {
        int l, r;
        Query(int l, int r) {
            this.l = l;
            this.r = r;
        }

        @Override
        public int compareTo(Query o) {
            return l - o.l;
        }

        @Override
        public String toString() {
            return "Query{" +
                    "l=" + l +
                    ", r=" + r +
                    '}';
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("snowcow.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("snowcow.out")));
        new snowcow(in, out);
        in.close();
        out.close();
    }
}
