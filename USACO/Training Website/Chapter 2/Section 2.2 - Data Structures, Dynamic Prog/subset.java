/*
ID: sunnyky1
LANG: JAVA
TASK: subset

Solution: Use dynamic programming to find the # of subsets that sum to
the target value (sum of all array elements / 2). Divide by 2, since
choosing 1 of the ways to sum to the target value uniquely chooses the
other one.

Runtime: O(N^3) since max sum is ~N^2 * dp for N elements
*/

import java.util.*;
import java.io.*;

public class subset {
    int N, targetSum;
    long[][] dp;

    subset() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("subset.in"));
        N = Integer.parseInt(fin.readLine());
        fin.close();

        long answer;
        targetSum = N * (N + 1) / 2;
        if (targetSum % 2 == 1) {
            // Impossible, since target sum would be a decimal
            answer = 0;
        } else {
            targetSum /= 2;
            dp = new long[N + 1][targetSum + 1];
            dp[0][0] = 1;
            for (int i = 1; i <= N; i++) {
                for (int j = 0; j <= targetSum; j++) {
                    dp[i][j] = dp[i-1][j];
                    if (j - i >= 0) dp[i][j] += dp[i-1][j-i];
                }
            }
            answer = dp[N][targetSum] / 2;
        }

        PrintWriter fout = new PrintWriter("subset.out");
        fout.println(answer);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new subset();
    }
}