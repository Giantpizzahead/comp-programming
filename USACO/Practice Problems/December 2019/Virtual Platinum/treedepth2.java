/*
Solution: The key observation is that for a specific array a, index j is an ancestor of
index i iff a.min(i, j) = j. Using this fact, you can turn the problem into something
solvable using DP.

First, figure out how to count the # of arrays of length i with j inversions in O(N^3).
dp[i][j] = # of arrs length i with j inversions
BC: dp[0][0] = 1
dp[i][j] = sum from k -> j-i+1...j (dp[i-1][k])

This can be optimized using prefix sums or sliding window to get O(N^3).

Now, thinking of the value of d0 (total depth at index 0) will help make the solution path
become clear. When adding a new element to the end (extending length of array), if that
element is the smallest one so far (adding j-i+1 inversions), then that'll add 1 to d0 for
all arrays that can be formed from that point on. So, you can track a separate dp with
the d0 value for all arrays of length i with j inversions.

numArrs[i][j] = # of arrs length i with j inversions
depth[i][j] = Sum of d0 for arrs length i with j inversions
Both have the same transitions as the above one, but depth[i][j] += numArrs[i-1][j-i+1] at
each step (to add 1 to depth if the last element is the min one).

This solves d0. To generalize it to something in the middle, you can count the ancestors
on the right and left of the target index separately. You can't do them together, because
that'll mess up the counting (new element doesn't need to be min of the WHOLE array). So,
calculate the ancestors on the right, and then track the # of arrays that can be formed
with N length and K inversions (but don't add any new ancestors on the left!). Do the same
process for the left ancestors, and sum the two to get your answer.

Sadly, this solution is kinda hard to put into words, and the implementation isn't exactly
fun either. You have to do a few more tricks (like avoiding repeat caluclations by keeping
an "affect on answer" array / handling overcounting) to get the time complexity down to
O(N^3), but it's possible!

And guess what? NO GENERATING FUNCTIONS!!!!! :))))))))))))))))))))))))))))))

Runtime: O(N^3)
*/

