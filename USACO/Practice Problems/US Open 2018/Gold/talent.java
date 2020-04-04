/*
Solution: DP. dp[i][j] = Max talent possible with weight j, from cows 0...i.
i is from 0 to N-1, j is from 0 to W-1. Make sure to sort the cows by talent to weight ratio
first.

BC: dp[0][0...W-1] = -INF, dp[0][w[i]] = t[i]
Trans:
dp[i][j] = max(dp[i-1][j-w[i]] + t[i], dp[i-1][j])

Answer: After each row of the DP (after each cow), iterate from k = j-w[i]...W-1.
answer = max((dp[i-1][k] + t[i]) / (k + w[i]))
*/

import java.util.*;
import java.io.*;

public class talent {
    int N, W;
    Cow[] cows;
    final int INF = 999999999;

    talent() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        W = Integer.parseInt(st.nextToken());
        cows = new Cow[N];
        int w, t;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            w = Integer.parseInt(st.nextToken());
            t = Integer.parseInt(st.nextToken());
            cows[i] = new Cow(w, t);
        }
        fin.close();

        // Sort cows by talent to weight ratio (decreasing), breaking ties by lowest weight
        Arrays.sort(cows, new Comparator<Cow>() {
            @Override
            public int compare(Cow a, Cow b) {
                double result = ((double) b.t / b.w) - ((double) a.t / a.w);
                if (result != 0) return (result > 0) ? 1 : -1;
                else return a.w - b.w;
            }
        });

        // System.out.println(Arrays.toString(cows));

        int answer = doDP();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("talent.out")));
        fout.println(answer);
        fout.close();
    }

    int doDP() {
        int[][] dp = new int[N][W];
        for (int j = 0; j < W; j++) dp[0][j] = -INF;
        int answer = 0;
        dp[0][0] = 0;
        if (cows[0].w < W) dp[0][cows[0].w] = cows[0].t;
        else answer = calcAnswer(cows[0].t, cows[0].w);

        for (int i = 1; i < N; i++) {
            for (int j = 0; j < W; j++) {
                int newDP = dp[i-1][j];
                if (j-cows[i].w >= 0) newDP = Math.max(dp[i-1][j-cows[i].w] + cows[i].t, newDP);
                dp[i][j] = (newDP < 0) ? -INF : newDP;
            }

            // Update the answer
            for (int j = Math.max(W - cows[i].w, 0); j < W; j++) {
                //(dp[i-1][k] + t[i]) / (k + w[i])
                if (dp[i-1][j] == -INF) continue;
                answer = Math.max(calcAnswer(dp[i-1][j] + cows[i].t, j + cows[i].w), answer);
                // System.out.println(answer + " " + (dp[i-1][j] + cows[i].t) + " " + (j + cows[i].w));
            }
        }

        return answer;
    }

    int calcAnswer(int talent, int weight) {
        return (int) ((double) (talent * 1000) / weight);
    }

    public static void main(String[] args) throws IOException {
        new talent();
    }

    static class Cow {
        int w, t;
        Cow(int w, int t) {
            this.w = w;
            this.t = t;
        }

        @Override
        public String toString() {
            return "(" + w + ", " + t + ")";
        }
    }
}
