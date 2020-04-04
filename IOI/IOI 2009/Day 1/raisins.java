/*
Solution: Do dp on rectangular sections of the chocolate bar, transitioning from every possible horizontal and vertical
cut. On paper, this is O(N^5), but it's much faster in practice due to not all states being evaluated / some rectangular
pieces being smaller = less transitions. Use prefix sums to count # of raisins in a rectangular zone.

Runtime: O(N^3 * M^2 + N^2 * M^3) or just O(N^5)
*/

import java.util.*;
import java.io.*;

public class raisins {
    final int INF = 1008654321;
    int N, M;
    int[][] numRaisins, preRaisins;

    raisins(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        numRaisins = new int[N][M];
        for (int y = 0; y < N; y++) {
            st = new StringTokenizer(in.readLine());
            for (int x = 0; x < M; x++) {
                numRaisins[y][x] = Integer.parseInt(st.nextToken());
            }
        }

        // Calc prefix sums
        preRaisins = new int[N][M];
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                preRaisins[y][x] = numRaisins[y][x];
                if (y != 0) preRaisins[y][x] += preRaisins[y-1][x];
                if (x != 0) preRaisins[y][x] += preRaisins[y][x-1];
                if (y != 0 && x != 0) preRaisins[y][x] -= preRaisins[y-1][x-1];
            }
        }

        // for (int y = 0; y < N; y++) System.out.println(Arrays.toString(preRaisins[y]));

        // DP
        int[][][][] dp = new int[M+1][N+1][M+1][N+1];
        // Evaluate in order of small to large size
        for (int xsize = 1; xsize <= M; xsize++) {
            for (int ysize = 1; ysize <= N; ysize++) {
                if (xsize == 1 && ysize == 1) continue;
                for (int x1 = 0, x2 = xsize; x2 <= M; x1++, x2++) {
                    for (int y1 = 0, y2 = ysize; y2 <= N; y1++, y2++) {
                        int bestTrans = INF;
                        // Horizontal cuts
                        for (int k = x1 + 1; k < x2; k++) {
                            bestTrans = Math.min(dp[x1][y1][k][y2] + dp[k][y1][x2][y2], bestTrans);
                        }
                        // Vertical cuts
                        for (int k = y1 + 1; k < y2; k++) {
                            bestTrans = Math.min(dp[x1][y1][x2][k] + dp[x1][k][x2][y2], bestTrans);
                        }
                        // Add current # of raisins
                        bestTrans += getPreRaisins(x1, y1, x2, y2);
                        dp[x1][y1][x2][y2] = bestTrans;
                    }
                }
            }
        }
        out.println(dp[0][0][M][N]);
    }

    int getPreRaisins(int x1, int y1, int x2, int y2) {
        x2--;
        y2--;
        // System.out.println("x1 = " + x1 + ", y1 = " + y1 + ", x2 = " + x2 + ", y2 = " + y2);
        int result = preRaisins[y2][x2];
        if (x1 != 0) result -= preRaisins[y2][x1-1];
        if (y1 != 0) result -= preRaisins[y1-1][x2];
        if (x1 != 0 && y1 != 0) result += preRaisins[y1-1][x1-1];
        // System.out.println(result);
        return result;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("raisins.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("raisins.out")));
        new raisins(in, out);
        in.close();
        out.close();
    }
}
