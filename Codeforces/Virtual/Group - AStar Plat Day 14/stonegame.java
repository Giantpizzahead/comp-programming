/*
Solution: Handle the special case of having multiple stones of the same amount at the beginning.
Then, the ending state is always 0 1 2 3..., so figure out whose turn it is on that state.
Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class stonegame {
    int N;
    int[] stones;

    stonegame(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        stones = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) stones[i] = Integer.parseInt(st.nextToken());

        // Look for duplicates
        HashMap<Integer, Integer> numStones = new HashMap<>();
        int moreThan1 = -1;
        for (int i = 0; i < N; i++) {
            int newVal = numStones.getOrDefault(stones[i], 0) + 1;
            numStones.put(stones[i], newVal);
            if (newVal > 1) {
                // Possible issue
                if (moreThan1 != -1) {
                    // First player will lose
                    out.println("cslnb");
                    return;
                } else {
                    moreThan1 = stones[i];
                }
            }
        }

        if (moreThan1 != -1 && (moreThan1 == 0 || numStones.containsKey(moreThan1 - 1))) {
            // Cannot play first turn (again)
            out.println("cslnb");
            return;
        }

        // No edge cases; all moves will be valid until they reach the base state
        // how long will that take?
        Arrays.sort(stones);
        int moves = 0;
        for (int i = 0; i < N; i++) {
            moves += stones[i] - i;
            moves %= 2;
        }

        if (moves == 0) {
            // Toki's turn at state, so csl will win
            out.println("cslnb");
        } else {
            out.println("sjfnb");
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new stonegame(in, out);
        in.close();
        out.close();
    }
}
