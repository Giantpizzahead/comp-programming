/*
Solution: DP with matrix exponentiation.

Runtime: O(2^3 * log(N))
*/

import java.util.*;
import java.io.*;

public class tetraMatrixExp {
    int N;
    final int MOD = 1000000007;
    long[][] toMult = {
        {2, 1},
        {3, 0}
    };

    tetraMatrixExp() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        in.close();

        // The matrix to transfer is:
        // [ 2 1 ]
        // [ 3 0 ]
        long[][] currMat = {{0, 1}};
        while (N > 0) {
            if (N % 2 == 1) currMat = matrixMult(currMat, toMult);
            toMult = matrixMult(toMult, toMult);
            N /= 2;
        }
        System.out.println(currMat[0][1]);
    }

    // Multiplies the given matrices.
    long[][] matrixMult(long[][] a, long[][] b) {
        assert a[0].length == b.length;
        long[][] r = new long[a.length][b[0].length];
        for (int i = 0; i < r.length; i++) {
            for (int j = 0; j < r[0].length; j++) {
                for (int k = 0; k < b.length; k++) {
                    r[i][j] += a[i][k] * b[k][j];
                }
                r[i][j] %= MOD;
            }
        }
        return r;
    }

    public static void main(String[] args) throws IOException {
        new tetraMatrixExp();
    }
}