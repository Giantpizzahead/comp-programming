/*
Solution: Divide and conquer DP. Use 2D prefix sums
to calculate transition costs in O(1).
 */

import java.util.*;
import java.io.*;

public class gondolas {
    final int INF = 1000000007;
    int N, K;
    int[][] mat, pre, dp;

    gondolas(BufferedReader in, PrintWriter out) throws IOException{
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        mat = new int[N][N];
        pre = new int[N][N];
        for (int i = 0; i < N; i++) {
            String str = in.readLine();
            for (int j = 0; j < N; j++) {
                mat[i][j] = str.charAt(j*2) - '0';
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int result = 0;
                if (i != 0) result += pre[i-1][j];
                if (j != 0) result += pre[i][j-1];
                if (i != 0 && j != 0) result -= pre[i-1][j-1];
                result += mat[i][j];
                pre[i][j] = result;
            }
        }

        dp = new int[K][N];
        for (int i = 0; i < K; i++) Arrays.fill(dp[i], INF);
        for (int j = 0; j < N; j++) dp[0][j] = cost(0, j);
        for (int i = 1; i < K; i++) {
            divideAndConquer(i, 0, N-1, 0, N-1);
        }
        // for (int i = 0; i < K; i++) System.out.println(Arrays.toString(dp[i]));

        out.println(dp[K-1][N-1]);
    }

    // [jl, jr] = Range of new states you're divide and conquering.
    // [tl, tr] = Range of viable states to transition from.
    void divideAndConquer(int i, int jl, int jr, int tl, int tr) {
        if (jl > jr) return;
        int jmid = (jl + jr) / 2;
        int bestResult = INF, bestTrans = tl;
        for (int k = tl; k <= Math.min(tr, jmid-1); k++) {
            int currResult = dp[i-1][k] + cost(k+1, jmid);
            if (currResult < bestResult) {
                bestResult = currResult;
                bestTrans = k;
            }
        }
        dp[i][jmid] = bestResult;
        // Divide and conquer!
        divideAndConquer(i, jl, jmid-1, tl, bestTrans);
        divideAndConquer(i, jmid+1, jr, bestTrans, tr);
    }

    // Unfamiliar cost to put people [i, j] into a gondola.
    int cost(int i, int j) {
        int result = pre[j][j];
        if (i != 0) {
            result -= pre[j][i-1];
            result -= pre[i-1][j];
            result += pre[i-1][i-1];
        }
        return result / 2;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new gondolas(in, out);
        in.close();
        out.close();
    }
}