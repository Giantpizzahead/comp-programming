/*
Solution: Standard segment tree problem (set [l, r] to value, and query max in [l, r]). Just be a bit careful when
handling the weirdly shaped blocks.
Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class blocks {
    int N;

    blocks(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        SegmentTree heights = new SegmentTree(110010);
        int l, h, p, c, x;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            l = Integer.parseInt(st.nextToken());
            h = Integer.parseInt(st.nextToken());
            p = Integer.parseInt(st.nextToken());
            c = Integer.parseInt(st.nextToken());
            x = Integer.parseInt(st.nextToken()) - 1;
            if (c == 0) {
                // Below
                long placeHeight = Math.max(heights.query(x, x + l - 1) + 1, heights.query(x + p - 1, x + p - 1) + h + 1);
                heights.set(x, x + l - 1, placeHeight);
            } else {
                // Above
                long placeHeight = heights.query(x, x + l - 1) + 1;
                heights.set(x, x + l - 1, placeHeight);
                heights.set(x + p - 1, x + p - 1, placeHeight + h);
            }
        }
        System.out.println(heights.query(0, 110009));
    }

    class SegmentTree {
        int size;
        long[] vals, delta;

        SegmentTree(int size) {
            this.size = size;
            vals = new long[size * 4 + 1];
            delta = new long[size * 4 + 1];
        }

        void set(int l, int r, long v) {
            set(1, 0, size - 1, l, r, v);
        }

        void set(int n, int lb, int ub, int l, int r, long v) {
            if (lb > r || ub < l) return;
            else if (lb >= l && ub <= r) {
                delta[n] = v;
                vals[n] = v;
                return;
            }
            propagate(n);
            set(n*2, lb, (lb+ub)/2, l, r, v);
            set(n*2+1, (lb+ub)/2+1, ub, l, r, v);
            vals[n] = Math.max(vals[n*2], vals[n*2+1]);
        }

        long query(int l, int r) {
            return query(1, 0, size - 1, l, r);
        }

        long query(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return 0;
            else if (lb >= l && ub <= r) return vals[n];
            propagate(n);
            return Math.max(query(n*2, lb, (lb+ub)/2, l, r), query(n*2+1, (lb+ub)/2+1, ub, l, r));
        }

        void propagate(int n) {
            if (delta[n] != 0) {
                vals[n*2] = delta[n];
                vals[n*2+1] = delta[n];
                delta[n*2] = delta[n];
                delta[n*2+1] = delta[n];
                delta[n] = 0;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("blocks.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("blocks.out")));
        new blocks(in, out);
        in.close();
        out.close();
    }
}
