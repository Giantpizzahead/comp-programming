/*
ID: sunnyky1
LANG: JAVA
TASK: game1

Solution: dp[l][r] = Pair representing max scores for both players.
if ((r-l+1) % 2 == N % 2) {
    Player 1's turn
    dp[l][r] = max player 1 score: (dp[l+1][r] + arr[l], dp[l][r-1] + arr[r])
} else {
    Player 2's turn (mirror player 1 dp)
}
Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

public class game1 {
    int N;
    int[] arr;

    game1(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        arr = new int[N];
        String line = in.readLine();
        int ci = 0;
        while (line != null) {
            st = new StringTokenizer(line);
            while (st.hasMoreTokens()) {
                arr[ci++] = Integer.parseInt(st.nextToken());
            }
            line = in.readLine();
        }

        Pair[][] dp = new Pair[N][N];
        for (int i = 0; i < N; i++) {
            if (N % 2 == 0) {
                // Player 2 moves last
                dp[i][i] = new Pair(0, arr[i]);
            } else {
                // Player 1 moves last
                dp[i][i] = new Pair(arr[i], 0);
            }
        }
        for (int size = 1; size < N; size++) {
            for (int l = 0, r = size; r < N; l++, r++) {
                Pair bestTrans;
                if (size % 2 != N % 2) {
                    // Player 1's turn
                    bestTrans = new Pair(dp[l+1][r].p1 + arr[l], dp[l+1][r].p2);
                    Pair trans = new Pair(dp[l][r-1].p1 + arr[r], dp[l][r-1].p2);
                    if (trans.p1 > bestTrans.p1) bestTrans = trans;
                } else {
                    // Player 2's turn
                    bestTrans = new Pair(dp[l+1][r].p1, dp[l+1][r].p2 + arr[l]);
                    Pair trans = new Pair(dp[l][r-1].p1, dp[l][r-1].p2 + arr[r]);
                    if (trans.p2 > bestTrans.p2) bestTrans = trans;
                }
                dp[l][r] = bestTrans;
            }
        }
        out.printf("%d %d\n", dp[0][N-1].p1, dp[0][N-1].p2);
    }

    class Pair {
        int p1, p2;
        Pair(int p1, int p2) {
            this.p1 = p1;
            this.p2 = p2;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("game1.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("game1.out")));
        new game1(in, out);
        in.close();
        out.close();
    }
}
