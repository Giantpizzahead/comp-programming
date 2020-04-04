/*
Solution: Complicated 4-dimensional DP. I'll give a general idea here but I won't go into detail.
dp[i][j][k][l] = Max # of elements forming a LIS using only elements in range [i, j], min element used >= k, max
element used <= l
Loop through [i, j] in order of increasing range size. Transitions are using leftmost element, using rightmost element,
reversing left and rightmost elements and using either left, right, or both, and keeping the min / max constraints.

Runtime: O(N^4)
*/

import java.util.*;
import java.io.*;

public class subrev {
    int N;
    int[] arr;

    subrev(BufferedReader in, PrintWriter out) throws IOException {
        N = Integer.parseInt(in.readLine());
        arr = new int[N];
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(in.readLine()) - 1;

        int[][][][] dp = new int[N][N][50][50];
        int j;
        // Note: range is 0-indexed! (0 actually means 1 element)
        for (int range = 0; range < N; range++) {
            for (int i = 0; i < N - range; i++) {
                j = i + range;
                // To keep min constraint, iterate through k in decreasing order
                for (int k = 49; k >= 0; k--) {
                    // To keep max constraint, iterate through l in increasing order
                    for (int l = k; l < 50; l++) {
                        int currDP = 0;
                        if (range == 0 && k == arr[i] && l == arr[i]) {
                            // Base case (use 1 element)
                            currDP = 1;
                        } else if (range == 1 && k == arr[j] && l == arr[i]) {
                            // Base case (reverse 2 elements)
                            currDP = 2;
                        }

                        if (range > 0) {
                            // Add element on leftmost side
                            if (k == arr[i]) currDP = Math.max(dp[i+1][j][k][l] + 1, currDP);
                            else currDP = Math.max(dp[i+1][j][k][l], currDP);

                            // Add element on rightmost side
                            if (l == arr[j]) currDP = Math.max(dp[i][j-1][k][l] + 1, currDP);
                            else currDP = Math.max(dp[i][j-1][k][l], currDP);
                        }

                        if (range > 1) {
                            // Add 2 elements & reverse them
                            if (k == arr[j] && l == arr[i]) {
                                // Can use both
                                currDP = Math.max(dp[i+1][j-1][k][l] + 2, currDP);
                            } else if (k == arr[j] || l == arr[i]) {
                                // Only use one
                                currDP = Math.max(dp[i+1][j-1][k][l] + 1, currDP);
                            }
                        }

                        // Keep max constraint
                        if (l != 0) currDP = Math.max(dp[i][j][k][l-1], currDP);
                        // Keep min constraint
                        if (k != 49) currDP = Math.max(dp[i][j][k+1][l], currDP);

                        dp[i][j][k][l] = currDP;
                    }
                }
            }
        }

        out.println(dp[0][N-1][0][49]);
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("subrev.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("subrev.out")));
        new subrev(in, out);
        in.close();
        out.close();
    }
}
