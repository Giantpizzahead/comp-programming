/*
Solution: First, remove any lifeguard that is completely enclosed in another lifeguard's shift (since removing that
lifeguard will always be better than removing the larger lifeguard). This leaves segments that can be sorted by both
start and end point.

Now, the problem becomes a dp problem. dp[i][j] = Max time covered with lifeguards 0 to i (inclusive) after firing
exactly j lifeguards. The ith lifeguard must not be fired.

This DP can be solved with a divide-and-conquer technique, since the previous states are arranged in a diagonal line
(when visualized), and they're monotonic.

Runtime: O(NK * log(K))
*/

import java.util.*;
import java.io.*;

public class lifeguards {
    int N, K;
    int[][] dpTrans, dp;
    boolean[] isRedundant;
    Pair[] lifeguards;
    final int INF = 1000000007;

    lifeguards() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("lifeguards.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        lifeguards = new Pair[N];
        int a, b;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            lifeguards[i] = new Pair(a, b);
        }
        fin.close();
        Arrays.sort(lifeguards, Comparator.comparingInt(x -> x.a));

        // Remove redundant lifeguards
        int maxEndpoint = -1;
        int newN = N;
        isRedundant = new boolean[N];
        for (int i = 0; i < N; i++) {
            if (lifeguards[i].b < maxEndpoint) {
                // Redundant; treat this lifeguard as fired
                isRedundant[i] = true;
                newN--;
                K--;
            }
            maxEndpoint = Math.max(lifeguards[i].b, maxEndpoint);
        }

        // Form new array without redundant things
        Pair[] newLifeguards = new Pair[newN + 1];
        for (int i = 0, j = 0; i < N; i++) {
            if (!isRedundant[i]) newLifeguards[j++] = lifeguards[i];
        }
        // For easier implementation
        newLifeguards[newN] = new Pair(INF, INF);
        lifeguards = newLifeguards;
        N = newN;

        // System.out.println("New N: " + N);
        // System.out.println("New K: " + K);
        // System.out.println(Arrays.toString(newLifeguards));

        if (K < 0) K = 0;
        preCompDPTrans();
        int answer = doDP();

        // System.out.println("# operations: " + numOps);
        
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("lifeguards.out")));
        fout.println(answer);
        fout.close();
    }

    long numOps = 0;
    int doDP() {
        dp = new int[N + 1][K + 1];
        // Base cases (1st segment used)
        for (int i = 0; i < K + 1; i++) {
            dp[i][i] = lifeguards[i].b - lifeguards[i].a;
        }

        // For now, do the dp without divide and conquer
        for (int diag = K + 1; diag < N + 1; diag++) {
            for (int j = 0, i; j < K + 1; j++) {
                i = diag - K + j;
                // Try every possible transition
                int bestTrans = -INF;
                for (int k = 0; k <= j; k++) {
                    // numOps++;
                    bestTrans = Math.max(trans(i, j, k), bestTrans);
                }
                dp[i][j] = bestTrans;
            }
        }

        /*
        // Calculate each diagonal one at a time to take advantage of monotonicity
        // Start at the top-right, going down to bottom-left
        for (int i = K + 1; i < N + 1; i++) {
            // Track current best state to transition from, along with next best state
            //TODO: track next value too
            int currState = 0, nextState = -1, nextTakeoverLoc = -INF;
            dp[i-K][0] = dp[i-K-1][0] + dpTrans[i-K][0];
            for (int j = K - 1; j >= 0; j--) {
                int currTakeoverLoc = findTakeoverLoc(i, currState, j);
                if (currTakeoverLoc >= nextTakeoverLoc) {
                    // This state will take over faster; record it
                    nextState = j;
                    nextTakeoverLoc = currTakeoverLoc;
                }

                if (j <= currTakeoverLoc) {
                    // Current state has been taken over
                    currState = nextState;
                    nextState = -1;
                    nextTakeoverLoc = -INF;
                }

                System.out.println("Best state: " + currState + " " + trans(i-j, K-j, currState));
                dp[i-j][K-j] = trans(i-j, K-j, currState);
            }
        }
         */

        // for (int i = 0; i < N + 1; i++) System.out.println(Arrays.toString(dp[i]));
        return dp[N][K];
    }

    // Finds the time at which b overtakes a (if it does).
    int findTakeoverLoc(int i, int a, int b) {
        // System.out.println("Takeover i = " + i + ", a = " + a + ", b = " + b);
        int low = 0, high = b;
        while (low < high) {
            int mid = (low + high) / 2;
            if (trans(i-mid, K-mid, b-mid) > trans(i-mid, K-mid, a-mid)) {
                // b has overtaken here
                high = mid;
            } else {
                // a hasn't been overtaken
                low = mid + 1;
            }
        }
        // System.out.println("Takeover loc: " + low);
        return low;
    }

    // i, j = dp location to transition to, k = transition number
    int trans(int i, int j, int k) {
        // System.out.println("i = " + i + ", j = " + j + ", k = " + k);
        return dp[i-k-1][j-k] + dpTrans[i][k];
    }

    // length(i) + overlap(i - j - 1, i)
    // j from 0 to 100
    void preCompDPTrans() {
        dpTrans = new int[N + 1][K + 1];
        for (int i = 0; i < N + 1; i++) {
            for (int j = 0; j < K + 1; j++) {
                if (i - j - 1 < 0) break;
                dpTrans[i][j] = lifeguards[i].b - lifeguards[i].a - Math.max(lifeguards[i-j-1].b - lifeguards[i].a, 0);
            }
        }
        // for (int i = 0; i < N + 1; i++) System.out.println(Arrays.toString(dpTrans[i]));
    }

    public static void main(String[] args) throws IOException {
        new lifeguards();
    }

    class Pair {
        int a, b;
        Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
        public String toString() {
            return "(" + a + ", " + b + ")";
        }
    }
}