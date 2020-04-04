/*
Solution: Standard segment tree.
*/

import java.util.*;
import java.io.*;

public class HORRIBLE {
    int T, N, C;
    GSS.SegmentTree seg;

    HORRIBLE() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        StringTokenizer st = new StringTokenizer(in.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int i = 0; i < T; i++) {
            st = new StringTokenizer(in.readLine());
            N = Integer.parseInt(st.nextToken());
            C = Integer.parseInt(st.nextToken());
            seg = new GSS.SegmentTree(N);
            int type, p, q, v;
            for (int j = 0; j < C; j++) {
                st = new StringTokenizer(in.readLine());
                type = Integer.parseInt(st.nextToken());
                p = Integer.parseInt(st.nextToken())-1;
                q = Integer.parseInt(st.nextToken())-1;
                if (p > q) {
                    int temp = p;
                    p = q;
                    q = temp;
                }
                if (type == 0) {
                    // Add
                    v = Integer.parseInt(st.nextToken());
                    seg.add(p, q, v);
                } else {
                    // Query
                    out.println(seg.query(p, q));
                }
            }
            // System.out.println(Arrays.toString(seg.sum));
        }
        in.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new HORRIBLE();
    }
}

class SegmentTree {
    int size;
    long[] sum, lazy;
    SegmentTree(int size) {
        this.size = size;
        sum = new long[size * 4 + 1];
        lazy = new long[size * 4 + 1];
    }

    void add(int p, int q, int v) {
        add(1, 0, size-1, p, q, v);
    }

    void add(int n, int lb, int ub, int p, int q, int v) {
        if (lb > q || ub < p) return;
        else if (lb >= p && ub <= q) {
            sum[n] += (ub - lb + 1) * (long) v;
            lazy[n] += v;
            return;
        }

        propagate(n, lb, ub);

        add(n*2, lb, (lb+ub)/2, p, q, v);
        add(n*2+1, (lb+ub)/2+1, ub, p, q, v);
        update(n);
    }

    long query(int p, int q) {
        return query(1, 0, size-1, p, q);
    }

    long query(int n, int lb, int ub, int p, int q) {
        if (lb > q || ub < p) return 0;
        else if (lb >= p && ub <= q) return sum[n];

        propagate(n, lb, ub);

        return query(n*2, lb, (lb+ub)/2, p, q) + query(n*2+1, (lb+ub)/2+1, ub, p, q);
    }

    void propagate(int n, int lb, int ub) {
        sum[n*2] += ((lb + ub) / 2 - lb + 1) * lazy[n];
        sum[n*2+1] += (ub - (lb + ub) / 2) * lazy[n];
        lazy[n*2] += lazy[n];
        lazy[n*2+1] += lazy[n];
        lazy[n] = 0;
    }

    void update(int n) {
        sum[n] = sum[n*2] + sum[n*2+1];
    }
}