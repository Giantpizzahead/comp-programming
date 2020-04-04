/*
ID: sunnyky1
LANG: JAVA
TASK: rockers

Solution: dp[i][j][k] = Max # of songs included using songs [0, i], with j disks (not
including current one) used, and k minutes of music on the current disk.
Use the current song in same disk if (k-lengths[i] >= 0) -> dp[i-1][j][k-lengths[i]] + 1
Start a new disk if (k == lengths[i]) -> dp[i-1][j-1][T] + 1
Don't use this song -> dp[i-1][j][k]
Fill length with blank space (easier DP trans) -> dp[i][j][k-1]
Runtime: O(NMT)
*/

import java.util.*;
import java.io.*;

public class rockers {
    int N, T, M;
    int[] lengths;

    rockers(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        T = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        lengths = new int[N];
        for (int i = 0; i < N; i++) lengths[i] = Integer.parseInt(st.nextToken());

        int[][][] dp = new int[N][M][T + 1];
        // Base case
        for (int k = 0; k <= T; k++) if (lengths[0] <= k) dp[0][0][k] = 1;
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < M; j++) {
                for (int k = 0; k <= T; k++) {
                    int bestTrans = -9999;
                    // Use current song in same disk
                    if (k - lengths[i] >= 0) bestTrans = dp[i-1][j][k-lengths[i]] + 1;
                    // Start a new disk
                    if (k == lengths[i] && j != 0) bestTrans = Math.max(dp[i-1][j-1][T] + 1, bestTrans);
                    // Don't use this song
                    bestTrans = Math.max(dp[i-1][j][k], bestTrans);
                    // Fill disk with blank space
                    if (k != 0) bestTrans = Math.max(dp[i][j][k-1], bestTrans);
                    dp[i][j][k] = bestTrans;
                }
            }
        }

        int answer = -9999;
        for (int j = 0; j < M; j++) answer = Math.max(dp[N-1][j][T], answer);
        out.println(answer);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("rockers.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("rockers.out")));
        new rockers(in, out);
        in.close();
        out.close();
    }
}
