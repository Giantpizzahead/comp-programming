/*
Solution: Use a segment tree, and treat a circular query as 2 separate queries.
Runtime: O(M * log(N))
*/

import java.util.*;
import java.io.*;

public class circularrmq {
    int N, M;
    SegmentTree stree;

    circularrmq() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        stree = new SegmentTree(N);
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            stree.update(i, i, Integer.parseInt(st.nextToken()));
        }

        // Handle queries
        st = new StringTokenizer(in.readLine());
        M = Integer.parseInt(st.nextToken());

        int a, b, c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            if (st.hasMoreTokens()) {
                // Inc operation
                c = Integer.parseInt(st.nextToken());
                if (a > b) {
                    // Circular; do 2 increases
                    stree.update(a, N-1, c);
                    stree.update(0, b, c);
                } else {
                    stree.update(a, b, c);
                }
            } else {
                // RMQ operation
                if (a > b) {
                    // Circular; do 2 queries
                    out.println(Math.min(stree.query(a, N - 1), stree.query(0, b)));
                } else {
                    out.println(stree.query(a, b));
                }
            }
        }
        in.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new circularrmq();
    }

    class SegmentTree {
        private int size, MAX_SIZE;
        private int[] lb, ub;
        private long[] delta;
        public long[] vals;
        // Set this based on the operation that you're doing
        private final long NULL_VAL = Long.MAX_VALUE / 10;

        SegmentTree(int size) {
            this.size = size;
            this.MAX_SIZE = size * 4 + 1;
            lb = new int[MAX_SIZE];
            ub = new int[MAX_SIZE];
            delta = new long[MAX_SIZE];
            vals = new long[MAX_SIZE];
            initTree(1, 0, size-1);
        }

        public void update(int lower, int upper, int value) {
            update(1, lower, upper, value);
        }

        private long update(int node, int lower, int upper, int value) {
            if (lb[node] > upper || ub[node] < lower) return vals[node] + delta[node];  // Out of range
            else if (lb[node] >= lower && ub[node] <= upper) {
                // Completely in range
                delta[node] += value;
                return vals[node] + delta[node];
            }

            // Propagate changes
            propagate(node);

            // Recurse
            long leftVal = update(node * 2, lower, upper, value);
            long rightVal = update(node * 2 + 1, lower, upper, value);

            // Update this node's value
            vals[node] = Math.min(leftVal, rightVal);
            return vals[node];
        }

        public long query(int lower, int upper) {
            return query(1, lower, upper);
        }

        private long query(int node, int lower, int upper) {
            if (lb[node] > upper || ub[node] < lower) return NULL_VAL;  // Out of range
            else if (lb[node] >= lower && ub[node] <= upper) {
                // Completely in range
                return vals[node] + delta[node];
            }

            // Propagate changes
            propagate(node);

            // Recurse
            return Math.min(query(node * 2, lower, upper), query(node * 2 + 1, lower, upper));
        }

        private void propagate(int node) {
            vals[node] += delta[node];
            if (lb[node] != ub[node]) {
                delta[node * 2] += delta[node];
                delta[node * 2 + 1] += delta[node];
            }
            delta[node] = 0;
        }

        private void initTree(int node, int lower, int upper) {
            lb[node] = lower;
            ub[node] = upper;
            if (lower != upper) {
                // Recursively init lower nodes
                initTree(node * 2, lower, (lower + upper) / 2);
                initTree(node * 2 + 1, (lower + upper) / 2 + 1, upper);
            }
        }
    }
}