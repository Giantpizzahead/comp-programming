package CodeStar;/*
Solution: DP.
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class paltitionsimpler {
    int N, M, X;
    String str;
    final int INF = 999999999;

    paltitionsimpler() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        X = Integer.parseInt(st.nextToken());
        str = in.readLine();
        in.close();

        // System.out.println(palin(1, 3));

        int answer = dp();
        if (answer == INF) System.out.println("NO");
        else {
            System.out.println("YES");
            System.out.println(answer);
        }
    }

    int dp() {
        int[][] dp = new int[N+1][M+1];
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= M; j++) {
                dp[i][j] = INF;
            }
        }
        dp[0][0] = 0;

        for (int i = 0; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                int newValue = INF;
                for (int k = 0; k < i; k++) {
                    int changesNeeded = palin(str.substring(k, i));
                    if (dp[k][j-1] + changesNeeded <= X) newValue = Math.min(dp[k][j-1] + changesNeeded, newValue);
                }
                dp[i][j] = newValue;
            }
        }

        // System.out.println(Arrays.deepToString(dp));

        return dp[N][M];
    }

    int palin(String str) {
        int answer = 0;
        for (int i = 0, j = str.length() - 1; i < str.length() / 2; i++, j--) {
            if (str.charAt(i) != str.charAt(j)) answer++;
        }
        return answer;
    }

    public static void main(String[] args) throws IOException {
        new paltitionsimpler();
    }
}
