/*
Solution: Divide-and-conquer DP!
Runtime: O(N^2 * K * log(N))
*/

import java.util.*;
import java.io.*;

public class cbarn {
    final long INF = 98765432198765432L;
    int N, K;
    int[] cows;

    cbarn(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        cows = new int[N];
        for (int i = 0; i < N; i++) cows[i] = Integer.parseInt(in.readLine());

        // Try starting at every door
        long minDist = INF;
        for (int i = 0; i < N; i++) {
            minDist = Math.min(startDP(i), minDist);
            // System.out.println("Start at " + i + " = " + startDP(i));
        }
        out.println(minDist);
    }

    long[] preRolling, preRegular;
    long[][] dp;

    long startDP(int s) {
        // Generate prefix sum arrays
        preRolling = new long[N];
        preRegular = new long[N];
        long currRolling = 0, currRegular = 0;
        for (int i = 0, j = s; i < N; i++, j = (j + 1) % N) {
            currRolling += (i+1) * cows[j];
            currRegular += cows[j];
            preRolling[i] = currRolling;
            preRegular[i] = currRegular;
        }

        // Now do the DP
        // dp[i][j] = Min total dist, last door opened is i, # additional doors opened is j
        dp = new long[N][K];
        // BC
        for (int i = 1; i < N; i++) dp[i][0] = INF;
        dp[0][0] = 0;
        for (int j = 1; j < K; j++) {
            divideAndConquer(j);
        }
        // System.out.println(Arrays.deepToString(dp));

        // Get best answer
        long bestAnswer = INF;
        for (int i = 0; i < N; i++) {
            bestAnswer = Math.min(dp[i][K-1] + cost(i, N-1), bestAnswer);
        }
        return bestAnswer;
    }

    Trans currTrans, lastTrans;

    void divideAndConquer(int j) {
        // Make monotonic queue
        Deque<Trans> dq = new LinkedList<>();
        dq.addLast(new Trans(0, 0));
        for (int i = 1; i < N; i++) {
            // Remove useless transitions
            currTrans = new Trans(i, -1);
            while (true) {
                if (dq.size() == 0) {
                    // Nothing to compare to
                    currTrans.takeoverI = 0;
                    dq.addLast(currTrans);
                    break;
                }

                lastTrans = dq.peekLast();
                // Binary search for takeover point
                int low = 0, high = N;
                while (low < high) {
                    int mid = (low + high) / 2;
                    if (compare(mid, j)) {
                        // Current transition wins here
                        high = mid;
                    } else {
                        // Old transition wins here
                        low = mid + 1;
                    }
                }

                if (low <= lastTrans.takeoverI) {
                    // Last transition is useless
                    dq.pollLast();
                } else {
                    // Takeover location found
                    currTrans.takeoverI = low;
                    dq.addLast(currTrans);
                    break;
                }
            }
        }

        // Now, actually use the transitions
        Trans c = dq.pollFirst();
        for (int i = 1; i < N; i++) {
            if (dq.size() != 0 && dq.peekFirst().takeoverI == i) {
                // Time to takeover!
                c = dq.pollFirst();
            }
            dp[i][j] = dp[c.origI][j-1] + cost(c.origI, i-1);
        }
    }

    boolean compare(int currI, int j) {
        long currCost = dp[currTrans.origI][j-1] + cost(currTrans.origI, currI-1);
        long lastCost = dp[lastTrans.origI][j-1] + cost(lastTrans.origI, currI-1);
        return currCost <= lastCost;
    }

    static class Trans {
        int origI, takeoverI;
        Trans(int o, int t) {
            origI = o;
            takeoverI = t;
        }
    }

    long cost(int a, int b) {
        if (a > b) return INF;
        long rollingSum = preRolling[b] - ((a == 0) ? 0 : preRolling[a-1]);
        long regularSum = preRegular[b] - ((a == 0) ? 0 : preRegular[a-1]);
        // System.out.println("Cost " + a + " " + b + " = " + (rollingSum - regularSum * (a)));
        return rollingSum - regularSum * (a+1);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("cbarn.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cbarn.out")));
        new cbarn(in, out);
        in.close();
        out.close();
    }
}
