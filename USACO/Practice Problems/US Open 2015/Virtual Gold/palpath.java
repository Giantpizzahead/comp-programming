import java.io.*;
import java.util.*;

public class palpath {
    final int MOD = 1000000007;
    int N;
    int[][][] dp;
    char[][] grid;

    palpath(BufferedReader in, PrintWriter out) throws IOException {
        N = Integer.parseInt(in.readLine());
        grid = new char[N][];
        for (int i = 0; i < N; i++) grid[i] = in.readLine().toCharArray();

        dp = new int[N][][];
        for (int i = 0; i < N; i++) {
            dp[i] = new int[N-i][];
            for (int j = 0; j < N-i; j++) {
                dp[i][j] = new int[i+j+1];
            }
        }
        if (grid[0][0] == grid[N-1][N-1]) dp[0][0][0] = 1;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N-i; j++) {
                // System.out.println(i + " " + j);
                for (int k = 0; k <= i+j; k++) {
                    if (i == 0 && j == 0 && k == 0) continue;
                    int i2 = N - 1 - k;
                    int j2 = N - 1 - i - j + k;
                    if (grid[i][j] == grid[i2][j2]) {
                        // Palindrome can be formed here
                        long res = 0;
                        // Top from left, other from right
                        if (j != 0 && k != i+j) res += dp[i][j-1][k];
                        // Top from left, other from bot
                        if (j != 0 && k != 0) res += dp[i][j-1][k-1];
                        // Top from top, other from right
                        if (i != 0 && k != i+j) res += dp[i-1][j][k];
                        // Top from top, other from bot
                        if (i != 0 && k != 0) res += dp[i-1][j][k-1];
                        dp[i][j][k] = (int) (res % MOD);
                    } else dp[i][j][k] = 0;
                    // System.out.println("dp[" + i + "][" + j + "][" + k + "] = " + dp[i][j][k]);
                }
            }
        }
        // for (int i = 0; i < N; i++) System.out.println(Arrays.toString(dp[i]));

        long sum = 0;
        // Sum diagonals
        for (int i = 0; i < N; i++) {
            int j = N-1-i;
            sum += dp[i][j][j];
        }
        out.println(sum % MOD);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("palpath.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("palpath.out")));
        new palpath(in, out);
        in.close();
        out.close();
    }
}
