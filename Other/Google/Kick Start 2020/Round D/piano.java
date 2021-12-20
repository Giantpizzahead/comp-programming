import java.io.*;
import java.util.StringTokenizer;

public class piano {
    int K;
    int[] arr;
    // dp[i][j] = Min # of rules broken on key i, last key j
    int[][] dp;

    piano(BufferedReader in, PrintWriter out, int tn) throws IOException {
        K = Integer.parseInt(in.readLine());
        int currMax = -1;
        arr = new int[K];
        StringTokenizer st = new StringTokenizer(in.readLine());
        for (int i = 0; i < K; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
        }

        dp = new int[K][4];
        for (int i = 1; i < K; i++) {
            int lastMin = 9999999;
            for (int j = 0; j < 4; j++) lastMin = Math.min(dp[i-1][j] + 1, lastMin);
            if (arr[i] > arr[i-1]) {
                for (int j = 0; j < 4; j++) {
                    dp[i][j] = lastMin;
                    lastMin = Math.min(dp[i-1][j], lastMin);
                }
            } else if (arr[i] < arr[i-1]) {
                for (int j = 3; j >= 0; j--) {
                    dp[i][j] = lastMin;
                    lastMin = Math.min(dp[i-1][j], lastMin);
                }
            } else {
                for (int j = 0; j < 4; j++) {
                    dp[i][j] = Math.min(dp[i-1][j], lastMin);
                }
            }
        }

        int answer = 9999999;
        for (int j = 0; j < 4; j++) answer = Math.min(dp[K-1][j], answer);
        out.printf("Case #%d: %d\n", tn, answer);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int t = Integer.parseInt(in.readLine());
        for (int i = 1; i <= t; i++) new piano(in, out, i);
        in.close();
        out.close();
    }
}
