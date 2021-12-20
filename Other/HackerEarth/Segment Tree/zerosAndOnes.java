/*
Solution: Standard segment tree problem (set element at i to 0, query sum from [l, r]). To answer 1 queries, use a
binary search like algorithm on the segment tree (if enough 1s on left side, recurse on left; else recurse on right).
Runtime: O(Q * log(N))
*/

import java.util.*;
import java.io.*;

public class zerosAndOnes {
    int N, Q;

    zerosAndOnes(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st;
        N = Integer.parseInt(in.readLine());
        Q = Integer.parseInt(in.readLine());
        SegmentTree seg = new SegmentTree(N);
        int a, b;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            if (a == 0) seg.set0(b-1);
            else out.println(seg.queryIth1(b));
        }
    }

    class SegmentTree {
        int size;
        int[] vals;
        SegmentTree(int size) {
            this.size = size;
            vals = new int[size * 4 + 1];
            initTree(1, 0, size - 1);
        }

        void set0(int i) {
            set0(1, 0, size - 1, i);
        }

        void set0(int n, int lb, int ub, int i) {
            if (lb == ub) {
                vals[n] = 0;
                return;
            }

            if (i > (lb+ub)/2) {
                set0(n*2+1, (lb+ub)/2+1, ub, i);
            } else {
                set0(n*2, lb, (lb+ub)/2, i);
            }
            vals[n] = vals[n*2] + vals[n*2+1];
        }

        int queryIth1(int i) {
            if (vals[1] < i) return -1;
            else return queryIth1(1, 0, size - 1, i);
        }

        int queryIth1(int n, int lb, int ub, int i) {
            if (lb == ub) return lb + 1;
            if (vals[n*2] >= i) return queryIth1(n*2, lb, (lb+ub)/2, i);
            else return queryIth1(n*2+1, (lb+ub)/2+1, ub, i - vals[n*2]);
        }

        void initTree(int n, int lb, int ub) {
            if (lb == ub) vals[n] = 1;
            else {
                initTree(n*2, lb, (lb+ub)/2);
                initTree(n*2+1, (lb+ub)/2+1, ub);
                vals[n] = vals[n*2] + vals[n*2+1];
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("zerosAndOnes.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("zerosAndOnes.out")));
        new zerosAndOnes(in, out);
        in.close();
        out.close();
    }
}
