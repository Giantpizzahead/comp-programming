import java.util.*;
import java.io.*;

public class plates {
    int N, K, P;
    int[][] platesPre;

    plates(BufferedReader in, PrintWriter out, int t) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        P = Integer.parseInt(st.nextToken());
        platesPre = new int[N][K + 1];
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            int currPre = 0;
            for (int j = 1; j <= K; j++) {
                currPre += Integer.parseInt(st.nextToken());
                platesPre[i][j] = currPre;
            }
        }

        int[][] dp = new int[N][P + 1];
        for (int j = 0; j <= P; j++) {
            if (j <= K) dp[0][j] = platesPre[0][j];
            else dp[0][j] = dp[0][j-1];
        }
        for (int i = 1; i < N; i++) {
            for (int j = 1; j <= P; j++) {
                for (int k = 0; k <= K; k++) {
                    if (j-k < 0) break;
                    dp[i][j] = Math.max(dp[i-1][j-k] + platesPre[i][k], dp[i][j]);
                }
                dp[i][j] = Math.max(dp[i][j-1], dp[i][j]);
            }
        }
        out.println("Case #" + (t+1) + ": " + dp[N-1][P]);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new plates(in, out, i);
        in.close();
        out.close();
    }
}
