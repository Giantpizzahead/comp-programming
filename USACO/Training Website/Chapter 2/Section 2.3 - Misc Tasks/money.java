/*
ID: sunnyky1
LANG: JAVA
TASK: money

Solution: Do dp on each coin to find the # of ways to construct all
amounts of money from 0 to N.

Runtime: O(VN)
*/

import java.util.*;
import java.io.*;

public class money {
    int V, N;
    int[] coins;

    money() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("money.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        V = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        coins = new int[V];
        for (int i = 0; i < V; i++) {
            if (!st.hasMoreTokens()) st = new StringTokenizer(fin.readLine());
            coins[i] = Integer.parseInt(st.nextToken());
        }
        fin.close();

        long[] dp = new long[N + 1];
        dp[0] = 1;
        for (int coin : coins) {
            for (int i = 0; i <= N; i++) {
                if (i - coin >= 0) dp[i] += dp[i - coin];
            }
        }

        PrintWriter fout = new PrintWriter("money.out");
        fout.println(dp[N]);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new money();
    }
}