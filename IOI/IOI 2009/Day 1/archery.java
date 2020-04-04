/*
Solution: Naive solution; try every location, and simulate the first 2N rounds.
Runtime: O(N^3)
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class archery {
    int N, R, M;
    int[] startLine;

    archery(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        R = Integer.parseInt(st.nextToken());
        startLine = new int[N * 2 - 1];
        st = new StringTokenizer(in.readLine());
        M = Integer.parseInt(st.nextToken());
        for (int i = 0; i < N * 2 - 1; i++) {
            st = new StringTokenizer(in.readLine());
            startLine[i] = Integer.parseInt(st.nextToken());
        }

        int bestStartLoc = -1, bestEndLoc = N, currEndLoc = -1;
        if (M == 1) {
            // Case 1: I will always end at target 1
            out.println(N);
            return;
        } else if (M == 2 * N) {
            // Case 2: I will never move
            out.println(2);
            return;
        } else if (M > N + 1) {
            // Case 3: I will get stuck eventually
            // Try putting me in every place
            int[] archers = new int[N * 2];
            for (int i = N - 1; i >= 0; i--) {
                // Insert me into archers
                int offset = 0;
                for (int j = 0; j < N * 2; j++) {
                    if (j == i * 2) {
                        archers[j] = 0;
                        offset = 1;
                    } else if (startLine[j-offset] > M) {
                        archers[j] = 1;
                    } else archers[j] = -1;
                }

                // Simulate rounds until I get stuck (no more ++)
                boolean stopEarly = false;
                for (int r = 0; r < N * 2; r++) {
                    int[] newArchers = simulateRound(archers);
                    // System.out.println(Arrays.toString(archers));
                    // Can we stop early? (Exactly the same as last time)
                    stopEarly = true;
                    for (int j = 0; j < N * 2; j++) {
                        if (archers[j] != newArchers[j]) {
                            // No we cannot
                            stopEarly = false;
                            break;
                        }
                    }
                    archers = newArchers;
                    if (stopEarly) break;
                }

                // Find me & determine ending location
                for (int j = 0; j < N * 2; j++) {
                    if (archers[j] == 0) {
                        currEndLoc = j / 2;
                        break;
                    }
                }
                if (bestEndLoc > currEndLoc) {
                    bestStartLoc = i;
                    bestEndLoc = currEndLoc;
                    if (bestEndLoc == 0) break;
                }
                // System.out.println("Start " + i + ", end " + currEndLoc);
            }
        } else {
            // Case 4: I will get into a length N cycle eventually
            // Try putting me in every place
            int[] archers = new int[N * 2];
            for (int i = N - 1; i >= 0; i--) {
                // Insert me into archers
                int offset = 0;
                for (int j = 0; j < N * 2; j++) {
                    if (j == i * 2) {
                        archers[j] = 0;
                        offset = 1;
                    } else if (startLine[j-offset] > M) {
                        archers[j] = 1;
                    } else archers[j] = -1;
                }

                // Simulate rounds until I get stuck (no more ++)
                int roundsSoFar = 1;
                boolean stopEarly = false;
                for (; roundsSoFar <= N * 2; roundsSoFar++) {
                    archers = simulateRound(archers);
                    // System.out.println(Arrays.toString(archers));
                    // Can we stop early?
                    stopEarly = true;
                    for (int r = 1; r < N; r++) {
                        if (archers[r*2] != 1 && archers[r*2+1] != 1) {
                            // No we cannot
                            stopEarly = false;
                            break;
                        }
                    }
                    // Special case for top target
                    if (archers[0] == -1 && archers[1] == -1) stopEarly = false;
                    if (stopEarly) break;
                }

                int remaining = R - roundsSoFar;
                // Find me & determine ending location
                for (int j = 0; j < N * 2; j++) {
                    if (archers[j] == 0) {
                        currEndLoc = j / 2;
                        break;
                    }
                }

                // I am trapped in a cycle of length N
                currEndLoc = currEndLoc - (remaining % N);
                if (currEndLoc < 0) currEndLoc += N;
                if (bestEndLoc > currEndLoc) {
                    bestStartLoc = i;
                    bestEndLoc = currEndLoc;
                    if (bestEndLoc == 0) break;
                }
            }
        }
        out.println(bestStartLoc + 1);
    }

    int[] simulateRound(int[] archers) {
        int[] newArchers = new int[N * 2];
        for (int r = N - 1; r > 0; r--) {
            int win = Math.min(archers[r*2], archers[r*2+1]);
            int lose = Math.max(archers[r*2], archers[r*2+1]);
            newArchers[(r-1)*2] = win;
            newArchers[r*2+1] = lose;
        }
        // Handle last round as a special case
        int win = Math.min(archers[0], archers[1]);
        int lose = Math.max(archers[0], archers[1]);
        newArchers[1] = win;
        newArchers[(N-1)*2] = lose;
        return newArchers;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("archerysim.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("archerysim.out")));
        new archery(in, out);
        in.close();
        out.close();
    }
}
