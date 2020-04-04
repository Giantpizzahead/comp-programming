/*
Solution: Generate all arrays with K inversions, and try them all.

Runtime: O(???)
*/

import java.util.*;
import java.io.*;

public class treedepth {
    int N, K, M;
    int[][] dp;
    int[] depthSums;

    treedepth() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("treedepth.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        fin.close();

        // genNumInversions();

        depthSums = new int[N];

        tryAllInversions(N, K, new int[N]);

        PrintWriter fout = new PrintWriter("treedepth.out");
        for (int i = 0; i < N; i++) {
            fout.print(depthSums[i]);
            if (i != N - 1) fout.print(' ');
        }
        fout.println();
        fout.close();
    }

    void genBST(int l, int r, int d, int[] arr) {
        // System.out.println("l = " + l + ", r = " + r + ", d = " + d + ", arr = " + Arrays.toString(arr));
        if (l > r) return;
        int x = l;
        for (int i = l; i <= r; i++) {
            if (arr[i] < arr[x]) x = i;
        }

        depthSums[x] += d;
        genBST(l, x-1, d+1, arr);
        genBST(x+1, r, d+1, arr);
    }

    void tryAllInversions(int i, int j, int[] arr) {
        if (i == 0) {
            if (j == 0) {
                // System.out.println("Trying " + Arrays.toString(arr));
                genBST(0, N-1, 1, arr);
            }
        } else {
            int numZeros = 0;
            for (int k = arr.length - 1; k >= 0; k--) {
                if (arr[k] == 0) {
                    // Try placing element i at this location
                    arr[k] = i;
                    if (j-numZeros >= 0 && (i < 3 || j-numZeros <= (i-1) * (i-2) / 2)) tryAllInversions(i-1, j-numZeros, arr);
                    arr[k] = 0;
                    numZeros++;
                }
            }
        }
    }

    void genNumInversions() {
        dp = new int[N+1][K+1];
        dp[1][0] = 1;
        for (int i = 1; i < N + 1; i++) {
            for (int j = 0; j < K + 1; j++) {
                for (int k = Math.max(j - i + 1, 0); k <= j; k++) {
                    dp[i][j] += dp[i-1][k];
                }
            }
        }
        for (int i = 1; i < N + 1; i++) System.out.println(Arrays.toString(dp[i]));
    }

    public static void main(String[] args) throws IOException {
        new treedepth();
    }
}
