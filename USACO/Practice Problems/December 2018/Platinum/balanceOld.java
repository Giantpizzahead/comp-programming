/*
Solution: DP with math.
dp[i] = Optimal payment at position i (1-indexed)
i -> 0...N
BC: dp[0] = 0 (fall off)
dp[i] = max from j -> i...N of {(dp[i-1] * (j-i) + pay[j]) / (j-i+1)}
Answer: dp[1...N]

Runtime (without optimizations): O(N^2)
*/

import javax.crypto.EncryptedPrivateKeyInfo;
import java.util.*;
import java.io.*;

public class balance {
    int N;
    int[] pay;
    double[] dp;
    final double EPSILON = 0.00001;

    balance() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("balance.in"));
        N = Integer.parseInt(fin.readLine());
        pay = new int[N+2];
        for (int i = 1; i <= N; i++) {
            pay[i] = Integer.parseInt(fin.readLine());
        }
        pay[N+1] = 0;
        fin.close();

        doDP();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("balance.out")));
        for (int i = 1; i <= N; i++) {
            // System.out.println(dp[i]);
            double toPrint = dp[i] * 100000;
            if (toPrint % 1 < EPSILON || toPrint % 1 > 1 - EPSILON) toPrint = Math.round(toPrint);
            fout.println((long) toPrint);
        }
        fout.close();
    }

    double calcValue(int i, int j) {
        double newVal = ((j - i) * dp[i-1] + pay[j]) / (j - i + 1);
        if (newVal % 1 < EPSILON || newVal % 1 > 1 - EPSILON) newVal = Math.round(newVal);
        return newVal;
    }

    void doDP() {
        dp = new double[N+1];
        int[] bestFrom = new int[N+1];
        double bestSoFar;
        for (int i = 1; i <= N; i++) {
            // Optimization: No need to check if last one hasn't been reached yet
            if (bestFrom[i-1] > i) {
                dp[i] = calcValue(i, bestFrom[i-1]);
                bestFrom[i] = bestFrom[i-1];
                continue;
            }

            bestSoFar = -1;
            for (int j = i; j <= N + 1; j++) {
                double newVal = calcValue(i, j);
                if (newVal > bestSoFar) {
                    bestSoFar = newVal;
                    bestFrom[i] = j;
                }
            }
            dp[i] = bestSoFar;
        }
        // System.out.println(Arrays.toString(dp));
        // System.out.println(Arrays.toString(bestFrom));
    }

    public static void main(String[] args) throws IOException {
        new balance();
    }
}
