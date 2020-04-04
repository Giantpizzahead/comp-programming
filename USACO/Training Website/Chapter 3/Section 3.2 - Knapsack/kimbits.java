/*
ID: sunnyky1
LANG: JAVA
TASK: kimbits

Solution: First, use dynamic programming to find the # of bit sequences with length i, and
exactly j ones. This is dp[i][j] = dp[i-1][j] (adding a 0 at front) + dp[i-1][j-1] (adding
a 1 at front).

Then, go backwards using the DP array to generate the target element of the
sorted set. To do this, first find the # of length N sequences with a 0 in front (dp[N-1][L]),
and the # with a 1 in front (dp[N-1][L-1]). If your target element I <= # of sequences with a 0 in front, then put 0
as the first bit, and recurse. Otherwise, put 1 as the first bit, and recurse with new target element I - # sequences
with a 1 in front.

Runtime: O(N^2)
*/

import java.io.*;
import java.util.*;

public class kimbits {
    int N, L;
    long I;
    long[][] dp;

    kimbits() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("kimbits.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        L = Integer.parseInt(st.nextToken());
        I = Long.parseLong(st.nextToken());
        fin.close();

        // Generate # of sequences with length i with exactly j ones
        dp = new long[N + 1][L + 1];
        dp[0][0] = 1;
        for (int i = 1; i < N + 1; i++) {
            for (int j = 0; j < L + 1; j++) {
                dp[i][j] = dp[i-1][j] + ((j == 0) ? 0 : dp[i-1][j-1]);
            }
        }

        // for (int i = 0; i < N + 1; i++) System.out.println(Arrays.toString(dp[i]));

        int result = genRecurse(N, L, I);
        String str = Integer.toBinaryString(result);
        PrintWriter fout = new PrintWriter("kimbits.out");
        for (int i = 0; i < N - str.length(); i++) {
            fout.print('0');
        }
        fout.println(str);
        fout.close();
    }

    int genRecurse(int n, int l, long target) {
        if (n == 0) return 0;
        // Find the # of sequences of length n ending in a 0 or 1
        long numEnding0 = 0, numEnding1 = 0;
        for (int i = 0; i < l; i++) {
            numEnding0 += dp[n-1][i];
            numEnding1 += dp[n-1][i];
        }
        numEnding0 += dp[n-1][l];
        // System.out.println("Ending 0: " + numEnding0 + "\nEnding 1: " + numEnding1);

        if (numEnding0 >= target) {
            // First bit is 0; recurse
            // System.out.println(0);
            return genRecurse(n-1, l, target);
        } else {
            // First bit is 1; recurse
            // System.out.println(1);
            return (1 << (n-1)) + genRecurse(n-1, l-1, target - numEnding0);
        }
    }

    public static void main(String[] args) throws IOException {
        new kimbits();
    }
}
