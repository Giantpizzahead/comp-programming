import java.util.*;
import java.io.*;

public class longWalks {
    int T, N, office, house;
    long[][] matrixExp;
    long K;
    final long MOD = 1000000007;

    longWalks() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int i = 0; i < T; i++) {
            st = new StringTokenizer(in.readLine());
            N = Integer.parseInt(st.nextToken());
            K = Long.parseLong(st.nextToken());
            office = Integer.parseInt(st.nextToken());
            house = Integer.parseInt(st.nextToken());
            matrixExp = new long[N][N];
            for (int j = 0; j < N; j++) {
                String line = in.readLine();
                for (int k = 0; k < N; k++) matrixExp[j][k] = (line.charAt(k*2) == '1') ? 1 : 0;
            }

            // Do matrix exponentiation
            long[][] result = new long[1][N];
            result[0][office] = 1;
            while (K > 0) {
                if (K % 2 == 1) result = multMatrices(result, matrixExp);
                K /= 2;
                matrixExp = multMatrices(matrixExp, matrixExp);
            }

            System.out.println(result[0][house]);
        }
        in.close();
    }

    long[][] multMatrices(long[][] A, long[][] B) {
        long[][] R = new long[A.length][B[0].length];
        for (int i = 0; i < R.length; i++) {
            for (int j = 0; j < R[0].length; j++) {
                for (int k = 0; k < B.length; k++) {
                    R[i][j] += A[i][k] * B[k][j];
                    R[i][j] %= MOD;
                }
            }
        }
        return R;
    }

    public static void main(String[] args) throws IOException {
        new longWalks();
    }
}
