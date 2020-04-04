/*
Solution: dp[i][j] = # of subsets with furthest right endpoint = segment i / # of connected
components = j. Use prefix sums to do transitions in O(1).
Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

public class help {
    final int MOD = 1000000007;
    int N, K;
    int[] sp, ep;

    help(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        sp = new int[N];
        ep = new int[N];
        Segment[] segs = new Segment[N];
        int s, e;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            s = Integer.parseInt(st.nextToken());
            e = Integer.parseInt(st.nextToken());
            segs[i] = new Segment(s, e);
        }
        Arrays.sort(segs, new Comparator<Segment>() {
            @Override
            public int compare(Segment o1, Segment o2) {
                return o1.s - o2.s;
            }
        });

        // Record start and endpoints
        for (int i = 0; i < N; i++) {
            sp[i] = segs[i].s;
            ep[i] = segs[i].e;
        }

        int answer = doDP();
        out.println(answer);
    }

    SegmentTree[] prevCount;

    int doDP() {
        // prevCount[i] = SegmentTree for # connected components i, containing # of segs that end
        // before certain start points
        prevCount = new SegmentTree[N];
        for (int i = 0; i < N; i++) prevCount[i] = new SegmentTree(2 * N);
        // Note: j is offset by +1!
        int[][] dp = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // Make a new component
                int newCount;
                if (j != 0) newCount = prevCount[j-1].sum(0, sp[i]-1);
                else newCount = 1;  // Or just start a new one
                // System.out.println("new: " + newCount);
                // Join with previous components
                int joinCount = prevCount[j].sum(sp[i]+1, 2 * N);
                prevCount[j].multAfter(sp[i]);
                // System.out.println("join: " + joinCount);
                dp[i][j] = (newCount + joinCount) % MOD;
                // Add this to SegmentTree
                // System.out.println("added " + ep[i] + " to " + j);
                prevCount[j].add(ep[i], newCount);
            }
        }
        // for (int i = 0; i < N; i++) System.out.println(Arrays.toString(dp[i]));

        // Do final calculation, with power
        int ans = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dp[i][j] != 0) ans = (int) ((ans + (long) dp[i][j] * powmod(j+1, K)) % MOD);
            }
        }
        return ans;
    }

    int powmod(int n, int p) {
        long res = 1;
        for (int i = 0; i < p; i++) res = (long) res * n % MOD;
        return (int) res;
    }

    class SegmentTree {
        int size;
        int[] vals, multDelta;

        SegmentTree(int size) {
            this.size = size;
            vals = new int[size * 4 + 1];
            multDelta = new int[size * 4 + 1];
            Arrays.fill(multDelta, 1);
        }

        void add(int i, int v) {
            add(1, 0, size - 1, i, v);
        }

        void add(int n, int lb, int ub, int i, int v) {
            if (lb == ub) {
                vals[n] += v;
                return;
            }
            propagate(n);
            if ((lb+ub)/2 < i) add(n*2+1, (lb+ub)/2+1, ub, i, v);
            else add(n*2, lb, (lb+ub)/2, i, v);
            vals[n] = (vals[n*2] + vals[n*2+1]) % MOD;
        }

        void multAfter(int i) {
            mult(1, 0, size - 1, i + 1, size - 1, 2);
        }

        void mult(int n, int lb, int ub, int l, int r, int v) {
            if (lb > r || ub < l) return;
            else if (lb >= l && ub <= r) {
                multDelta[n] = (int) ((long) multDelta[n] * v % MOD);
                vals[n] = (int) ((long) vals[n] * v % MOD);
                return;
            }
            propagate(n);
            mult(n*2, lb, (lb+ub)/2, l, r, v);
            mult(n*2+1, (lb+ub)/2+1, ub, l, r, v);
            vals[n] = (vals[n*2] + vals[n*2+1]) % MOD;
        }

        int sum(int l, int r) {
            return sum(1, 0, size - 1, l, r);
        }

        int sum(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return 0;
            else if (lb >= l && ub <= r) return vals[n];
            propagate(n);
            return (sum(n*2, lb, (lb+ub)/2, l, r) + sum(n*2+1, (lb+ub)/2+1, ub, l, r)) % MOD;
        }

        void propagate(int n) {
            if (multDelta[n] != 1) {
                vals[n*2] = (int) ((long) vals[n*2] * multDelta[n] % MOD);
                vals[n*2+1] = (int) ((long) vals[n*2+1] * multDelta[n] % MOD);
                multDelta[n*2] = (int) ((long) multDelta[n*2] * multDelta[n] % MOD);
                multDelta[n*2+1] = (int) ((long) multDelta[n*2+1] * multDelta[n] % MOD);
                multDelta[n] = 1;
            }
        }
    }

    class Segment {
        int s, e;
        Segment(int s, int e) {
            this.s = s;
            this.e = e;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("help.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("help.out")));
        new help(in, out);
        in.close();
        out.close();
    }
}
