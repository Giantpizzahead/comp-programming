/*
Solution: Fix the start location of the sequence you're currently checking. Sort both the spotted
and plain cow strings. Then, iterate through the plain cow strings, finding a string in the spotted
cow strings that matches the current substring. If one can be found, extend the current selection by
1. If none are found, record that as the max length needed to explain spotiness, and move to the
next string. To move to a new starting position, take the substring of all the strings (1, end), and
resort them.

Runtime: O(NM * log(M) + NM^2)
*/

import java.util.*;
import java.io.*;

public class cownomics {
    int N, M, currStrSize;
    String[] spotty, plain;

    cownomics() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cownomics.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        spotty = new String[N];
        plain = new String[N];
        for (int i = 0; i < N; i++) spotty[i] = fin.readLine();
        for (int i = 0; i < N; i++) plain[i] = fin.readLine();
        fin.close();

        // Try every possible starting location
        int shortestSeq = 987654321;
        currStrSize = M;
        for (int i = 0; i < M; i++) {
            Arrays.sort(spotty);
            Arrays.sort(plain);
            // System.out.println(Arrays.toString(spotty));
            // System.out.println(Arrays.toString(plain));
            shortestSeq = Math.min(shortestSeq, findShortest());
            // Setup for next
            for (int j = 0; j < N; j++) {
                spotty[j] = spotty[j].substring(1);
                plain[j] = plain[j].substring(1);
            }
            currStrSize--;
        }

        PrintWriter fout = new PrintWriter("cownomics.out");
        fout.println(shortestSeq);
        fout.close();
    }

    int findShortest() {
        int spottyI = 0, maxLength = 1;
        for (int plainI = 0; plainI < N;) {
            if (spottyI == N) break;
            else if (maxLength > currStrSize) return 987654321;
            int compareResult = spotty[spottyI].compareTo(plain[plainI].substring(0, maxLength));
            if (compareResult < 0) {
                // Keep going
                spottyI++;
            } else {
                // Check if gone too far or matched result
                if (spotty[spottyI].startsWith(plain[plainI].substring(0, maxLength))) {
                    // Extend maxLength
                    maxLength++;
                } else {
                    // Gone too far; this one's good, move to the next string
                    plainI++;
                }
            }
        }
        // System.out.println(maxLength);
        return maxLength;
    }

    public static void main(String[] args) throws IOException {
        new cownomics();
    }
}
