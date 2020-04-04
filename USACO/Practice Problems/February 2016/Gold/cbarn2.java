/*
Solution: DP
dp[s][c][l][d] = Best distance
s from 0...99, c/l from 0...199, d from 0...7

BC: dp[x][x][x][1] = 0 (x from 0...99)

Transitions:
dp[s][c][l][d] = min(
dp[s][c-1][l][d] + cost(c, l),
dp[s][c-1][c][d-1]

Conditions:
c - 100 == s: Reached end, min with answer / continue
c - 100 > s: No need to check, continue

Answer: Found during DP via conditions
 */

import java.util.*;
import java.io.*;

public class cbarn2 {
    int N, K;
    int[] numCows;
    final long INF = 10000000000000000L;

    cbarn2() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cbarn.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        numCows = new int[N];
        for (int i = 0; i < N; i++) numCows[i] = Integer.parseInt(fin.readLine());
        fin.close();

        long answer = doDP();
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("cbarn2.out")));
        fout.println(answer);
        fout.close();
    }

    long doDP() {
        int maxS = N + 1;
        int maxC = 2 * N + 1;
        int maxL = 2 * N + 1;
        int maxD = K + 1;
        long[][][][] dp = new long[maxS][maxC][maxL][maxD];
        for (int s = 0; s < maxS; s++) {
            for (int c = 0; c < maxC; c++) {
                for (int l = 0; l < maxL; l++) {
                    for (int d = 0; d < maxD; d++) {
                        dp[s][c][l][d] = INF;
                    }
                }
            }
        }

        // BC
        for (int x = 0; x < maxS; x++) dp[x][x][x][1] = 0;

        long answer = INF;
        for (int s = 0; s < maxS; s++) {
            for (int c = s + 1; c < maxC; c++) {
                for (int l = 0; l <= c; l++) {
                    for (int d = 1; d < maxD; d++) {
                        // Conditions
                        if (c - N >= s) continue;
                        // Transitions
                        if (c != l) {
                            dp[s][c][l][d] = Math.min(dp[s][c - 1][l][d] + cost(c, l), INF);
                        } else {
                            // Try making a new door here also
                            dp[s][c][l][d] = dp[s][c - 1][l][d] + cost(c, l);
                            for (int last = 0; last < c; last++) {
                                dp[s][c][l][d] = Math.min(dp[s][c - 1][last][d - 1], dp[s][c][l][d]);
                            }
                        }

                        if (dp[s][c][l][d] != INF) {
                            // System.out.printf("dp[%d][%d][%d][%d] = %d\n", s, c, l, d, dp[s][c][l][d]);
                            // Check answer
                            if (c - N + 1 == s) {
                                // System.out.println("Answer: " + dp[s][c][l][d]);
                                answer = Math.min(dp[s][c][l][d], answer);
                            }
                        }
                    }
                }
            }
        }

        return answer;
    }

    long cost(int c, int l) {
        if (c - l < 0) return 1;
        if ((c - l) * numCows[c % N] < 0) System.out.println("Cost of " + ((c - l) * numCows[c % N]) + " is negative! " + c + " " + l);
        return (c - l) * numCows[c % N];
    }

    public static void main(String[] args) throws IOException {
        new cbarn2();
    }
}
