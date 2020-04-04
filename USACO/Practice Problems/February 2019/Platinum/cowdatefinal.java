/*
Solution: From the N^2 exploration, it seems like you can binary search using
the first value. For every single first value, there's a perfect target size
that is better than all the other sizes. Find that for each, and max those.

Another observation is that the maximum value always occurs when the probabilities
sum up to 1 for some reason.
Runtime: O(N * log(N))
*/

import java.io.*;
import java.util.Arrays;

public class cowdatefinal {
    int N;
    double[] probs;
    double[] prefixMults;

    cowdatefinal() throws IOException {
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
        new cowdatefinal();
    }
}
