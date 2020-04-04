/*
ID: sunnyky1
LANG: JAVA
TASK: barn1

Solution: Use a greedy algorithm to find the minimum of stalls that need to be blocked.
Start with the M=1 solution of the board from the first occupied to the last occupied.
Record the length of each segment inside that first board that is empty (no occupied).
Sort these lengths in decreasing order. Finally, subtract the first M-1 elements of the
sorted array to represent splitting the first board M-1 times, removing the longest gaps
in each split.
*/

import java.util.*;
import java.io.*;

public class barn1 {
    static int M, S, C;
    static int[] occupied;
    static ArrayList<Integer> freeLengths;

    public static void main(String[] args) throws IOException {
        // Input
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        M = Integer.parseInt(st.nextToken());
        S = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());

        // Parse all occupied stalls
        occupied = new int[C];
        for (int i = 0; i < C; i++) {
            occupied[i] = Integer.parseInt(fin.readLine());
        }

        // Sort occupied stalls to make it easier to deal with
        Arrays.sort(occupied);

        fin.close();

        // Solve the problem
        // First, find the lengths of each free segment inside the first board
        freeLengths = new ArrayList<>();
        int nextLength;
        for (int i = 1; i < C; i++) {
            nextLength = occupied[i] - occupied[i-1] - 1;
            if (nextLength != 0) freeLengths.add(nextLength);
        }

        // Sort those free lengths to let the greedy algorithm work
        freeLengths.sort(Comparator.comparingInt(a -> -a));

        // Run the greedy algorithm
        int currAnswer = occupied[C-1] - occupied[0] + 1;
        int bound = Math.min(M-1, freeLengths.size());
        for (int i = 0; i < bound; i++) {
            currAnswer -= freeLengths.get(i);
        }

        // Output
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("barn1.out")));
        fout.println(currAnswer);
        fout.close();
    }

}