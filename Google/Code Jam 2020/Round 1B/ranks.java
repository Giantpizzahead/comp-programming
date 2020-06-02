import java.util.*;
import java.io.*;

public class ranks {
    final int INF = 987654321;
    int R, S;

    ranks(BufferedReader in, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        R = Integer.parseInt(st.nextToken());
        S = Integer.parseInt(st.nextToken());
        dp = new int[R + 1];
        bestDP = new int[R + 1];
        Arrays.fill(dp, INF);
        dp[1] = 0;
        int answer = solve(R);
        // System.out.println(Arrays.toString(dp));

        System.out.println("Case #" + tn + ": " + answer);
        // Generate moves
        trace(R, 0);
    }

    void trace(int r, int offset) {
        if (r == 1) return;
        // Split up into left and right sides
        for (int i = 1; i < S; i++) {
            printPair(offset + r * i, bestDP[r]);
        }
        // Sort left side first
        trace(bestDP[r], offset);
    }

    void printPair(int a, int b) {
        System.out.println(a + " " + b);
    }

    int[] dp;
    int[] bestDP;
    int solve(int r) {
        if (dp[r] != INF) return dp[r];
        for (int i = 1; i < r; i++) {
            int newCost = solve(i) + solve(r-i) + S - 1;
            if (i != r - 1) newCost++;
            if (newCost < dp[r]) {
                dp[r] = newCost;
                bestDP[r] = i;
            }
        }
        return dp[r];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new ranks(in, i);
        in.close();
    }
}
