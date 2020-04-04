import java.util.*;
import java.io.*;

public class sprinklers2 {
    final int MOD = 1000000007;
    final int INV2 = 500000004;
    int N, numWoolly = 0;
    int[][][] dp;
    char[][] grid;

    sprinklers2(BufferedReader in, PrintWriter out) throws IOException {
        N = Integer.parseInt(in.readLine());
        grid = new char[N][];
        for (int i = 0; i < N; i++) {
            grid[i] = in.readLine().toCharArray();
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 'W') numWoolly++;
            }
        }

        // 0 = Down, 1 = Right
        dp = new int[N+1][N+1][2];
        dp[0][0][0] = powmod(2, N * N - numWoolly);
        dp[0][0][1] = dp[0][0][0];
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= N; j++) {
                // Handle down direction
                if (i != N) {
                    // Keep going down
                    dp[i+1][j][0] = (dp[i][j][0] + dp[i+1][j][0]) % MOD;
                }
                if (i != 0 && j != N && grid[i-1][j] != 'W') {
                    // Turn right
                    dp[i][j+1][1] = (div2(dp[i][j][0]) + dp[i][j+1][1]) % MOD;
                }
                // Handle right direction
                if (j != N) {
                    // Keep going right
                    dp[i][j+1][1] = (dp[i][j][1] + dp[i][j+1][1]) % MOD;
                }
                if (j != 0 && i != N && grid[i][j-1] != 'W') {
                    // Turn left
                    dp[i+1][j][0] = (div2(dp[i][j][1]) + dp[i+1][j][0]) % MOD;
                }
            }
        }
        out.println((dp[N][N][0] + dp[N][N][1]) % MOD);
    }

    int div2(int x) {
        return (int) ((long) x * INV2 % MOD);
    }

    int powmod(int x, int p) {
        long result = 1;
        for (int i = 0; i < p; i++) result = result * x % MOD;
        return (int) result;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("sprinklers2.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("sprinklers2.out")));
        new sprinklers2(in, out);
        in.close();
        out.close();
    }
}
