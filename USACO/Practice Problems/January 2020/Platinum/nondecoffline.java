/*
To save memory, handle the queries offline by sorting them in order of L.
 */

import java.io.*;
import java.util.*;

public class nondecoffline {
    final int MOD = 1000000007;
    int N, K, Q;
    int[] arr;
    int[][][] currPreInv;
    int[][][] baseMats, baseInvMats;
    int[][][] pre;
    LinkedList<Query>[] queries;

    nondecoffline(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());

        queries = new LinkedList[N];
        for (int i = 0; i < N; i++) queries[i] = new LinkedList<>();
        Q = Integer.parseInt(in.readLine());
        int l, r;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            l = Integer.parseInt(st.nextToken()) - 1;
            r = Integer.parseInt(st.nextToken()) - 1;
            queries[l].add(new Query(r, i));
        }

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
        pre = new int[N][K + 1][K + 1];
        currPreInv = new int[2][K + 1][K + 1];
        int currInvI = 0;
        // Base matrix (copy of base matrix)
        pre[0] = new int[K + 1][K + 1];
        int val = arr[0];
        for (int i = 0; i <= K; i++) {
            for (int j = 0; j <= K; j++) {
                pre[0][i][j] = baseMats[val][i][j];
                currPreInv[0][i][j] = baseInvMats[val][i][j];
            }
        }
        // Generate next pre using smart matrix multiplication
        for (int i = 1; i < N; i++) pre[i] = multForward(pre[i-1], baseMats[arr[i]], arr[i]);

        // Generate rolling preInv, handling queries as you go
        // Handle all L=0 queries first
        int[] queryAnswers = new int[Q];
        int[][] result = new int[3][K + 1];
        for (Query q : queries[0]) {
            Arrays.fill(result[0], 0);
            result[0][0] = 1;
            multAnswer(result[0], pre[q.r], result[1]);
            int sum = 0;
            for (int j = 0; j <= K; j++) sum = (sum + result[1][j]) % MOD;
            queryAnswers[q.i] = sum;
        }
        for (int i = 1; i < N; i++) {
            if (queries[i].size() != 0) {
                Arrays.fill(result[0], 0);
                result[0][0] = 1;
                multAnswer(result[0], currPreInv[currInvI], result[1]);
                for (Query q : queries[i]) {
                    multAnswer(result[1], pre[q.r], result[2]);
                    int sum = 0;
                    for (int j = 0; j <= K; j++) sum = (sum + result[2][j]) % MOD;
                    queryAnswers[q.i] = sum;
                }
            }
            multInverse(baseInvMats[arr[i]], currPreInv[currInvI], currPreInv[1-currInvI], arr[i]);
            currInvI = 1 - currInvI;
        }

        // Print out answers
        Arrays.stream(queryAnswers).forEach(out::println);
    }

    class Query {
        int r, i;
        Query(int r, int i) {
            this.r = r;
            this.i = i;
        }
    }

    void multAnswer(int[] A, int[][] B, int[] R) {
        for (int i = 0; i <= K; i++) {
            long result = 0;
            for (int j = 0; j <= K; j++) {
                result = (result + (long) A[j] * B[j][i]) % MOD;
            }
            R[i] = (int) result;
        }
    }

    void printMatrix(int[][] M) {
        for (int i = 0; i <= K; i++) System.out.println(Arrays.toString(M[i]));
    }

    int[][] multForward(int[][] A, int[][] B, int col) {
        int[][] R = new int[K + 1][K + 1];
        // Fill all that aren't in changed column
        for (int i = 0; i <= K; i++) {
            for (int j = 0; j <= K; j++) {
                R[i][j] = A[i][j];
            }
        }
        for (int i = 0; i <= K; i++) R[i][col] = 0;
        // Generate changed column
        for (int i = 0; i <= K; i++) {
            long result = 0;
            for (int j = 0; j <= K; j++) {
                result = (result + (long) A[i][j] * B[j][col]) % MOD;
            }
            R[i][col] = (int) result;
        }
        return R;
    }

    void multInverse(int[][] A, int[][] B, int[][] R, int col) {
        // Fill all except changed row
        for (int i = 0; i <= K; i++) {
            for (int j = 0; j <= K; j++) {
                R[i][j] = B[i][j];
            }
        }
        Arrays.fill(R[col], 0);
        // Factor transitions in for only the changed column
        for (int i = 0; i <= K; i++) {
            for (int j = 0; j <= K; j++) {
                R[i][j] = (int) ((R[i][j] + (long) A[i][col] * B[col][j]) % MOD);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("nondec.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("nondec.out")));
        new nondecoffline(in, out);
        in.close();
        out.close();
    }
}
