/*
Solution: BIT.
Runtime: O(N * log(N))
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class cerseiArmy {
    int T, N, K;
    int[] arr;
    Integer[] sortedPre;
    long[] pre;

    cerseiArmy(BufferedReader in, PrintWriter out) throws IOException {
        T = Integer.parseInt(in.readLine());
        for (int t = 0; t < T; t++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            N = Integer.parseInt(st.nextToken());
            K = Integer.parseInt(st.nextToken());
            // Adjust all elements to essentially make K = 0
            arr = new int[N];
            st = new StringTokenizer(in.readLine());
            for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken()) - K;

            // Gen prefix sum array
            pre = new long[N];
            pre[0] = arr[0];
            for (int i = 1; i < N; i++) pre[i] = pre[i - 1] + arr[i];
            // System.out.println(Arrays.toString(pre));

            sortedPre = new Integer[N];
            for (int i = 0; i < N; i++) sortedPre[i] = i;
            Arrays.sort(sortedPre, (a, b) -> {
                long res = pre[a] - pre[b];
                if (res > 0) return 1;
                else if (res < 0) return -1;
                return 0;
            });

            long answer = 0;
            BIT bit = new BIT(N + 1);
            for (int i : sortedPre) {
                if (pre[i] >= 0) answer++;
                answer += bit.query(i);
                bit.increment(i + 1);
            }
            System.out.println(answer);
        }
    }

    class BIT {
        int size;
        int[] vals;

        BIT(int size) {
            this.size = size;
            vals = new int[size + 1];
        }

        // Adds 1 to index i (one-indexed).
        void increment(int i) {
            while (i <= size) {
                vals[i]++;
                i += Integer.lowestOneBit(i);
            }
        }

        // Queries sum from [1, i].
        int query(int i) {
            int result = 0;
            while (i > 0) {
                result += vals[i];
                i -= Integer.lowestOneBit(i);
            }
            return result;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("SUBARR.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("SUBARR.out")));
        new cerseiArmy(in, out);
        in.close();
        out.close();
    }
}
