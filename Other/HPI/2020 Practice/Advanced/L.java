import java.util.Scanner;

public class L {
    int N, A, B;
    int[] dp;
    final int MOD = 1000000007;

    L() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt() * 2;
        A = sc.nextInt();
        B = sc.nextInt();
        dp = new int[N + 1];
        dp[0] = 1;
        for (int i = 2; i <= N; i += 2) {
            for (int j = 0; j < i; j += 2) {
                int newWays = (int) ((long) dp[j] * dp[i-2-j] % MOD);
                dp[i] = (dp[i] + newWays) % MOD;
            }
        }

        int transRight = B - A - 1;
        int overCount = (int) ((long) dp[transRight] * dp[N-2-transRight] % MOD);
        int answer = dp[N] - overCount;
        if (answer < 0) answer += MOD;
        System.out.println(answer);
    }

    public static void main(String[] args) {
        new L();
    }
}
