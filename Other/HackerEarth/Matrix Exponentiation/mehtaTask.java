import java.io.*;
import java.util.*;

public class mehtaTask {
    int T, target;
    long N;
    long[][][] preExp;
    final int MAX_PRECOMP = 63;
    final long MOD = 1000000007;

    mehtaTask() throws IOException {
        // Precompute the matrices needed for matrix exponentiation
        preExp = new long[MAX_PRECOMP][][];
        preExp[0] = genFirst();
        for (int i = 1; i < MAX_PRECOMP; i++) {
            preExp[i] = multMatrices(preExp[i-1], preExp[i-1]);
        }

        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int i = 0; i < T; i++) {
            st = new StringTokenizer(in.readLine());
            N = Long.parseLong(st.nextToken());
            target = 0;
            for (int j = 0; j < 4; j++) {
                if (Integer.parseInt(st.nextToken()) == 1) target += 1 << j;
            }

            // Do matrix exponentiation
            long[][] result = new long[1][16];
            result[0][0] = 1;
            for (int j = MAX_PRECOMP - 1; j >= 0; j--) {
                if (N >= (1L << j)) {
                    result = multMatrices(result, preExp[j]);
                    N -= 1L << j;
                }
            }
            System.out.println(result[0][target]);
        }
        in.close();
    }

    long[][] multMatrices(long[][] A, long[][] B) {
        assert A[0].length == B.length;
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

    long[][] genFirst() {
        long[][] first = new long[16][16];
        // Try transitioning from all states (bitmask)
        for (int state = 0; state < 16; state++) {
            // Try adding each prime
            for (int i = 0; i < 4; i++) {
                first[state][state ^ (1 << i)]++;
            }
            // Add any other number
            first[state][state] += 6;
        }
        // for (int i = 0; i < 16; i++) System.out.println(Arrays.toString(first[i]));
        return first;
    }

    public static void main(String[] args) throws IOException {
        new mehtaTask();
    }
}
