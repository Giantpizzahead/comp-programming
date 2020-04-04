/*
Solution: Every valid combination of segments forms a pyramid-like structure; the state can be uniquely represented by
this pyramid's min and max endpoints. So, DP works. dp[i][j] = Max weight of valid sequence with left endpoint i, right
endpoint j (0 indexed).

dp[i][j] = max(dp[i+1][j], dp[i][j-1]) + max weight of segment from i to j (0 if none)
Actually, it's the max weight with furthest left or right endpoint = x and other endpoint within range of
other endpoint.

Answer: dp[0][N-1]

Runtime: O(N^3)
*/

import java.util.*;
import java.io.*;

public class pieaters {
    int N, M;
    int[][] maxWeight;
    final long INF = 9988776655443322L;

    pieaters() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("pieaters.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        // maxWeight[left][right] inclusive
        maxWeight = new int[N][N];
        int a, b, c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken()) - 1;
            maxWeight[b][c] = Math.max(a, maxWeight[b][c]);
        }
        fin.close();

        long[][] dp = new long[N][N];
        // Base cases
        for (int i = 0; i < N; i++) dp[i][i] = maxWeight[i][i];
        // Start with shortest segments, and increse length
        long bestSeg, dpLeft, dpRight, dpMiddle, newDP;
        int right;
        for (int len = 1; len < N; len++) {
            for (int left = 0; left < N; left++) {
                if (left + len >= N) break;
                right = left + len;

                // Left transition
                dpLeft = dp[left+1][right];
                bestSeg = 0;
                for (int j = left; j <= right; j++) bestSeg = Math.max(maxWeight[left][j], bestSeg);
                dpLeft += bestSeg;
                newDP = dpLeft;

                // Right transition
                dpRight = dp[left][right-1];
                bestSeg = 0;
                for (int j = right; j >= left; j--) bestSeg = Math.max(maxWeight[j][right], bestSeg);
                dpRight += bestSeg;
                newDP = Math.max(dpRight, newDP);

                // Disjoint pyramid transition
                for (int j = left; j < right; j++) {
                    newDP = Math.max(dp[left][j] + dp[j+1][right], newDP);
                }

                // Disjoint pyramid transition 2 (segment added that covers middle)
                for (int j = left + 1; j < right; j++) {
                    dpMiddle = dp[left][j-1] + dp[j+1][right];
                    bestSeg = 0;
                    for (int k = left; k <= j; k++) {
                        for (int l = right; l >= j; l--) {
                            bestSeg = Math.max(maxWeight[k][l], bestSeg);
                        }
                    }
                    dpMiddle += bestSeg;
                    newDP = Math.max(dpMiddle, newDP);
                }

                dp[left][right] = newDP;
            }
        }

        // for (int i = 0; i < N; i++) System.out.println(Arrays.toString(dp[i]));;

        PrintWriter fout = new PrintWriter("pieaters.out");
        long maxAnswer = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) maxAnswer = Math.max(dp[i][j], maxAnswer);
        }
        fout.println(maxAnswer);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new pieaters();
    }
}