import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class treedepth2 {
    int N, K, M, numTargetArrs, MAX_INV;
    // How many arrays len i with j inversions, when extended to length N, will have K
    // inversions? (How much does this state affect the answer?)
    int[][] affectOnAnswer, arrs, ancs;
    int[] ancOnLeft, ancOnRight;

    treedepth2(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        MAX_INV = sumFrom1(N - 1);

        ancOnLeft = new int[N];
        ancOnRight = new int[N];

        // Find affect on answer
        fillAffectDP();

        // for (int i = 0; i <= N; i++) System.out.println(Arrays.toString(affectOnAnswer[i]));

        // Fill in ancestor arrays
        fillRightAnc();
        fillLeftAnc();
        // System.out.println("Right anc: " + Arrays.toString(ancOnRight));
        // System.out.println("Left anc: " + Arrays.toString(ancOnLeft));
        // System.out.println("Array count: " + numTargetArrs);

        for (int i = 0; i < N; i++) {
            if (i != 0) out.print(' ');
            int answer = ancOnLeft[i] + ancOnRight[i] - numTargetArrs;
            if (answer < 0) answer += M;
            else answer %= M;
            out.print(answer);
        }
        out.println();
    }

    void fillAffectDP() {
        affectOnAnswer = new int[N + 1][MAX_INV + 1];
        affectOnAnswer[N][K] = 1;
        for (int i = N - 1; i >= 0; i--) {
            int maxInv = sumFrom1(i-1);
            // Use sliding window sum to speed up dp
            int currSum = 0;
            for (int k = maxInv; k <= maxInv + i; k++) {
                currSum += affectOnAnswer[i+1][k];
                currSum %= M;
            }
            // Fill in actual DP states
            for (int j = maxInv; j > 0; j--) {
                affectOnAnswer[i][j] = currSum;
                currSum -= affectOnAnswer[i+1][j + i];
                currSum += affectOnAnswer[i+1][j-1];
                if (currSum < 0) currSum += M;
                else currSum %= M;
            }
            affectOnAnswer[i][0] = currSum;
        }
    }

    void fillRightAnc() {
        // Both of these represent arrs length i with j inversions
        arrs = new int[N + 1][MAX_INV + 1];
        arrs[0][0] = 1;
        ancs = new int[N + 1][MAX_INV + 1];
        for (int i = 1; i <= N; i++) {
            int maxInv = sumFrom1(i-1);
            // Use sliding window sum to speed up dp
            int currArrSum = 0, currAncSum = 0;
            for (int k = maxInv; k >= Math.max(maxInv - i + 1, 0); k--) {
                currArrSum += arrs[i-1][k];
                currAncSum += ancs[i-1][k];
                currArrSum %= M;
                currAncSum %= M;
            }
            for (int j = maxInv; j >= 0; j--) {
                // Update # of arrs with j inversions
                // Also update # of ancestors on right
                arrs[i][j] = currArrSum;
                ancs[i][j] = currAncSum;
                // Add new ancestors (new element added was minimum)
                if (j - i + 1 >= 0) {
                    ancs[i][j] += arrs[i-1][j-i+1];
                    ancs[i][j] %= M;
                }
                // Update sliding window
                currArrSum -= arrs[i-1][j];
                currAncSum -= ancs[i-1][j];
                if (j - i >= 0) {
                    currArrSum += arrs[i-1][j - i];
                    currAncSum += ancs[i-1][j - i];
                }
                if (currArrSum < 0) currArrSum += M;
                else currArrSum %= M;
                if (currAncSum < 0) currAncSum += M;
                else currAncSum %= M;
            }

            // Save current # of ancestors
            for (int j = 0; j <= maxInv; j++) {
                ancOnRight[N - i] += (int) (((long) ancs[i][j] * affectOnAnswer[i][j]) % M);
                ancOnRight[N - i] %= M;
            }
        }

        // To prevent overcounting
        numTargetArrs = arrs[N][K];
    }

    void fillLeftAnc() {
        // Both of these represent arrs length i with j inversions
        // Don't make a new array, just clear the old one
        for (int i = 0; i <= N; i++) {
            Arrays.fill(arrs[i], 0);
            Arrays.fill(ancs[i], 0);
        }
        arrs[0][0] = 1;
        for (int i = 1; i <= N; i++) {
            int maxInv = sumFrom1(i-1);
            // Use sliding window sum to speed up dp
            int currArrSum = 0, currAncSum = 0;
            for (int k = maxInv; k >= Math.max(maxInv - i + 1, 0); k--) {
                currArrSum += arrs[i-1][k];
                currAncSum += ancs[i-1][k];
                currArrSum %= M;
                currAncSum %= M;
            }
            for (int j = maxInv; j >= 0; j--) {
                // Update # of arrs with j inversions
                // Also update # of ancestors on left
                arrs[i][j] = currArrSum;
                ancs[i][j] = currAncSum;
                // Add new ancestors (new element added was minimum)
                ancs[i][j] += arrs[i-1][j];
                ancs[i][j] %= M;
                // Update sliding window
                currArrSum -= arrs[i-1][j];
                currAncSum -= ancs[i-1][j];
                if (j - i >= 0) {
                    currArrSum += arrs[i-1][j - i];
                    currAncSum += ancs[i-1][j - i];
                }
                if (currArrSum < 0) currArrSum += M;
                else currArrSum %= M;
                if (currAncSum < 0) currAncSum += M;
                else currAncSum %= M;
            }

            // Save current # of ancestors
            // System.out.println("Left anc for " + (i - 1) + ": " + Arrays.toString(ancs[i]));
            for (int j = 0; j <= maxInv; j++) {
                ancOnLeft[i - 1] += (int) (((long) ancs[i][j] * affectOnAnswer[i][j]) % M);
                ancOnLeft[i - 1] %= M;
            }
        }
    }

    int sumFrom1(int n) {
        return n * (n + 1) / 2;
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("treedepth.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("treedepth.out")));
        new treedepth2(in, out);
        in.close();
        out.close();
    }
}
