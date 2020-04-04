/*
Solution: Naive solution; try every location, and simulate the first 2N rounds.
Runtime: O(N^3)
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class archeryn3 {
    int N, R, M;
    int[] startLine, archers;

    archeryn3(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        R = Integer.parseInt(st.nextToken());
        startLine = new int[N * 2 - 1];
        archers = new int[N * 2];
        st = new StringTokenizer(in.readLine());
        M = Integer.parseInt(st.nextToken());
        for (int i = 0; i < N * 2 - 1; i++) {
            st = new StringTokenizer(in.readLine());
            startLine[i] = Integer.parseInt(st.nextToken());
        }

        // Try putting me in every place
        int bestStartLoc = -1, bestEndLoc = N;
        for (int i = N - 1; i >= 0; i--) {
            // Insert me into archers
            int offset = 0;
            for (int j = 0; j < N * 2; j++) {
                if (j == i * 2) {
                    archers[j] = M;
                    offset = 1;
                } else archers[j] = startLine[j-offset];
            }
            // Simulate first 2N rounds
            for (int j = 0; j < N * 2; j++) archers = simulateRound(archers);
            int remaining = R - N * 2, currEndLoc = -1;
            // Find me & determine ending location
            for (int j = 0; j < N * 2; j++) {
                if (archers[j] == M) {
                    currEndLoc = j / 2;
                    break;
                }
            }

            if (M != 1 && M < N + 1) {
                // I am trapped in a cycle of length N
                currEndLoc = currEndLoc - (remaining % N);
                if (currEndLoc < 0) currEndLoc += N;
            }

            if (bestEndLoc > currEndLoc) {
                bestStartLoc = i;
                bestEndLoc = currEndLoc;
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
        new archeryn3(in, out);
        in.close();
        out.close();
    }
}
