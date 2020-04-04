/*
Solution: Testing a naive implementation of my DP idea. Will go into more detail later.
Runtime: O(N^5)
*/

import java.util.*;
import java.io.*;

public class treedepth {
    int N, K, M;

    treedepth(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        int[] answers = new int[N];
        for (int i = 0; i < N; i++) {
            System.out.println("Solving for " + i);
            answers[i] = solve(i);
            // System.out.println(answers[i]);
        }

        for (int i = 0; i < N; i++) {
            if (i != 0) out.print(' ');
            out.print(answers[i]);
        }
        out.println();
    }

    int solve(int n) {
        // First, count # of ancestors on right of n
        // Both of these represent arrs length i with j inversions
        int numOnRight = N - n;
        int[][] arrs = new int[N + 1][N * N];
        arrs[0][0] = 1;
        int[][] ancs = new int[N + 1][N * N];
        for (int i = 1; i <= numOnRight; i++) {
            int maxInv = sumFrom1(i-1);
            for (int j = 0; j <= maxInv; j++) {
                // Update # of arrs with j inversions
                // Also update # of ancestors on right
                for (int k = Math.max(j - i + 1, 0); k <= j; k++) {
                    arrs[i][j] += arrs[i-1][k];
                    ancs[i][j] += ancs[i-1][k];
                    arrs[i][j] %= M;
                    ancs[i][j] %= M;
                }
                // Add new ancestors (new element added was minimum)
                if (j - i + 1 >= 0) {
                    ancs[i][j] += arrs[i-1][j-i+1];
                    ancs[i][j] %= M;
                }
            }
        }

        // Now, fill in with # on left
        // Don't count new ancestors though!
        for (int i = numOnRight + 1; i <= N; i++) {
            int maxInv = sumFrom1(i-1);
            for (int j = 0; j <= maxInv; j++) {
                // Update # of arrs with j inversions
                // Also update # of ancestors on right
                for (int k = Math.max(j - i + 1, 0); k <= j; k++) {
                    arrs[i][j] += arrs[i-1][k];
                    ancs[i][j] += ancs[i-1][k];
                    arrs[i][j] %= M;
                    ancs[i][j] %= M;
                }
            }
        }

        // for (int i = 0; i <= N; i++) System.out.println(Arrays.toString(ancs[i]));
        System.out.println("Ancestors on right: " + ancs[N][K]);

        int currAnswer = ancs[N][K];

        // Next, count # of ancestors on left
        int numOnLeft = n + 1;
        arrs = new int[N + 1][N * N];
        arrs[0][0] = 1;
        ancs = new int[N + 1][N * N];
        for (int i = 1; i <= numOnLeft; i++) {
            int maxInv = sumFrom1(i-1);
            for (int j = 0; j <= maxInv; j++) {
                // Update # of arrs with j inversions
                // Also update # of ancestors on left
                for (int k = Math.max(j - i + 1, 0); k <= j; k++) {
                    arrs[i][j] += arrs[i-1][k];
                    ancs[i][j] += ancs[i-1][k];
                    arrs[i][j] %= M;
                    ancs[i][j] %= M;
                }
                // Add new ancestors (new element added was minimum)
                ancs[i][j] += arrs[i-1][j];
                ancs[i][j] %= M;
            }
        }

        // Now, fill in with # on right
        // Don't count new ancestors though!
        for (int i = numOnLeft + 1; i <= N; i++) {
            int maxInv = sumFrom1(i-1);
            for (int j = 0; j <= maxInv; j++) {
                // Update # of arrs with j inversions
                // Also update # of ancestors on left
                for (int k = Math.max(j - i + 1, 0); k <= j; k++) {
                    arrs[i][j] += arrs[i-1][k];
                    ancs[i][j] += ancs[i-1][k];
                    arrs[i][j] %= M;
                    ancs[i][j] %= M;
                }
            }
        }

        // for (int i = 0; i <= N; i++) System.out.println(Arrays.toString(ancs[i]));
        System.out.println("Ancestors on left: " + ancs[N][K]);

        currAnswer += ancs[N][K];
        currAnswer %= M;

        // Overcounting middle element
        // System.out.println("Array count: " + arrs[N][K]);
        int toReturn = currAnswer - arrs[N][K];
        if (toReturn < 0) toReturn += M;
        return toReturn;
    }

    int sumFrom1(int n) {
        return n * (n + 1) / 2;
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("treedepth.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("treedepth.out")));
        new treedepth(in, out);
        in.close();
        out.close();
    }
}
