/*
Solution: Use a window to test each location. A series of decisions can be categorized by how far Bessie
is willing to go left and right, so test every possible left / right pair at each point.

Runtime: O(N^3) - If this doesn't work (all TLE, no incorrect), then I have no clue what to do.
*/

import java.util.*;
import java.io.*;

public class balanceWindow {
    int N;
    long[] pay;
    int[] bestLeft, bestRight;
    long[] bestPay;
    final double EPSILON = 0.0000001;

    balanceWindow() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("balance.in"));
        N = Integer.parseInt(fin.readLine());
        pay = new long[N+2];
        for (int i = 1; i <= N; i++) pay[i] = Integer.parseInt(fin.readLine()) * 100000L;
        fin.close();

        bestPay = new long[N+2];
        bestLeft = new int[N+2];
        bestRight = new int[N+2];
        for (int i = 1; i <= N; i++) {
            // Optimization: If bestRight has not been passed, it'll be the same
            if (bestRight[i-1] >= i) {
                bestLeft[i] = bestLeft[i-1];
                bestRight[i] = bestRight[i-1];
                bestPay[i] = calcCost(bestLeft[i-1], bestRight[i-1], i);
            } else {
                check(i);
            }
        }
        /*
        System.out.println(Arrays.toString(bestPay));
        System.out.println(Arrays.toString(bestLeft));
        System.out.println(Arrays.toString(bestRight));
        */
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("balance.out")));
        for (int i = 1; i <= N; i++) {
            fout.println(bestPay[i]);
        }
        fout.close();
    }

    long calcCost(int lb, int rb, int i) {
        long numerator = pay[lb] * (rb - i) + pay[rb] * (i - lb);
        long newPay = numerator / (rb - lb);
        return newPay;
    }

    void check(int i) {
        // Optimization: Left bound is always previous right bound
        long bestSoFar = pay[i];
        int bestLB = i;
        int bestRB = i;
        for (int rb = N + 1; rb > i; rb--) {
            long newPay = calcCost(bestRight[i-1], rb, i);
            if (newPay > bestSoFar) {
                bestSoFar = newPay;
                bestLB = bestRight[i-1];
                bestRB = rb;
            }
        }
        bestPay[i] = bestSoFar;
        bestLeft[i] = bestLB;
        bestRight[i] = bestRB;
    }

    public static void main(String[] args) throws IOException {
        new balanceWindow();
    }
}
