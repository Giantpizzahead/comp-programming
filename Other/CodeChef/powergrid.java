import java.util.*;
import java.io.*;

public class powergrid {
    int K, M;
    int[] arr;

    powergrid(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        K = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        arr = new int[M];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < M; i++) arr[i] = Integer.parseInt(st.nextToken());

        // Find basis vectors needed to represent the given array elements
        findBasis();
        // System.out.println("Basis: " + Arrays.toString(basis));

        // Answer = 2^(K-numBasis)
        long answer = (long) Math.pow(2, K - numBasis);
        out.println(answer);
    }

    // basis[i] = Basis vector with lowest one bit at position i
    int numBasis = 0;
    int[] basis;
    void findBasis() {
        basis = new int[K];
        int c;
        for (int i = 0; i < M; i++) {
            c = arr[i];
            for (int j = 0; j < K; j++) {
                if ((c & (1 << j)) == 0) continue;  // jth bit is not set

                // Can current basis vectors account for this?
                if (basis[j] != 0) {
                    // Yes!
                    c ^= basis[j];
                } else {
                    // New basis vector needed
                    basis[j] = c;
                    numBasis++;
                    break;
                }
            }
            // If gets through this check without any issues, current basis
            // vectors are enough
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new powergrid(in, out);
        in.close();
        out.close();
    }
}