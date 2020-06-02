/*
ID: sunnyky1
LANG: JAVA
TASK: runround

Solution: Try all possible numbers with distinct digits to find the next
runaround number. This is fine, since there are at max 10! numbers to try
with distinct digits.

Runtime: O(11! [~11 for testing runaroundness])
*/

import java.util.*;
import java.io.*;

public class runround {
    int M;
    long answer;

    runround() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("runround.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        M = Integer.parseInt(st.nextToken());
        fin.close();
        for (int i = 0; i < 9; i++) {
            findNum(i, new boolean[10], 0);
        }
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("runround.out")));
        fout.println(answer);
        fout.close();
    }

    void findNum(int i, boolean[] used, long partialNum) {
        if (i == -1) {
            // Try this # if it's greater
            // System.out.println(partialNum);
            if (partialNum > M && check(partialNum)) {
                answer = partialNum;
            }
            return;
        }
        for (int d = 1; d < 10; d++) {
            if (!used[d]) {
                used[d] = true;
                long newNum = partialNum + d * (long) Math.pow(10, i);
                findNum(i-1, used, newNum);
                used[d] = false;
                if (answer != 0) return;
            }
        }
    }

    boolean check(long num) {
        String numStr = Long.toString(num);
        boolean[] visited = new boolean[numStr.length()];
        int currLoc = 0;
        do {
            if (visited[currLoc]) return false;
            // Move to next #
            visited[currLoc] = true;
            currLoc = (currLoc + numStr.charAt(currLoc) - '0') % numStr.length();

        } while (currLoc != 0);

        // Check if all #s visited
        for (boolean b : visited) {
            if (!b) return false;
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        new runround();
    }
}