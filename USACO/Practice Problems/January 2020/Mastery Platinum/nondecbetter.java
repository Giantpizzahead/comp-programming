import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class nondecbetter {
    final int MOD = 1000000007;
    int N, K, Q;
    int[] arr, answers;
    int[][][] baseMats, baseInvMats;
    int[][] preInv;
    int[][][] currPre;
    // Grouped by R endpoint
    ArrayList<Query>[] queries;

    class Query {
        int l, i;
        Query(int l, int i) {
            this.l = l;
            this.i = i;
        }
    }

    nondecbetter(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());

        queries = new ArrayList[N];
        for (int i = 0; i < N; i++) queries[i] = new ArrayList<>(2);
        Q = Integer.parseInt(in.readLine());
        answers = new int[Q];
        int l, r;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            l = Integer.parseInt(st.nextToken()) - 1;
            r = Integer.parseInt(st.nextToken()) - 1;
            queries[r].add(new Query(l, i));
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
        preInv = new int[N][K + 1];
        currPre = new int[2][K + 1][K + 1];
        // Base matrix (copy of base matrix)
        int[][] currPreInv = new int[K + 1][K + 1];
        int val = arr[0];
        for (int i = 0; i <= K; i++) {
            for (int j = 0; j <= K; j++) {
                currPre[0][i][j] = baseMats[val][i][j];
                currPreInv[i][j] = baseInvMats[val][i][j];
            }
        }

        // Generate next preInv using smart matrix multiplication
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= K; j++) preInv[i][j] = currPreInv[0][j];
            if (i != N - 1) currPreInv = multInverse(baseInvMats[arr[i+1]], currPreInv, arr[i+1]);
        }

        // Keep a rolling sum matrix
        int currPreI = 0;
        for (int i = 0; i < N; i++) {
//            int[] result2 = new int[K + 1];
//            for (int j = 0; j <= K; j++) result2[j] = preInv[i][j];
//            result2 = multAnswer(result2, currPre[currPreI]);
//            System.out.println(Arrays.toString(preInv[i]));
//            System.out.println("2d");
//            printMatrix(currPre[currPreI]);
//            System.out.println(Arrays.toString(result2));
//            System.out.println("-");

            // Answer all queries here
            for (Query q : queries[i]) {
                int[] result = new int[K + 1];
                if (q.l != 0) {
                    for (int j = 0; j <= K; j++) result[j] = preInv[q.l-1][j];
                } else result[0] = 1;
                result = multAnswer(result, currPre[currPreI]);
                int sum = 0;
                for (int j = 0; j <= K; j++) sum = (sum + result[j]) % MOD;
                answers[q.i] = sum;
            }
            if (i != N - 1) currPre[1-currPreI] = multForward(currPre[currPreI], baseMats[arr[i+1]], arr[i+1]);
            currPreI = 1 - currPreI;
        }
        Arrays.stream(answers).forEach(out::println);
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
        new nondecbetter(in, out);
        in.close();
        out.close();
    }
}
