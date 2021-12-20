import java.util.*;
import java.io.*;

public class wanderingrobot {
    int W, H, L, U, R, D;

    wanderingrobot(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        W = Integer.parseInt(st.nextToken());
        H = Integer.parseInt(st.nextToken());
        L = Integer.parseInt(st.nextToken()) - 1;
        U = Integer.parseInt(st.nextToken()) - 1;
        R = Integer.parseInt(st.nextToken()) - 1;
        D = Integer.parseInt(st.nextToken()) - 1;

        double[][] dp = new double[H][W];
        dp[0][0] = 1;
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if (y == H - 1 && x == W - 1) continue;
                if (y >= U && y <= D && x >= L && x <= R) continue;
                if (y == H - 1) {
                    dp[y][x+1] += dp[y][x];
                } else if (x == W - 1) {
                    dp[y+1][x] += dp[y][x];
                } else {
                    dp[y + 1][x] += dp[y][x] / 2;
                    dp[y][x + 1] += dp[y][x] / 2;
                }
            }
        }

        for (int y = 0; y < H; y++) System.out.println(Arrays.toString(dp[y]));

        out.printf("Case #%d: %.6f\n", tn, dp[H-1][W-1]);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new wanderingrobot(in, out, i);
        in.close();
        out.close();
    }
}
