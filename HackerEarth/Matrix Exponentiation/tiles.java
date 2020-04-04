import java.util.*;
import java.io.*;

public class tiles {
    int T, M, N;
    long[][] matrixExp;
    final long MOD = 1000000007;

    tiles() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int i = 0; i < T; i++) {
            st = new StringTokenizer(in.readLine());
            M = Integer.parseInt(st.nextToken());
            N = Integer.parseInt(st.nextToken());
            // First, figure out the matrix to use for exponentiation
            findExpMatrix();
            // Now, calculate the answer using matrix exponentiation
            System.out.println(calcAnswer());
        }
        in.close();
    }

    long calcAnswer() {
        long[][] result = new long[1][1 << M];
        result[0][0] = 1;
        while (N > 0) {
            if (N % 2 == 1) result = multMatrices(result, matrixExp);
            N /= 2;
            matrixExp = multMatrices(matrixExp, matrixExp);
        }

        // System.out.println(Arrays.toString(result[0]));

        return result[0][0];
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

    void findExpMatrix() {
        matrixExp = new long[1 << M][1 << M];
        // Generate all bitmask states
        // State represents the cells that are filled with rectangles already in the current row
        for (int curr = 0; curr < (1 << M); curr++) {
            // Find all transitions / add to matrixExp using a DFS
            findTransitions(0, 0, curr);
        }

//        for (int i = 0; i < 1 << M; i++) {
//            System.out.println(Arrays.toString(matrixExp[i]));
//        }
    }

    void findTransitions(int state, int i, int startState) {
        if (i == M) {
            // Reached end; add state to matrix
            matrixExp[startState][state]++;
            return;
        } else if ((startState & 1 << i) == 0) {
            // Current row doesn't have any rectangles yet
            // Try adding a vertical rectangle if bottom is also empty
            if (i != M - 1 && ((startState & 1 << (i + 1)) == 0)) {
                findTransitions(state, i+2, startState);
            }
            // Try adding a horizontal rectangle
            state += 1 << i;
            findTransitions(state, i+1, startState);
            state -= 1 << i;
        }
        // Try not putting a rectangle
        findTransitions(state, i+1, startState);
    }

    public static void main(String[] args) throws IOException {
        new tiles();
    }
}
