package CodeStar;/*
Solution: Modified Knapsack / DP.
*/

import java.util.*;
import java.io.*;

public class pineappleprune {
    int P, piCost, prCost, piQuantity, prQuantity;
    int[] piSatis, prSatis;
    final int INF = 1000000005;

    pineappleprune() throws IOException {
        Scanner s = new Scanner(System.in);
        P = s.nextInt();
        piCost = s.nextInt();
        prCost = s.nextInt();
        piQuantity = s.nextInt();
        prQuantity = s.nextInt();

        piSatis = new int[piQuantity];
        for (int i = 0; i < piQuantity; i++) {
            piSatis[i] = s.nextInt();
        }

        prSatis = new int[prQuantity];
        for (int i = 0; i < prQuantity; i++) {
            prSatis[i] = s.nextInt();
        }
        s.close();

        // System.out.println(calcNumPrunes(20, 10));
        int answer = doKnapsack();
        System.out.println(answer);
    }

    int doKnapsack() {
        int[][] dp = new int[P+1][piQuantity + 1];
        for (int i = 0; i <= P; i++) {
            for (int j = 0; j <= piQuantity; j++) {
                dp[i][j] = -INF;
            }
        }
        dp[0][0] = 0;
        int answer = 0;
        int bestNew;
        for (int i = 1; i <= P; i++) {
            for (int j = 0; j <= piQuantity; j++) {
                bestNew = -INF;
                // Buy pineapple
                if (i - piCost >= 0 && j != 0) {
                    // System.out.println(dp[i-piCost][j-1]);
                    bestNew = dp[i-piCost][j-1] + piSatis[j-1];
                }
                // Buy prune
                if (i - prCost >= 0) {
                    // Make sure # of prunes works
                    int numPrunes = calcNumPrunes(i - prCost, j);
                    if (numPrunes >= 0 && numPrunes < prQuantity) {
                        bestNew = Math.max(dp[i-prCost][j] + prSatis[numPrunes], bestNew);
                    }
                }
                // System.out.println("dp" + i + " " + j + " = " + bestNew);
                dp[i][j] = bestNew;
                answer = Math.max(dp[i][j], answer);
            }
        }

        return answer;
    }

    int calcNumPrunes(int c, int j) {
        double result = (c - j * piCost) / (float) prCost;
        if (result < -0.000000001 || result % 1 > 0.000000001) return -1;
        else return (c - j * piCost) / prCost;
    }

    public static void main(String[] args) throws IOException {
        new pineappleprune();
    }
}
