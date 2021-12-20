/*
Solution: Do a floodfill-like search through the maze to find the max # of gems.

Runtime: O(n)
*/

import java.util.*;
import java.io.*;

public class gems {
    int T, A, B, C, N;
    int[] numGems;

    gems() throws IOException {
        Scanner sc = new Scanner(new FileReader("ipsc2012/g2.in"));
        PrintWriter fout = new PrintWriter("g.out");
        T = sc.nextInt();
        for (int i = 0; i < T; i++) {
            A = sc.nextInt();
            B = sc.nextInt();
            C = sc.nextInt();
            N = sc.nextInt();
            numGems = new int[N];
            floodfill();
            int max = 0;
            for (int j = 0; j < N; j++) max = Math.max(numGems[j], max);
            fout.println(max);
        }
        sc.close();
        fout.close();
    }

    void floodfill() {
        Stack<Integer> rooms = new Stack<>();
        for (int i = 0; i < N; i++) {
            if (numGems[i] == 0) {
                // Not yet visited; explore this path
                int loc = i, gems = 1;
                while (numGems[loc] == 0) {
                    rooms.add(loc);
                    numGems[loc] = -gems;  // Mark as visited
                    gems++;
                    loc = (int) (((long) A * loc * loc + (long) B * loc + C) % N);
                }

                // Mark # of gems
                if (numGems[loc] > 0) {
                    // Current path extends another path
                    gems = numGems[loc] + 1;
                    while (!rooms.isEmpty()) {
                        numGems[rooms.pop()] = gems++;
                    }
                } else {
                    // Cycle found
                    int cycleLength = gems + numGems[loc];
                    for (int j = 0; j < cycleLength; j++) numGems[rooms.pop()] = cycleLength;
                    gems = cycleLength + 1;
                    while (!rooms.isEmpty()) {
                        numGems[rooms.pop()] = gems++;
                    }
                }


            }
        }
    }

    public static void main(String[] args) throws IOException {
        new gems();
    }
}
