/*
Solution: Split the problem into individual parts, where you're only solving a range where the minimum
must be the same across that whole range. Do a bunch of math and stuff to figure out that there's a way
to sum and mod stuff to get the answer for that individual part. Just multiply the individual answers
together.

Runtime: Theoretically O(N * log(N)) but probably a bit slower
*/

import java.util.*;
import java.io.*;

public class tracking2 {
    int N, K, numSlidingMins;
    int[] slidingMins;
    final long MOD = 1000000007;
    final int MAX_FILL_VAL = 10;
    final int INF = 1000000007;

    tracking2() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("tracking2.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        numSlidingMins = N + 1 - K;
        slidingMins = new int[numSlidingMins + 1];
        for (int i = 0; i < numSlidingMins; i++) {
            slidingMins[i] = Integer.parseInt(fin.readLine());
        }
        // Add last sliding min to make code easier to implement
        slidingMins[numSlidingMins] = -INF;
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
        boolean lastNumMustBeMin = false;
        int lastMin = slidingMins[0];
        for (int i = 1; i < numSlidingMins + 1; i++) {
            if (lastMin == slidingMins[i]) continue;  // Nothing to do here
            else if (lastMin < slidingMins[i]) {
                // Min has increased:
                //   |---|
                // |---|
                // If first # of this range is a minimum, then calculate the # of ways to fill
                // from lastChangeI + K to i - K, with the last index being filled for you
                if (lastNumMustBeMin) answer *= solveRange(lastChangeI + K, i - K + 1, lastMin, true);
                // If first # is not a minimum, calculate # of ways to fill from lastChangeI to
                // i - K, with the last index being filled for you
                else answer *= solveRange(lastChangeI, i - K, lastMin, false);

                // Increased, so last num does not have to be min
                lastNumMustBeMin = false;
            } else {
                // Min has decreased:
                // |---|
                //   |---|
                // If first # of this range is a minimum, then calculate the # of ways to fill
                // from lastChangeI + K to i - 1
                if (lastNumMustBeMin) answer *= solveRange(lastChangeI + K, i - 2 + K, lastMin, true);
                // Else, calculate # of ways to fill from lastChangeI to i - 1
                else answer *= solveRange(lastChangeI, i - 2 + K, lastMin, false);

                // Decreased, so last num must be min
                lastNumMustBeMin = true;
            }

            answer %= MOD;
            lastChangeI = i;
            lastMin = slidingMins[i];
        }

        return answer;
    }

    long solveRange(int start, int end, int target, boolean lastIsMin) {
        System.out.println("start = " + start + ", end = " + end + ", target = " + target + ", lastIsMin = " + lastIsMin);
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
                // System.out.println("Removed " + (prevSums[i-K] * Math.pow(MAX_FILL_VAL - target, K - 1)));
                if (toMultiply == -1) toMultiply = calcMultiply(target);
                sum -= prevSums[i-K] * toMultiply;
                sum %= MOD;
                if (sum < 0) sum = MOD + sum;
            }

            // Calculate new sum
            sum = (sum * (MAX_FILL_VAL - target)) % MOD + prevSums[i];
            sum %= MOD;
        }

        System.out.println("Result: " + sum);
        return sum;
        /*
        if (lastIsMin) {
            System.out.println("Result: " + prevSums[numInRange - 1]);
            return prevSums[numInRange - 1];
        } else {
            System.out.println("Result: " + sum);
            return sum;
        }
         */
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
        new tracking2();
    }
}
