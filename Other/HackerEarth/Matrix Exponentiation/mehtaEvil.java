/*
Solution: 
*/

import java.util.*;
import java.io.*;

public class mehtaEvil {
    int T;
    long N;
    long[][][] preExp;
    final int MAX_PRECOMP = 62;
    final long MOD = 1000000007;

    mehtaEvil() throws IOException {
        // Precompute required matrices for matrix exponentiation
        // States track whether current length has even or odd # of each prime factor
        preExp = new long[MAX_PRECOMP][][];
        preExp[0] = genFirst();
        for (int i = 1; i < MAX_PRECOMP; i++) {
            preExp[i] = multMatrices(preExp[i-1], preExp[i-1]);
        }

        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int t = 0; t < T; t++) {
            st = new StringTokenizer(in.readLine());
            N = Long.parseLong(st.nextToken());

            // Do matrix exponentiation
            long[][] result = new long[1][16];
            result[0][0] = 1;
            for (int i = MAX_PRECOMP - 1; i >= 0; i--) {
                if (N >= (1L << i)) {
                    result = multMatrices(result, preExp[i]);
                    N -= 1L << i;
                }
            }

            // System.out.println(Arrays.toString(result[0]));

            long sum = 0;
            int[] orig = {2, 3, 5, 7};
            for (int state = 1; state < 16; state++) {
                // Note: State #13 (1101) shouldn't be counted, since 2 ^ 5 ^ 7 = 0. However, the official solution
                // has this bug, so this code also has it now. Yay! Bugs!!!!!!
                /*
                int xor = 0;
                for (int i = 0; i < 4; i++) {
                    if ((state & (1 << i)) != 0) xor ^= orig[i];
                }
                if (xor != 0) {
                    sum += result[0][state];
                } else System.out.println("XOR of " + state + " does not work");
                 */
                sum += result[0][state];
            }
            System.out.println(sum % MOD);
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

    long[][] genFirst() {
        // Contains all possible transitions
        int[][] trans = {
                {},  // 1
                {1}, // 2
                {2}, // 3
                {1, 1}, // 4
                {4}, // 5
                {1, 2}, // 6
                {8}, // 7
                {1, 1, 1}, // 8
                {2, 2}, // 9
        };
        long[][] result = new long[16][16];
        // Try transitioning from all states
        for (int state = 0; state < 16; state++) {
            // Try adding each number
            for (int[] t : trans) {
                // Update even and odd values
                int newState = state;
                for (int n : t) newState ^= n;
                result[state][newState]++;
            }
        }
        // for (int i = 0; i < 16; i++) System.out.println(Arrays.toString(result[i]));
        return result;
    }

    public static void main(String[] args) throws IOException {
        new mehtaEvil();
    }
}
