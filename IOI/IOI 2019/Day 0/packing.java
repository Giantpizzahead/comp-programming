/*
Solution: Greedily use up the largest shirts first, packing only completely full boxes until there's
no possible way to.
Runtime: O(100N)
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class packing {
    final int MAXS = 11, MAXB = 21;
    // final int[] priority = {1, 2, 4, 5, 10, 3, 6, 9, 8, 7};
    final int[] priority = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int N, K, boxesUsed = 0;
    Stack<Integer>[] origShirtI;
    int[] numShirts, packingPlan;

    packing(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        numShirts = new int[MAXS];
        st = new StringTokenizer(in.readLine());
        origShirtI = new Stack[MAXS];
        for (int i = 1; i < MAXS; i++) origShirtI[i] = new Stack<>();
        for (int i = 0; i < N; i++) {
            int v = Integer.parseInt(st.nextToken());
            origShirtI[v].add(i);
            numShirts[v]++;
        }

        packingPlan = new int[N];
        while (N > 0) {
            shirtCosts = new ArrayList<>();
            for (int i : priority) {
                int currSum = 0;
                for (int j = 0; j < numShirts[i]; j++) {
                    currSum += i;
                    if (currSum >= MAXB) break;  // We'll never need this many shirts
                    shirtCosts.add(i);
                }
            }
            getNewBox();
        }

        out.println(boxesUsed);
        for (int i = 0; i < packingPlan.length; i++) {
            if (i != 0) out.print(' ');
            out.print(packingPlan[i]);
        }
        out.println();
        out.close();

        System.out.println("Over by " + (boxesUsed - K));
    }

    ArrayList<Integer> shirtCosts;
    int tempN;
    boolean[][] dp;
    void getNewBox() {
        // System.out.println(shirtCosts);
        tempN = shirtCosts.size();
        dp = new boolean[tempN][MAXB];
        dp[0][0] = true;
        dp[0][shirtCosts.get(0)] = true;
        // For each shirt
        for (int i = 1; i < tempN; i++) {
            // For each current volume
            for (int j = 0; j < MAXB; j++) {
                dp[i][j] = dp[i-1][j];
                if (j-shirtCosts.get(i) >= 0) dp[i][j] |= dp[i-1][j-shirtCosts.get(i)];
            }
        }

        // Check for any valid packing
        // Try your best to use up the first shirt
        for (int i = MAXB - 1; i >= 0; i--) {
            if (dp[tempN-1][i]) {// && (tempN == 1 || dp[tempN-2][i-shirtCosts.get(tempN-1)])) {
                genValidPacking(i, tempN - 1);
                boxesUsed++;
                return;
            }
        }

        // No more packings...?
        // System.out.println("no valid");
    }

    void genValidPacking(int v, int currN) {
        if (v == 0) return;  // Done with this box

        if (v-shirtCosts.get(currN) < 0) {
            // Can't use this anyways
            genValidPacking(v, currN - 1);
            return;
        }

        // Use this shirt if possible
        if (currN == 0 || dp[currN-1][v-shirtCosts.get(currN)]) {
            // This shirt can be used
            numShirts[shirtCosts.get(currN)]--;
            N--;
            packingPlan[origShirtI[shirtCosts.get(currN)].pop()] = boxesUsed;
            genValidPacking(v-shirtCosts.get(currN), currN - 1);
        } else {
            // Can't use this shirt
            genValidPacking(v, currN - 1);
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        // new packing(in, out);
        for (int i = 1; i <= 10; i++) {
            BufferedReader in = new BufferedReader(new FileReader("0" + i + ".in"));
            PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("0" + i + ".out")));
            new packing(in, out);
            in.close();
            out.close();
        }
    }
}
