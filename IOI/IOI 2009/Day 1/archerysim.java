/*
Solution: Helper for simulating archery things.
Runtime: O(who cares)
*/

import java.util.*;
import java.io.*;

public class archerysim {
    int N, R;
    int[] archers;

    archerysim(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        R = Integer.parseInt(st.nextToken());
        archers = new int[N * 2];
        for (int i = 0; i < N * 2; i++) {
            st = new StringTokenizer(in.readLine());
            archers[i] = Integer.parseInt(st.nextToken());
        }

        for (int i = 0; i < R; i++) {
            System.out.println(Arrays.toString(archers));
            archers = simulateRound(archers);
        }
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
        new archerysim(in, out);
        in.close();
        out.close();
    }
}
