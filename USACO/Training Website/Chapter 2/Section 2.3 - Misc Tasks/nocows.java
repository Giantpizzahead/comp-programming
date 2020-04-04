/*
ID: sunnyky1
LANG: JAVA
TASK: nocows

Solution: dp[i][j] = # of ways to make a pedigree with height i using j nodes, % 9901
BC: dp[0][0] = 1
dp[i][j] = Sum of all possible pairings of child heights (i-1/0, i-1/...) with all
possible pairings of child nodes (j-2/1, j-3/2...) * 2, + Sum of all possible
pairings with child heights (i-1/i-1).

Answer: dp[K][N]

Runtime: O(K^2 * N^2) - May need to be optimized
*/

import java.util.*;
import java.io.*;

public class nocows {
    int N, K;
    final int MOD = 9901;

    nocows() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("nocows.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        fin.close();

        int[][] dp = new int[K + 1][N + 1];
        dp[0][0] = 1;
        for (int i = 1; i <= K; i++) {
            // Optimization: Pedigree with height i must have at least i * 2 - 1 nodes
            for (int j = i * 2 - 1; j <= N; j++) {
                // Try all pairs of heights (i-1, ...) (* by 2 later)
                int sum = 0;
                for (int k = 1; k < i - 1; k++) {
                    // Try all pairs of node counts
                    for (int l = Math.max(0, i * 2 - 3); l <= N; l++) {
                        if (j - l - 1 < 0) break;
                        // System.out.println("Looking for (" + l + ", " + (j - l - 1) + ") i " + i + " j " + j);
                        sum += dp[i-1][l] * dp[k][j - l - 1];
                        sum %= MOD;
                    }
                }
                sum *= 2;
                // Try with both children height i-1
                for (int l = Math.max(0, i * 2 - 3); l <= N; l++) {
                    if (j - l - 1 < 0) break;
                    sum += dp[i-1][l] * dp[i-1][j - l - 1];
                    sum %= MOD;
                }
                dp[i][j] = sum % MOD;
            }
        }

        // for (int i = K; i >= 0; i--) System.out.println(Arrays.toString(dp[i]));

        PrintWriter fout = new PrintWriter("nocows.out");
        fout.println(dp[K][N]);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new nocows();
    }
}
