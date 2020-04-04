/*
Solution: Sliding window with math. I haven't proven that sliding window
works, but it seems to. So I'm gonna try it. It's quite easy to implement, so
if this doesn't get the problem right I'll try something else.

Runtime: O(N)
*/

import java.io.*;
import java.util.Arrays;

public class cowdatedp {
    int N;
    double[] probs;
    double[] prefixMults;

    cowdatedp() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cowdate.in"));
        N = Integer.parseInt(fin.readLine());
        probs = new double[N];
        for (int i = 0; i < N; i++) {
            probs[i] = Integer.parseInt(fin.readLine()) / 1000000d;
        }
        fin.close();

        // Try all ranges
        int[][] dp = new int[N][N];
        double maxSoFar = 0;
        for (int size = 0; size < N; size++) {
            int back = 0;
            double total = 0;
            double runningMultiple = 1;
            for (int i = 0; i < size; i++) {
                total *= (1 - probs[i]);
                total += probs[i] * runningMultiple;
                runningMultiple *= (1 - probs[i]);
            }
            // Simulate all ranges
            for (int front = size; front < N; front++) {
                total *= (1 - probs[front]);
                total += probs[front] * runningMultiple;
                runningMultiple *= (1 - probs[front]);
                maxSoFar = Math.max(total, maxSoFar);
                dp[front][size] = (int) (total * 1000000);
                // Remove the last one
                runningMultiple /= (1 - probs[back]);
                total -= probs[back] * runningMultiple;
                total /= (1 - probs[back]);
                back++;
            }
        }

        for (int[] row : dp) {
            System.out.println(Arrays.toString(row));
        }

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("cowdate.out")));
        fout.println((int) (maxSoFar * 1000000));
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new cowdatedp();
    }
}
