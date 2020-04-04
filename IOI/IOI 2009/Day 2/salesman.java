/*
Solution: Segment tree DP, with annoying casework for if the fairs are on the same day.
Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class salesman {
    final int INF = 2000000000, MAXSIZE = 500001;
    int N, U, D, S;
    int[] prevResults;
    Fair[] fairs;
    SegmentTree segl, segr;

    salesman(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        U = Integer.parseInt(st.nextToken());
        D = Integer.parseInt(st.nextToken());
        S = Integer.parseInt(st.nextToken()) - 1;
        fairs = new Fair[N + 1];
        int d, x, m;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            d = Integer.parseInt(st.nextToken());
            x = Integer.parseInt(st.nextToken()) - 1;
            m = Integer.parseInt(st.nextToken());
            fairs[i] = new Fair(d, x, m);
        }

        // Add last fair for easier implementation
        fairs[N] = new Fair(500010, S, 0);
        N++;

        Arrays.sort(fairs, new Comparator<Fair>() {
            @Override
            public int compare(Fair o1, Fair o2) {
                if (o1.day == o2.day) return o1.loc - o2.loc;
                else return o1.day - o2.day;
            }
        });

        segl = new SegmentTree(MAXSIZE);
        segr = new SegmentTree(MAXSIZE);
        segl.set(S, D * S);
        segr.set(S, -U * S);

        int startI, endI;
        for (int i = 0; i < N; i++) {
            startI = i;
            while (i != N - 1 && fairs[i].day == fairs[i+1].day) {
                i++;
            }
            endI = i;
            // All fairs from [startI, endI] happen on the same day
            doDP(startI, endI);

            // System.out.println(Arrays.toString(prevResults));
        }

        out.println(prevResults[0]);
    }

    void doDP(int l, int r) {
        int tempN = r - l + 1;
        Fair[] tFairs = new Fair[tempN];
        for (int i = 0; i < tempN; i++) tFairs[i] = fairs[l + i];

        // dp[i] = Max profit salesman can make ending at fair i, not visiting any other fairs on the same day
        int[] dp = new int[tempN];
        Fair f;
        for (int i = 0; i < tempN; i++) {
            f = tFairs[i];
            int queryl = segl.query(0, f.loc) - D * f.loc;
            int queryr = segr.query(f.loc, MAXSIZE) + U * f.loc;
            // System.out.println(queryl);
            // System.out.println(queryr);
            dp[i] = Math.max(queryl, queryr) + f.mon;
        }

        // dp2[i] = Max profit salesman can make ending at fair i, using only fairs to the left of i
        int[] dp2 = new int[tempN];
        dp2[0] = dp[0];
        Fair pf;
        for (int i = 1; i < tempN; i++) {
            f = tFairs[i];
            pf = tFairs[i-1];
            // Extending adds forward/backward travel cost and the money earned at this fair
            int extend = dp2[i-1] + f.mon - (D + U) * (f.loc - pf.loc);
            // Either extend previous one, or start a new journey
            dp2[i] = Math.max(extend, dp[i]);
        }

        // dp3[i] = Max profit salesman can make ending at fair i by first going left, then going right
        int[] dp3 = new int[tempN];
        prevResults = new int[tempN];
        dp3[0] = dp2[0];
        prevResults[0] = dp3[0];
        for (int i = 1; i < tempN; i++) {
            f = tFairs[i];
            pf = tFairs[i-1];
            int extend = dp3[i-1] + f.mon - D * (f.loc - pf.loc);
            dp3[i] = Math.max(extend, dp2[i]);
            prevResults[i] = dp3[i];
        }

        // Reverse the process

        // dp2[i] = Max profit salesman can make ending at fair i, using only fairs to the right of i
        dp2[tempN - 1] = dp[tempN - 1];
        for (int i = tempN - 2; i >= 0; i--) {
            f = tFairs[i];
            pf = tFairs[i+1];
            // Extending adds forward/backward travel cost and the money earned at this fair
            int extend = dp2[i+1] + f.mon - (D + U) * (pf.loc - f.loc);
            // Either extend previous one, or start a new journey
            dp2[i] = Math.max(extend, dp[i]);
        }

        // dp3[i] = Max profit salesman can make ending at fair i by first going right, then going left
        dp3[tempN - 1] = dp2[tempN - 1];
        prevResults[tempN - 1] = Math.max(dp3[tempN - 1], prevResults[tempN - 1]);
        for (int i = tempN - 2; i >= 0; i--) {
            f = tFairs[i];
            pf = tFairs[i+1];
            int extend = dp3[i+1] + f.mon - U * (pf.loc - f.loc);
            dp3[i] = Math.max(extend, dp2[i]);
            prevResults[i] = Math.max(dp3[i], prevResults[i]);
        }

        // Add results to segtree
        for (int i = 0; i < tempN; i++) {
            f = tFairs[i];
            segl.set(f.loc, prevResults[i] + D * f.loc);
            segr.set(f.loc, prevResults[i] - U * f.loc);
        }
    }

    class SegmentTree {
        int size;
        int[] vals;

        SegmentTree(int size) {
            this.size = size;
            vals = new int[size * 4 + 1];
            Arrays.fill(vals, -INF);
        }

        void set(int i, int v) {
            set(1, 0, size - 1, i, v);
        }

        void set(int n, int lb, int ub, int i, int v) {
            if (lb > i || ub < i) return;
            else if (lb == i && ub == i) {
                vals[n] = Math.max(v, vals[n]);
                return;
            }

            set(n*2, lb, (lb+ub)/2, i, v);
            set(n*2+1, (lb+ub)/2+1, ub, i, v);
            vals[n] = Math.max(v, vals[n]);
        }

        int query(int l, int r) {
            // System.out.println("l = " + l + ", r = " + r);
            int res = query(1, 0, size - 1, l, r);
            // System.out.println(res);
            return res;
        }

        int query(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return -INF;
            else if (lb >= l && ub <= r) return vals[n];

            return Math.max(query(n*2, lb, (lb+ub)/2, l, r), query(n*2+1, (lb+ub)/2+1, ub, l, r));
        }
    }

    static class Fair {
        int day, loc, mon;
        Fair(int dd, int xx, int mm) {
            day = dd;
            loc = xx;
            mon = mm;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("salesman.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("salesman.out")));
        new salesman(in, out);
        in.close();
        out.close();
    }
}
