/*
Solution: Any painting with at least 1 K-length block of contiguous colors is a valid painting, as you
can individually paint every other square with the stamps, and overlay the last K-length block with the
final stamp. To count the number of these, do complimentary counting (# of paintings without a K-length
block). This can be done using DP with a sum optimization in O(N) time. The answer is # of possible
paintings - # of painting without K-length block.

Runtime: O(N)
*/

import java.util.*;
import java.io.*;

public class spainting {
    int N, M, K;
    final long MOD = 1000000007;

    spainting() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("spainting.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        fin.close();

        long numWithout = compCounting();
        // System.out.println(numWithout);
        long numWith = 1;
        for (int i = 0; i < N; i++) {
            numWith = (numWith * M) % MOD;
        }
        long answer = numWith - numWithout;
        if (answer < 0) answer += MOD;

        PrintWriter fout = new PrintWriter("spainting.out");
        fout.println(answer);
        fout.close();
    }

    long compCounting() {
        long[] toSubtract = new long[N];
        toSubtract[K - 1] = (K == 1) ? 0 : M;
        long currVal = 0, currSum = (K == 1) ? 0 : M;
        for (int i = 1; i < N; i++) {
            currVal = currSum * (M - 1) % MOD;
            currSum += currVal;
            currSum -= toSubtract[i];
            if (currSum < 0) currSum += MOD;
            else if (currSum >= MOD) currSum -= MOD;
            if (i + K - 1 < N) toSubtract[i + K - 1] = currVal;
        }
        return currSum;
    }

    public static void main(String[] args) throws IOException {
        new spainting();
    }
}
