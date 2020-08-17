/*
Solution: Matrix exponentiation! :)
Runtime: O(M^3 * log(N))
*/

import java.util.*;
import java.io.*;

public class genome {
    long N;
    int M, K;
    int[][] trans;
    final int MOD = 1000000007;

    genome(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Long.parseLong(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        trans = new int[M][M];
        for (int i = 0; i < M; i++) Arrays.fill(trans[i], 1);
        for (int i = 0; i < K; i++) {
            String str = in.readLine();
            int a = convToInt(str.charAt(0));
            int b = convToInt(str.charAt(1));
            trans[a][b] = 0;
        }
        // for (int i = 0; i < M; i++) System.out.println(Arrays.toString(trans[i]));

        int[][] answer = new int[1][M];
        for (int i = 0; i < M; i++) answer[0][i] = 1;
        long lengthToGo = N - 1;
        for (int tv = 1; lengthToGo > 0; tv *= 2) {
            if (lengthToGo % 2 == 1) {
                answer = multMatrices(answer, trans);
            }
            lengthToGo /= 2;
            trans = multMatrices(trans, trans);
        }

        int sum = 0;
        for (int i = 0; i < M; i++) sum = (sum + answer[0][i]) % MOD;
        out.println(sum);
    }

    int[][] multMatrices(int[][] A, int[][] B) {
        int[][] R = new int[A.length][B[0].length];
        for (int i = 0; i < R.length; i++) {
            for (int j = 0; j < R[0].length; j++) {
                for (int k = 0; k < B.length; k++) {
                    R[i][j] += ((long) A[i][k] * B[k][j]) % MOD;
                    R[i][j] %= MOD;
                }
            }
        }
        return R;
    }

    int convToInt(char c) {
        if (c >= 'a' && c <= 'z') return c - 'a';
        else return c - 'A' + 26;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new genome(in, out);
        in.close();
        out.close();
    }
}
