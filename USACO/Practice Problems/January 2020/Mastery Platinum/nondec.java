import java.util.*;
import java.io.*;

public class nondec {
    final int MOD = 1000000007;
    int N, K, Q;
    int[] arr;
    int[][][] baseMats, baseInvMats;
    int[][][] pre, preInv;

    nondec(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());

        /*
        int[][] A = new int[][] {
                {1, 500000003, 0},
                {0, 500000004, 0},
                {0, 0, 1}
        };
        int[][] B = new int[][] {
                {2, 8, 4},
                {0, 4, 8},
                {0, 0, 2}
        };
        int[][] C = multInverse(A, B, 1);
        printMatrix(C);
         */

        // Generate base matrices
        baseMats = new int[K + 1][K + 1][K + 1];
        baseInvMats = new int[K + 1][K + 1][K + 1];
        for (int n = 1; n <= K; n++) {
            for (int i = 0; i <= K; i++) {
                baseMats[n][i][i] = 1;
                baseInvMats[n][i][i] = 1;
            }
            // Generate special column
            for (int i = 0; i < n; i++) {
                baseMats[n][i][n] = 1;
                baseInvMats[n][i][n] = 500000003;  // 1/2 mod 10^9+7...?
            }
            baseMats[n][n][n] = 2;
            baseInvMats[n][n][n] = 500000004;  // -1/2 mod 10^9+7...?
        }

        // Now, generate prefix matrices
        pre = new int[N][][];
        preInv = new int[N][][];
        // Base matrix (copy of base matrix)
        pre[0] = new int[K + 1][K + 1];
        preInv[0] = new int[K + 1][K + 1];
        int val = arr[0];
        for (int i = 0; i <= K; i++) {
            for (int j = 0; j <= K; j++) {
                pre[0][i][j] = baseMats[val][i][j];
                preInv[0][i][j] = baseInvMats[val][i][j];
            }
        }
//        System.out.println("pre[0]");
//        printMatrix(pre[0]);
//        System.out.println("preInv[0]");
//        printMatrix(preInv[0]);
        // Generate next pre / preInv using smart matrix multiplication
        for (int i = 1; i < N; i++) {
            pre[i] = multForward(pre[i-1], baseMats[arr[i]], arr[i]);
            preInv[i] = multInverse(baseInvMats[arr[i]], preInv[i-1], arr[i]);
//            System.out.println("pre[" + i + "]");
//            printMatrix(pre[i]);
//            System.out.println("preInv[" + i + "]");
//            printMatrix(preInv[i]);
        }

//        for (int i = 0; i < N; i++) {
//            int[] result = new int[K + 1];
//            result[0] = 1;
//            result = multAnswer(result, preInv[i]);
//            result = multAnswer(result, pre[i]);
//            System.out.println(Arrays.toString(result));
//        }

        Q = Integer.parseInt(in.readLine());
        int l, r;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            l = Integer.parseInt(st.nextToken()) - 1;
            r = Integer.parseInt(st.nextToken()) - 1;
            int[] result = new int[K + 1];
            result[0] = 1;
            if (l != 0) result = multAnswer(result, preInv[l-1]);
            result = multAnswer(result, pre[r]);
            int sum = 0;
            for (int j = 0; j <= K; j++) sum = (sum + result[j]) % MOD;
            out.println(sum);

//            System.out.println("Query " + l + " " + r + " = " + Arrays.toString(result));
        }
    }

    int[] multAnswer(int[] A, int[][] B) {
        int[] R = new int[K + 1];
        for (int i = 0; i <= K; i++) {
            long result = 0;
            for (int j = 0; j <= K; j++) {
                result += (long) A[j] * B[j][i];
                result %= MOD;
            }
            R[i] = (int) result;
        }
        return R;
    }

    void printMatrix(int[][] M) {
        for (int i = 0; i <= K; i++) System.out.println(Arrays.toString(M[i]));
    }

    int[][] multForward(int[][] A, int[][] B, int col) {
        int[][] R = new int[K + 1][K + 1];
        // Fill all that aren't in changed column
        for (int i = 0; i <= K; i++) {
            for (int j = 0; j <= K; j++) {
                if (j == col) continue;
                R[i][j] = A[i][j];
            }
        }
        // Generate changed column
        for (int i = 0; i <= K; i++) {
            long result = 0;
            for (int j = 0; j <= K; j++) {
                result += (long) A[i][j] * B[j][col] % MOD;
                result %= MOD;
            }
            R[i][col] = (int) result;
        }
        return R;
    }

    int[][] multInverse(int[][] A, int[][] B, int col) {
        int[][] R = new int[K + 1][K + 1];
        // Fill all except changed row
        for (int i = 0; i <= K; i++) {
            if (i == col) continue;
            for (int j = 0; j <= K; j++) {
                R[i][j] = B[i][j];
            }
        }
        // Factor transitions in for only the changed column
        for (int i = 0; i <= K; i++) {
            for (int j = 0; j <= K; j++) {
                R[i][j] = (int) ((R[i][j] + (long) A[i][col] * B[col][j]) % MOD);
            }
        }
        return R;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("nondec.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("nondec.out")));
        new nondec(in, out);
        in.close();
        out.close();
    }
}
