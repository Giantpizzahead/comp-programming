/*
Solution: First, generate a segment tree like structure. Then, do divide and conquer on the queries.
Runtime: O(NK^2 * log(N))
*/

import java.util.*;
import java.io.*;

public class nondec {
    int N, K, Q;
    int[] arr;
    final int MOD = 1000000007;

    nondec(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
        }

        if (N <= 2000) {
            // Do DP from every starting location
            // Runtime: O(N^2 * K)
            int[][] answers = new int[N][N];
            int[][] dp = new int[N + 1][K + 1];
            for (int i = 0; i < N; i++) {
                // System.out.println("now on " + i);
                Arrays.fill(dp[i], 0);
                dp[i][0] = 1;
                for (int j = i + 1; j <= N; j++) {
                    long answerSum = 0;
                    for (int k = 0; k <= K; k++) {
                        if (arr[j-1] != k) {
                            dp[j][k] = dp[j-1][k];
                        } else {
                            long sum = dp[j-1][k];
                            for (int l = 0; l <= k; l++) sum += dp[j-1][l];
                            dp[j][k] = (int) (sum % MOD);
                        }
                        answerSum += dp[j][k];
                    }
                    answers[i][j-1] = (int) (answerSum % MOD);
                    // System.out.println(Arrays.toString(dp[j]));
                }
            }
            // for (int i = 0; i < N; i++) System.out.println(Arrays.toString(answers[i]));

            // Answer queries using lookup table
            st = new StringTokenizer(in.readLine());
            Q = Integer.parseInt(st.nextToken());
            int l, r;
            for (int i = 0; i < Q; i++) {
                st = new StringTokenizer(in.readLine());
                l = Integer.parseInt(st.nextToken()) - 1;
                r = Integer.parseInt(st.nextToken()) - 1;
                out.println(answers[l][r]);
            }
        } else {
            // Generate segment-tree like structure
            SegmentTree segt = new SegmentTree(N);

            // Answer queries
            st = new StringTokenizer(in.readLine());
            Q = Integer.parseInt(st.nextToken());
            int l, r;
            for (int i = 0; i < Q; i++) {
                st = new StringTokenizer(in.readLine());
                l = Integer.parseInt(st.nextToken()) - 1;
                r = Integer.parseInt(st.nextToken()) - 1;
                out.println(segt.query(l, r));
            }
        }
    }

    long hash(int l, int r) {
        return (long) l * N + r;
    }

    class SegmentTree {
        int size;
        long[][][] vals;

        SegmentTree(int size) {
            this.size = size;
            vals = new long[size * 4 + 1][][];
            initTree(1, 0, size - 1);
        }

        /*
        Generates the transition array for all nodes in the tree.
        dp[i][j] = # of ways a NDS starting with i becomes a NDS ending with j in this section of
        the array.
         */
        void initTree(int n, int lb, int ub) {
            if (lb != ub) {
                initTree(n*2, lb, (lb+ub)/2);
                initTree(n*2+1, (lb+ub)/2+1, ub);
            }
            // Use the most efficient way to gen trans
            if ((ub - lb + 1) > K) {
                // Matrix multiplication is better
                vals[n] = multMatrices(vals[n*2], vals[n*2+1]);
            } else {
                // Generating trans is better
                vals[n] = findNDSTrans(lb, ub);
            }
        }

        long query(int l, int r) {
            result = new long[K + 1];
            result[0] = 1;
            query(1, 0, size - 1, l, r);
            // System.out.println(l + " " + r);
            // System.out.println(Arrays.toString(result));
            long sum = 0;
            for (long res : result) sum += res;
            return sum % MOD;
        }

        long[] result;
        void query(int n, int lb, int ub, int l, int r) {
            if (lb >= l && ub <= r) {
                // Contained in range; update result array
                for (int i = K; i >= 0; i--) {
                    long newRes = 0;
                    for (int j = 0; j <= i; j++) {
                        newRes = (newRes + result[j] * vals[n][j][i]) % MOD;
                    }
                    result[i] = newRes;
                }
            } else if (lb <= r && ub >= l) {
                query(n * 2, lb, (lb + ub) / 2, l, r);
                query(n * 2 + 1, (lb + ub) / 2 + 1, ub, l, r);
            }
        }
    }

    long[][] multMatrices(long[][] A, long[][] B) {
        long[][] R = new long[A.length][B[0].length];
        for (int i = 0; i < R.length; i++) {
            for (int j = 0; j < R[0].length; j++) {
                for (int k = 0; k < B.length; k++) {
                    R[i][j] = (R[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return R;
    }

    /*
    Complexity: O(NK^2)
     */
    long[][] findNDSTrans(int lb, int ub) {
        long[][] dp = new long[K+1][K+1];
        for (int i = 0; i <= K; i++) dp[i][i] = 1;
        // For each element in original array, add new transitions
        for (int i = lb; i <= ub; i++) {
            for (int j = 0; j <= arr[i]; j++) {
                long newVal = 0;
                for (int k = 0; k <= arr[i]; k++) {
                    newVal += dp[j][k];
                }
                dp[j][arr[i]] = (dp[j][arr[i]] + newVal) % MOD;
            }
        }
        // System.out.println(lb + " to " + ub);
        // for (int i = 0; i <= K; i++) System.out.println(Arrays.toString(dp[i]));
        return dp;
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("nondec.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("nondec.out")));
        new nondec(in, out);
        in.close();
        out.close();
    }
}
