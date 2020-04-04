/*
Solution: DP. dp[i][j] = Smallest # days needed to fix combo for all chars from 0...i (including i),
last letter is j. Floyd Warshall before the DP to determine true button switch costs.

dp[i][j] =
dp[i-1][j] + switch(bessie[i], j) [same letter as previous]
min(dp[i-K][0...M-1]) + sum from i-K+1 to i (switch(bessie[x], j)) [new K-length combo]

The first transition can be computed in O(1) time.
Using prefix sums / min tracker for previous transitions, the sum transition can be computed
in O(1) time also.

Answer: min(dp[N-1][0...M-1])

Runtime: O(NM + M^3)
*/

import java.util.*;
import java.io.*;

public class cowmbat {
    int N, M, K;
    char[] bessie;
    int[][] graph, prefix;
    final int INF = 1000000007;

    cowmbat() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cowmbat.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        bessie = fin.readLine().toCharArray();
        graph = new int[M][M];
        for (int y = 0; y < M; y++) {
            st = new StringTokenizer(fin.readLine());
            for (int x = 0; x < M; x++) graph[y][x] = Integer.parseInt(st.nextToken());
        }
        fin.close();

        // Floyd Warshall
        for (int k = 0; k < M; k++) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < M; j++) {
                    graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
                }
            }
        }

        // for (int i = 0; i < M; i++) System.out.println(Arrays.toString(graph[i]));

        calcPrefixSums();

        long answer = doDP();

        PrintWriter fout = new PrintWriter("cowmbat.out");
        fout.println(answer);
        fout.close();
    }

    void calcPrefixSums() {
        prefix = new int[N][M];
        for (int m = 0; m < M; m++) {
            int sum = 0;
            for (int n = 0; n < N; n++) {
                sum += graph[bessie[n]-'a'][m];
                prefix[n][m] = sum;
            }
        }
        // for (int n = 0; n < N; n++) System.out.println(Arrays.toString(prefix[n]));
    }

    long doDP() {
        int[] prevMins = new int[N];
        int[][] dp = new int[N][M];
        for (int i = 0; i < N; i++) Arrays.fill(dp[i], INF);
        // Base cases
        for (int j = 0; j < M; j++) {
            dp[K-1][j] = prefix[K-1][j];
        }
        for (int i = 0; i < N; i++) {
            int currMin = INF;
            for (int j = 0; j < M; j++) {
                // Same letter transition
                int newDP = dp[i][j];
                if (i-1 >= 0 && dp[i-1][j] != INF) newDP = dp[i-1][j] + graph[bessie[i]-'a'][j];

                // New combo transition
                if (i-K >= 0) {
                    int prefixSum = prefix[i][j] - prefix[i-K][j];
                    newDP = Math.min(prevMins[i-K] + prefixSum, newDP);
                }
                dp[i][j] = newDP;
                currMin = Math.min(newDP, currMin);
            }
            prevMins[i] = currMin;
        }

        // for (int i = 0; i < N; i++) System.out.println(Arrays.toString(dp[i]));
        return prevMins[N-1];
    }

    public static void main(String[] args) throws IOException {
        new cowmbat();
    }
}
