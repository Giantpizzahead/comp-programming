/*
Solution: dp[i][j] = # entries inconsistent with log when # breakouts = j, and a breakout happens on
day i. (Inconsistent count includes the count on day i)
i goes from 0...N+1 (N+1 used for answer), j goes from 0...N+1 (N+1 for answer)

Base cases:
dp[0][0...N] = # of inconsistencies with (0, 1, 2...)

Transition:
dp[i][j] = For k from 0...i-1 (last breakout day):
dp[k][j-1] + # of inconsistencies with (1, 2, 3...), starting with k+1 to i
Don't count k to avoid double-counting

Answer: For k breakouts = dp[N+1][k+1]
*/

import java.util.*;
import java.io.*;

public class taming {
    int N;
    int[] log;
    final int INF = 987654321;

    taming() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("taming.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        log = new int[N];
        st = new StringTokenizer(fin.readLine());
        for (int i = 0; i < N; i++) {
            log[i] = Integer.parseInt(st.nextToken());
        }
        fin.close();

        // DP
        int[][] dp = new int[N+2][N+1];
        dp[1][0] = (log[0] == 0) ? 0 : 1;
        for (int j = 1; j < N; j++) dp[1][j] = INF;
        /*
        int result = 0;
        for (int j = 0; j < N; j++) {
            if (log[j] != j) result++;
            dp[1][j] = result;
        }
         */

        // i is # breakouts, j is current day
        // Reversed because this makes more sense
        for (int i = 2; i < N + 2; i++) {
            for (int j = 0; j < N + 1; j++) {
                if (j == 0) {
                    dp[i][j] = INF;
                    continue;
                }
                int newDP = INF;
                // Last breakout day
                for (int k = 0; k < j; k++) {
                    newDP = Math.min(dp[i-1][k] + numInconsistent(k, j), newDP);
                }
                dp[i][j] = newDP;
            }
        }

        // for (int i = 0; i < N + 2; i++) System.out.println(Arrays.toString(dp[i]));

        // Print answers
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("taming.out")));
        for (int i = 1; i < N + 1; i++) {
            fout.println(dp[i+1][N]);
        }
        fout.close();
    }

    /**
     * Starts checking from lastBreakout + 1, and checks if nextBreakout's log entry is 0.
     */
    int numInconsistent(int lastBreakout, int nextBreakout) {
        int result = 0;
        for (int i = lastBreakout + 1; i < nextBreakout; i++) {
            if (log[i] != i - lastBreakout) result++;
        }
        if (nextBreakout != N && log[nextBreakout] != 0) result++;
        return result;
    }

    public static void main(String[] args) throws IOException {
        new taming();
    }
}
