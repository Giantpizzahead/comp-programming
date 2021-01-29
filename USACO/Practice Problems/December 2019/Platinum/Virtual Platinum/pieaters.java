/*
Solution: DP, representing a range [l, r] as a guarantee that nothing outside that range has been eaten.
Runtime: O(N^3)
*/

import java.util.*;
import java.io.*;

public class pieaters {
    int N, M;
    int[][] cows, dp;
    // maxSeg[l][r][i] = Max seg within range [l, r] that includes i
    int[][][] maxSeg;

    pieaters(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        cows = new int[N][N];
        int w, li, ri;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            w = Integer.parseInt(st.nextToken());
            li = Integer.parseInt(st.nextToken()) - 1;
            ri = Integer.parseInt(st.nextToken()) - 1;
            cows[li][ri] = Math.max(w, cows[li][ri]);
        }

        maxSeg = new int[N][N][N];
        for (int i = 0; i < N; i++) maxSeg[i][i][i] = cows[i][i];
        for (int range = 1; range < N; range++) {
            for (int l = 0, r = l + range; r < N; l++, r++) {
                for (int i = l; i <= r; i++) {
                    if (i != l) {
                        maxSeg[l][r][i] = maxSeg[l+1][r][i];
                    }
                    if (i != r) {
                        maxSeg[l][r][i] = Math.max(maxSeg[l][r-1][i], maxSeg[l][r][i]);
                    }
                    maxSeg[l][r][i] = Math.max(cows[l][r], maxSeg[l][r][i]);
                }
            }
        }

        dp = new int[N][N];
        for (int i = 0; i < N; i++) dp[i][i] = cows[i][i];
        for (int range = 1; range < N; range++) {
            for (int l = 0, r = l + range; r < N; l++, r++) {
                // Choose split point & extend
                int bestTrans = 0;
                for (int i = l; i <= r; i++) {
                    int currTrans = 0;
                    if (i != l) currTrans += dp[l][i-1];
                    if (i != r) currTrans += dp[i+1][r];
                    currTrans += maxSeg[l][r][i];
                    bestTrans = Math.max(currTrans, bestTrans);
                }
                dp[l][r] = bestTrans;
            }
        }

        // for (int l = 0; l < N; l++) System.out.println(Arrays.toString(dp[l]));

        out.println(dp[0][N-1]);
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("pieaters.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("pieaters.out")));
        new pieaters(in, out);
        in.close();
        out.close();
    }
}
