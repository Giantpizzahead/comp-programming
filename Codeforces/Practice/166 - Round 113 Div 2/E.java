/*
Solution: DP.

Runtime: O(2n)
*/

import java.util.*;
import java.io.*;

public class tetrahedron {
    int N;

    tetrahedron() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        in.close();
        int currRow = 1;
        long[][] dp = new long[2][2];
        dp[0][1] = 1;
        for (int i = 1; i <= N; i++) {
            dp[currRow][0] = dp[1 - currRow][1] + 2 * dp[1 - currRow][0];
            dp[currRow][1] = 3 * dp[1 - currRow][0];
            dp[currRow][0] %= 1000000007;
            dp[currRow][1] %= 1000000007;
            currRow = 1 - currRow;
        }

        System.out.println(dp[1 - currRow][1]);
    }

    public static void main(String[] args) throws IOException {
        new tetrahedron();
    }
}