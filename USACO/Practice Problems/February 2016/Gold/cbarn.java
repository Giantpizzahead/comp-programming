/*
Solution: Loop through the circle in the CCW direction, counting the # of cows / open spaces. Reset
whenever the # of cows > # of open spaces. Stop once you reach a repeat # (no resets occurred). This
won't take more than 2 loops around the circle.
Next, use a queue to push room locations, and add the cost of a cow moving as you go CCW through the
rooms. Greedily send the cows you encounter to the first room in the queue to minimize cost. Start
this queue search at the location found in Step 1.

Complexity: O(2N + 2N) = O(4N)
*/

import java.util.*;
import java.io.*;

public class cbarn {
    int N;
    int[] numCows;

    cbarn() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cbarn.in"));
        N = Integer.parseInt(fin.readLine());
        numCows = new int[N];
        for (int i = 0; i < N; i++) numCows[i] = Integer.parseInt(fin.readLine());
        fin.close();

        // Step 1: Find starting location for greedy
        int startingLoc = findStartLoc();
        // System.out.println(startingLoc);

        // Step 2: Run greedy
        long answer = moveCows(startingLoc);

        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cbarn.out")));
        out.println(answer);
        out.close();
    }

    int findStartLoc() {
        int numWithoutReset = 0;
        int currCount = 0;
        int i = 0;
        // Count # of cows and open spaces, resetting whenever there are more cows than open spaces
        while (numWithoutReset < N) {
            numWithoutReset++;
            currCount += numCows[i] - 1;
            if (currCount > 0) {
                numWithoutReset = 0;
                currCount = 0;
            }
            i--;
            if (i < 0) i += N;
        }

        return i;
    }

    long moveCows(int start) {
        Queue<Integer> unfilledRooms = new LinkedList<>();
        long cost = 0;
        for (int i = start, j = 0; j < N; i = (i == 0) ? N-1 : i - 1, j++) {
            unfilledRooms.add(j);
            for (int n = numCows[i]; n > 0; n--) {
                cost += Math.pow((j - unfilledRooms.poll()), 2);
            }
        }

        return cost;
    }

    public static void main(String[] args) throws IOException {
        new cbarn();
    }
}
