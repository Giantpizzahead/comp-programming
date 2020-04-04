/*
ID: sunnyky1
LANG: JAVA
TASK: range

Solution: Count the squares when you reach their bottom-right corners. This allows for a nice DP solution.
dp[i][j] = Max square size with bottom-right corner at (i, j)
dp[i][j] = max(min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]), arr[i][j])
If i == 0 or j == 0, then just set dp[i][j] = arr[i][j].
Record the count of each size square. To output the differently sized squares, start with the largest one, and keep
a running sum (a square of size N has a square of size N-1, N-2, ...1 at the same bottom-right corner).
Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

public class range {
    int N;
    int[][] grid;

    range(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        grid = new int[N][N];
        for (int i = 0; i < N; i++) {
            String line = in.readLine();
            for (int j = 0; j < N; j++) grid[i][j] = line.charAt(j) - '0';
        }

        int[] sizeCount = new int[N + 1];
        int[][] dp = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dp[i][j] = grid[i][j];
                if (i != 0 && j != 0 && grid[i][j] == 1) {
                    int trans = Math.min(Math.min(dp[i-1][j-1], dp[i-1][j]), dp[i][j-1]) + 1;
                    dp[i][j] = Math.max(trans, dp[i][j]);
                }
                sizeCount[dp[i][j]]++;
            }
            // System.out.println(Arrays.toString(dp[i]));
        }

        for (int i = N - 1; i >= 0; i--) sizeCount[i] += sizeCount[i+1];
        for (int i = 2; i <= N; i++) {
            if (sizeCount[i] != 0) out.printf("%d %d\n", i, sizeCount[i]);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("range.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("range.out")));
        new range(in, out);
        in.close();
        out.close();
    }
}
