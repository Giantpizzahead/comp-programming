import java.util.*;
import java.io.*;

public class abcdStrings {
    int T, K, numStates;
    long N;
    long[][] transMatrix;
    HashSet<String> restricted;
    final long MOD = 1000000007;

    abcdStrings() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int i = 0; i < T; i++) {
            st = new StringTokenizer(in.readLine());
            N = Long.parseLong(st.nextToken());
            K = Integer.parseInt(st.nextToken());
            restricted = new HashSet<>(K, 1);
            for (int j = 0; j < K; j++) {
                restricted.add(in.readLine());
            }
            System.out.println(solve());
        }
        in.close();
    }

    long solve() {
        if (N < 1) return 0;
        // If N < 3, just generate all possible combos and return that (special cases)
        if (N < 3) {
            int num = 0;
            for (char c1 = 'a'; c1 <= 'd'; c1++) {
                if (restricted.contains("" + c1)) continue;
                if (N == 1) num += restricted.contains("" + c1) ? 0 : 1;
                else {
                    for (char c2 = 'a'; c2 <= 'd'; c2++) {
                        if (restricted.contains("" + c2)) continue;
                        num += restricted.contains("" + c1 + c2) ? 0 : 1;
                    }
                }
            }
            return num;
        }

        // Generate transition matrix
        genTransMatrix();
        // Setup result matrix
        long[][] result = new long[1][numStates];
        for (char c1 = 'a'; c1 <= 'd'; c1++) {
            if (restricted.contains("" + c1)) continue;
            for (char c2 = 'a'; c2 <= 'd'; c2++) {
                if (restricted.contains("" + c2) || restricted.contains("" + c1 + c2)) continue;
                result[0][state(c1, c2)] = 1;
            }
        }
        N -= 2;
        // Do matrix exponentiation
        while (N > 0) {
            if (N % 2 == 1) result = multMatrices(result, transMatrix);
            N /= 2;
            transMatrix = multMatrices(transMatrix, transMatrix);
        }

        long sum = 0;
        for (long l : result[0]) sum += l;
        return sum % MOD;
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

    void genTransMatrix() {
        numStates = 16;
        transMatrix = new long[numStates][numStates];
        // Try transitioning from all states (last 2 characters)
        for (char c1 = 'a'; c1 <= 'd'; c1++) {
            if (restricted.contains("" + c1)) continue;
            for (char c2 = 'a'; c2 <= 'd'; c2++) {
                if (restricted.contains("" + c2) || restricted.contains("" + c1 + c2)) continue;
                for (char c3 = 'a'; c3 <= 'd'; c3++) {
                    if (restricted.contains("" + c3) || restricted.contains("" + c2 + c3) || restricted.contains("" + c1 + c2 + c3)) continue;
                    // Valid set of characters; record it
                    transMatrix[state(c1, c2)][state(c2, c3)]++;
                }
            }
        }

        // for (int i = 0; i < numStates; i++) System.out.println(Arrays.toString(transMatrix[i]));
    }

    int state(char c1, char c2) {
        return (c1 - 'a') * 4 + c2 - 'a';
    }

    public static void main(String[] args) throws IOException {
        new abcdStrings();
    }
}
