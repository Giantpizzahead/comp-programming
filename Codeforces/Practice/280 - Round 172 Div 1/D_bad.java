/*
Solution: Use a segment tree, storing the sum, left sum, right sum, left-right sum, and max sum at each node with
k non-intersecting subsegments. Use these to calculate the values of the parent nodes.

Runtime: O(KN * log(N))
*/

import java.util.*;
import java.io.*;

public class kMaxSS {
    int N, M;
    short[] arr;
    SegmentTree seg;

    kMaxSS() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        N = Integer.parseInt(in.readLine());
        arr = new short[N];
        StringTokenizer st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Short.parseShort(st.nextToken());
        seg = new SegmentTree(N, arr);
        M = Integer.parseInt(in.readLine());
        int t, a, b, c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            t = Integer.parseInt(st.nextToken());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            if (t == 0) {
                // Assignment
                seg.set(a-1, b);
            } else {
                // Query
                c = Integer.parseInt(st.nextToken());
                out.println(seg.query(a-1, b-1, c));
            }
        }
        in.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new kMaxSS();
    }

    class SegmentTree {
        int size;
        short[] origArr;
        int[] s;
        int[][] ls, rs, lrs, ms;
        byte[] maxK;
        boolean[] updateMark;
        final int MAXK = 20, INF = 100;

        SegmentTree(int size, short[] arr) {
            this.size = size;
            this.origArr = arr;
            s = new int[size * 4 + 1];
            ls = new int[size * 4 + 1][];
            rs = new int[size * 4 + 1][];
            lrs = new int[size * 4 + 1][];
            ms = new int[size * 4 + 1][];
            maxK = new byte[size * 4 + 1];
            updateMark = new boolean[size * 4 + 1];
            initTree(1, 0, size-1);
        }

        void set(int i, int val) {
            set(1, 0, size-1, i, val);
        }

        void set(int n, int lb, int ub, int i, int val) {
            if (lb == i && ub == i) {
                s[n] = val;
                ls[n][1] = val;
                rs[n][1] = val;
                lrs[n][1] = val;
                ms[n][1] = val;
                maxK[n] = 1;
                return;
            }

            if ((lb+ub)/2 >= i) set(n*2, lb, (lb+ub)/2, i, val);
            else set(n*2+1, (lb+ub)/2+1, ub, i, val);
            updateMark[n] = true;
        }

        int query(int l, int r, int k) {
            Result result = query(1, 0, size-1, l, r, k);
            // System.out.println(result);
            int max = -INF;
            for (int j = 0; j <= Math.min(k, result.maxK); j++) max = Math.max(result.ms[j], max);
            return max;
        }

        Result query(int n, int lb, int ub, int l, int r, int k) {
            if (lb >= l && ub <= r) {
                // You're allowed to choose anywhere from 0...k subsegments
                if (updateMark[n]) update(n);
                return new Result(s[n], ls[n], rs[n], lrs[n], ms[n], maxK[n]);
            } else if ((lb+ub)/2 >= r) {
                // Only need to query left
                return query(n*2, lb, (lb+ub)/2, l, r, k);
            } else if ((lb+ub)/2+1 <= l) {
                // Only query right
                return query(n*2+1, (lb+ub)/2+1, ub, l, r, k);
            } else {
                // Recursively query bottom 2, and merge results
                Result rl = query(n * 2, lb, (lb + ub) / 2, l, r, k);
                Result rr = query(n * 2 + 1, (lb + ub) / 2 + 1, ub, l, r, k);
                return mergeResults(rl, rr, k);
            }
        }

        void initTree(int n, int lb, int ub) {
            if (lb == ub) {
                s[n] = origArr[lb];
                ls[n] = new int[2];
                rs[n] = new int[2];
                lrs[n] = new int[2];
                ms[n] = new int[2];
                ls[n][1] = s[n];
                rs[n][1] = s[n];
                lrs[n][1] = s[n];
                ms[n][1] = s[n];
                maxK[n] = 1;
            } else {
                initTree(n*2, lb, (lb+ub)/2);
                initTree(n*2+1, (lb+ub)/2+1, ub);
                update(n);
            }
        }

        // Updates all of n's values with its child values.
        void update(int n) {
            final int l = n*2;
            final int r = n*2+1;
            if (updateMark[l]) update(l);
            if (updateMark[r]) update(r);
            Result rm = mergeResults(new Result(s[l], ls[l], rs[l], lrs[l], ms[l], maxK[l]), new Result(s[r], ls[r], rs[r], lrs[r], ms[r], maxK[r]), MAXK);
            // Update results
            s[n] = rm.s;
            ls[n] = rm.ls;
            rs[n] = rm.rs;
            lrs[n] = rm.lrs;
            ms[n] = rm.ms;
            maxK[n] = rm.maxK;
            updateMark[n] = false;
        }

        Result mergeResults(Result rl, Result rr, int maxK) {
            Result rm = new Result((byte) Math.min(rl.maxK + rr.maxK, maxK));
            rm.s = rl.s + rr.s;
            // Try all pairs of lower sums
            for (int onLeft = 0; onLeft <= rl.maxK; onLeft++) {
                for (int onRight = 0; onRight <= rr.maxK; onRight++) {
                    int sum = onLeft + onRight;
                    boolean leftN0 = onLeft != 0;
                    boolean rightN0 = onRight != 0;
                    boolean update = false;
                    if (sum <= rm.maxK) {
                        update = true;
                        // Left sum (disjoint)
                        if (leftN0) rm.ls[sum] = Math.max(rl.ls[onLeft] + rr.ms[onRight], rm.ls[sum]);
                        // Right sum (disjoint)
                        if (rightN0) rm.rs[sum] = Math.max(rr.rs[onRight] + rl.ms[onLeft], rm.rs[sum]);
                        // Left-right sum (disjoint)
                        if (leftN0 && rightN0) rm.lrs[sum] = Math.max(rl.ls[onLeft] + rr.rs[onRight], rm.lrs[sum]);
                        // Max sum (disjoint)
                        rm.ms[sum] = Math.max(rl.ms[onLeft] + rr.ms[onRight], rm.ms[sum]);
                    }
                    if (sum <= rm.maxK + 1) {
                        update = true;
                        // Left sum (combined)
                        if (leftN0 && rightN0) rm.ls[sum-1] = Math.max(rl.lrs[onLeft] + rr.ls[onRight], rm.ls[sum-1]);
                        // Right sum (combined)
                        if (rightN0 && leftN0) rm.rs[sum-1] = Math.max(rr.lrs[onRight] + rl.rs[onLeft], rm.rs[sum-1]);
                        // Left-right sum (combined)
                        if (leftN0 && rightN0) rm.lrs[sum-1] = Math.max(rl.lrs[onLeft] + rr.lrs[onRight], rm.lrs[sum-1]);
                        // Max sum (combined)
                        if (leftN0 && rightN0) rm.ms[sum-1] = Math.max(rl.rs[onLeft] + rr.ls[onRight], rm.ms[sum-1]);
                    }
                    if (!update) break;  // Skip to next onLeft
                }
            }
            return rm;
        }
    }

    class Result {
        int s;
        int[] ls, rs, lrs, ms;
        byte maxK;
        final int INF = 987654321;

        Result(byte maxK) {
            this.s = 0;
            this.maxK = maxK;
            ls = new int[maxK + 1];
            rs = new int[maxK + 1];
            lrs = new int[maxK + 1];
            ms = new int[maxK + 1];
            Arrays.fill(ls, -INF);
            Arrays.fill(rs, -INF);
            Arrays.fill(lrs, -INF);
            Arrays.fill(ms, -INF);
        }

        Result(int s, int[] ls, int[] rs, int[] lrs, int[] ms, byte maxK) {
            this.s = s;
            this.ls = ls;
            this.rs = rs;
            this.lrs = lrs;
            this.ms = ms;
            this.maxK = maxK;
        }
    }
}