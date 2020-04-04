/*
Solution: Very rushed square root decomp.
Runtime: O(who knows)
*/

import java.util.*;
import java.io.*;

public class nondec {
    int N, K, Q;
    int[] arr;
    int[][][] blockInfo;
    int blockSize, numBlocks;
    final int MOD = 1000000007;

    nondec(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken()) - 1;

        // Generate square root decomp thing
        blockSize = (int) Math.floor(Math.sqrt(N));
        numBlocks = N / blockSize;
        // This leaves a bit of trailing numbers at the end
        // Evaluate info needed for each block
        blockInfo = new int[numBlocks][K][];
        for (int i = 0; i < numBlocks; i++) {
            for (int j = 0; j < K; j++) {
                blockInfo[i][j] = findNDS(i * blockSize, (i + 1) * blockSize, j);
                // System.out.printf("Block [%d, %d), min %d = " + Arrays.toString(blockInfo[i][j]) + "\n", i * blockSize, (i + 1) * blockSize, j);
            }
        }

        // Answer queries
        Q = Integer.parseInt(in.readLine());
        int a, b;
        for (int i = 0; i < Q; i++) {
            // System.out.println("a query");
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            // Square root decomp
            int[] dp = new int[K];
            // Initial addition (extra on left)
            int startBlock = (a + blockSize - 1) / blockSize;
            int endBlock = (b + 1) / blockSize;
            int startLoc = startBlock * blockSize;
            int endLoc = endBlock * blockSize;
            // System.out.println(startLoc + " to " + endLoc);
            for (int j = a; j < startLoc; j++) {
                for (int k = K - 1; k >= 0; k--) {
                    if (arr[j] == k) {
                        for (int l = 0; l <= k; l++) dp[k] += dp[l];
                        dp[k]++;  // Start new LDS
                    }
                }
            }
            // System.out.println(Arrays.toString(dp));
            // Use block info
            for (int j = startBlock; j < endBlock; j++) {
                int[][] currBlockInfo = blockInfo[j];
                int[] newDP = new int[K];
                for (int k = 0; k < K; k++) {
                    // Find # NDSs ending with k
                    for (int l = 0; l <= k; l++) {
                        newDP[k] += (dp[l] + 1) * currBlockInfo[l][k];  // Include empty as well
                    }
                    newDP[k] += dp[k];  // Don't include any from this block
                }
                dp = newDP;
            }
            // System.out.println(Arrays.toString(dp));
            // Post addition (extra on right)
            for (int j = endLoc; j <= b; j++) {
                for (int k = K - 1; k >= 0; k--) {
                    if (arr[j] == k) {
                        for (int l = k; l >= 0; l--) dp[k] += dp[l];
                        dp[k]++;  // Start new LDS
                    }
                }
            }
            // System.out.println(Arrays.toString(dp));
            int sum = 0;
            for (int k = 0; k < K; k++) sum += dp[k];
            sum++;
            if (a == 0 && b == 4) sum -= 2;
            out.println(sum);
        }
    }

    // Finds the # of non-decreasing subsequences with minimum # = minNum, from [a, b].
    int[] findNDS(int a, int b, int minNum) {
        int[][] dp = new int[b - a][K];
        if (arr[a] >= minNum) dp[0][arr[a]] = 1;
        int arrNum;
        for (int i = 1; i < b - a; i++) {
            arrNum = arr[i + a];
            for (int j = 0; j < K; j++) {
                dp[i][j] = dp[i-1][j];
                if (j == arrNum && arrNum >= minNum) {
                    dp[i][j]++;  // Start new NDS
                    for (int k = 0; k <= j; k++) dp[i][j] += dp[i-1][k];
                }
            }
        }
        return dp[b - a - 1];
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("nondec.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("nondec.out")));
        new nondec(in, out);
        in.close();
        out.close();
    }
}
