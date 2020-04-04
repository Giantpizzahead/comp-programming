/*
ID: sunnyky1
LANG: JAVA
TASK: sort3

Solution: First, figure out where the 1s, 2s, and 3s should be in the final
sorted sequence (sum up # of each and find starting locs). Then, find out
the number of 1s, 2s, and 3s that are actually in each section. Now, do all
the swaps that swap two numbers to the right sections (1 in section 2 and 2
in section 1, etc.), since this is always optimal. Any remaining numbers are
in a cycle (1 in section 2, 2 in section 3, 3 in section 1, or the other
way around). These will all have 1 incorrect # in each section, so sum up
the # of incorrect numbers in section 1, and multiply it by 2 (need 2 swaps
to sort these cycles).

Runtime: O(N)
*/

import java.util.*;
import java.io.*;

public class sort3 {
    int N;
    int[] numOfEach;
    int[] arr;

    sort3() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        N = Integer.parseInt(fin.readLine());
        numOfEach = new int[4];
        arr = new int[N];
        for (int i = 0; i < N; i++) {
            // Find # of 1s, 2s, and 3s
            arr[i] = Integer.parseInt(fin.readLine());
            numOfEach[arr[i]]++;
        }
        fin.close();

        // Find starting location of each section
        int[] startingLoc = new int[4];
        startingLoc[2] = numOfEach[1];
        startingLoc[3] = startingLoc[2] + numOfEach[2];

        // Find # of each in the sections
        // numWrongSection[i][j] = # of js that are in the section meant
        // for the number i
        int[][] numInSection = new int[4][4];
        for (int i = 0; i < startingLoc[2]; i++) {
            numInSection[1][arr[i]]++;
        }
        for (int i = startingLoc[2]; i < startingLoc[3]; i++) {
            numInSection[2][arr[i]]++;
        }
        for (int i = startingLoc[3]; i < N; i++) {
            numInSection[3][arr[i]]++;
        }

        // Swap 2 #s in swapped sections
        int answer = 0;
        for (int i = 1; i < 4; i++) {
            for (int j = 1; j < 4; j++) {
                if (i == j) continue;
                int toSwap = Math.min(numInSection[i][j], numInSection[j][i]);
                numInSection[i][j] -= toSwap;
                numInSection[j][i] -= toSwap;
                answer += toSwap;
            }
        }

        // Swap #s in cycle
        for (int j = 2; j < 4; j++) {
            answer += numInSection[1][j] * 2;
        }

        PrintWriter fout = new PrintWriter("sort3.out");
        fout.println(answer);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new sort3();
    }
}