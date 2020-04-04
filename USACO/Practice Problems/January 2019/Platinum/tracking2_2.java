/*
Solution: Split the problem into individual parts, where you're only solving a range where the minimum
must be the same across that whole range. Do a bunch of math and stuff to figure out that there's a way
to sum and mod stuff to get the answer for that individual part. Just multiply the individual answers
together.

Runtime: Theoretically O(N * log(N)) but probably a bit slower
*/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class tracking2_2 {
    int N, K, numSlidingMins;
    int[] slidingMins;
    final long MOD = 1000000007;
    final int MAX_FILL_VAL = 1000000000;
    final int INF = 1000000007;

    tracking2_2() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("tracking2.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        numSlidingMins = N + 1 - K;
        slidingMins = new int[numSlidingMins + 2];
        for (int i = 1; i < numSlidingMins + 1; i++) {
            slidingMins[i] = Integer.parseInt(fin.readLine());
        }
        // Add 2 sliding mins to make code easier to implement
        slidingMins[0] = -INF;
        slidingMins[numSlidingMins + 1] = -INF;
        fin.close();

        /*
        K = 3;
        for (int i = 0; i < 5; i++) System.out.println(solveRange(0, i, 7, false));
         */

        long answer = solve();
        PrintWriter fout = new PrintWriter("tracking2.out");
        fout.println(answer % MOD);
        fout.close();
    }

    long solve() {
        long answer = 1;
        int lastChangeI = 0;
        boolean lastChangeWasDecrease = false;
        int lastMin = slidingMins[0];
        for (int i = 1; i < numSlidingMins + 2; i++) {
            if (lastMin == slidingMins[i]) continue;  // Nothing to do here
            else if (lastMin < slidingMins[i]) {
                // Increase
                if (lastChangeWasDecrease) {
                    answer *= solveRange(lastChangeI + K, i-1, lastMin, true);
                } else {
                    answer *= solveRange(lastChangeI, i-1, lastMin, true);
                }
                lastChangeWasDecrease = false;
            } else {
                // Decrease
                if (lastChangeWasDecrease) {
                    answer *= solveRange(lastChangeI + K, i-2+K, lastMin, false);
                } else {
                    answer *= solveRange(lastChangeI, i-2+K, lastMin, false);
                }
                lastChangeWasDecrease = true;
            }

            answer %= MOD;
            lastChangeI = i;
            lastMin = slidingMins[i];
        }

        return answer;
    }

    long solveRange(int start, int end, int target, boolean lastNumMustBeMin) {
        // System.out.println("start = " + start + ", end = " + end + ", target = " + target + ", lastNumMustBeMin = " + lastNumMustBeMin);
        if (start > end) return 1;

        // Solve the range
        int numInRange = end - start + 1;
        // Represents the # of ways you can get a state of (i, i)
        long[] prevSums = new long[numInRange + 1];
        prevSums[0] = 1;
        long sum = 1;
        long toMultiply = -1;
        for (int i = 1; i <= numInRange; i++) {
            prevSums[i] = sum;
            if (i >= K) {
                // Remove ways that can't be randomly filled anymore
                if (toMultiply == -1) toMultiply = calcMultiply(target);
                sum -= prevSums[i-K] * toMultiply;
                sum %= MOD;
                if (sum < 0) sum = MOD + sum;
            }

            // Calculate new sum
            sum = (sum * (MAX_FILL_VAL - target)) % MOD + prevSums[i];
            sum %= MOD;
        }

        if (lastNumMustBeMin) {
            // System.out.println("Result: " + prevSums[numInRange]);
            return prevSums[numInRange];
        } else {
            // System.out.println("Result: " + sum);
            return sum;
        }
    }

    long calcMultiply(int target) {
        long val = 1;
        for (int i = 1; i < K; i++) {
            val *= MAX_FILL_VAL - target;
            val %= MOD;
        }
        return val;
    }

    public static void main(String[] args) throws IOException {
        new tracking2_2();
    }
}
