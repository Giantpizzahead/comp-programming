/*
ID: sunnyky1
LANG: JAVA
TASK: ratios

Solution: Since the number of units of each type of feed in the mixture
must be <100, you can just brute force the solution.

Runtime: O(100^3)
*/

import java.util.*;
import java.io.*;

public class ratios {
    int N;
    int[] goal;
    int[][] mixtures;

    ratios(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        goal = new int[3];
        for (int i = 0; i < 3; i++) goal[i] = Integer.parseInt(st.nextToken());
        mixtures = new int[3][3];
        for (int i = 0; i < 3; i++) {
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < 3; j++) mixtures[i][j] = Integer.parseInt(st.nextToken());
        }

        int bestMultSum = 9999999, bestTargetMult = -1;
        int[] bestMults = new int[3];
        int[] currMults = new int[3];
        for (int i = 0; i < 100; i++) {
            currMults[0] = i;
            for (int j = 0; j < 100; j++) {
                currMults[1] = j;
                for (int k = 0; k < 100; k++) {
                    currMults[2] = k;
                    // Try these multiples
                    int[] sums = new int[3];
                    for (int l = 0; l < 3; l++) {
                        for (int m = 0; m < 3; m++) {
                            sums[l] += currMults[m] * mixtures[m][l];
                        }
                    }
                    // Check if sum is valid
                    if (sums[0] % goal[0] != 0) continue;
                    else {
                        int targetMult = sums[0] / goal[0];
                        if (targetMult == 0) continue;
                        if (goal[1] * targetMult == sums[1] && goal[2] * targetMult == sums[2]) {
                            // Valid
                            // System.out.println(i + " " + j + " " + k);
                            if (i + j + k < bestMultSum) {
                                bestMultSum = i + j + k;
                                bestTargetMult = targetMult;
                                bestMults = Arrays.copyOf(currMults, 3);
                            }
                        }
                    }
                }
            }
        }

        if (bestMultSum == 9999999) {
            out.println("NONE");
        } else {
            out.print(bestMults[0]);
            out.print(' ');
            out.print(bestMults[1]);
            out.print(' ');
            out.print(bestMults[2]);
            out.print(' ');
            out.print(bestTargetMult);
            out.println();
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        BufferedReader in = new BufferedReader(new FileReader("ratios.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ratios.out")));
        new ratios(in, out);
        in.close();
        out.close();
    }
}