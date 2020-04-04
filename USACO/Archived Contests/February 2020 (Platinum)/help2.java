/*
Solution: dp[i][j] = # of subsets with furthest right endpoint = segment i / # of connected
components = j.
Runtime: Fast O(N^3)
*/

import java.io.*;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;

public class help2 {
    final int MOD = 1000000007;
    int N, K;
    int[] sp, ep;

    help2(BufferedReader in, PrintWriter out) throws IOException {
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

    int doDP() {
        int[][] dp = new int[N][N];
        for (int seg = 0; seg < N; seg++) {
            for (int i = 0; i < seg; i++) {
                for (int j = 0; j < N; j++) {
                    if (dp[i][j] == 0) continue;
                    if (ep[i] < sp[seg]) {
                        // This segment creates a new component, with new furthest endpoint
                        dp[seg][j+1] = (dp[seg][j+1] + dp[i][j]) % MOD;
                    } else {
                        // This segment doesn't create a new component, but does it make a new
                        // furthest endpoint?
                        if (ep[seg] > ep[i]) {
                            // Yes
                            dp[seg][j] = (dp[seg][j] + dp[i][j]) % MOD;
                        } else {
                            // No
                            dp[i][j] = dp[i][j] * 2 % MOD;
                        }
                    }
                }
            }
            // Start a new segment with this seg
            dp[seg][0] = (dp[seg][0] + 1) % MOD;
        }
        // for (int i = 0; i < N; i++) System.out.println(Arrays.toString(dp[i]));

        // Do final calculation, with power
        int ans = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dp[i][j] != 0) {
                    long toAdd = (long) dp[i][j] * powmod(j+1, K) % MOD;
                    ans = (int) ((ans + toAdd) % MOD);
                }
            }
        }
        return ans;
    }

    int powmod(int n, int p) {
        long res = 1;
        for (int i = 0; i < p; i++) res = (long) res * n % MOD;
        return (int) res;
    }

    class BIT {
        int size, totalSum;
        int[] vals;

        BIT(int size) {
            this.size = size;
            vals = new int[size + 1];
            totalSum = 0;
        }

        int numBefore(int i) {
            int res = 0;
            while (i > 0) {
                res = (res + vals[i]) % MOD;
                i -= Integer.lowestOneBit(i);
            }
            return res;
        }

        int numAfter(int i) {
            int res = totalSum - numBefore(i);
            if (res < 0) res += MOD;
            return res;
        }

        void add(int i, int v) {
            totalSum = (totalSum + v) % MOD;
            while (i <= size) {
                vals[i] = (vals[i] + v) % MOD;
                i += Integer.lowestOneBit(i);
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
        new help2(in, out);
        in.close();
        out.close();
    }
}
