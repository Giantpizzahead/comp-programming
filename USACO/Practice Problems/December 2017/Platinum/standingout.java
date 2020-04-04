/*
Solution: First, make a suffix array. Then, traverse that suffix array using a sliding window like thing to figure out
the uniqueness factor of each suffix. Use the sum of these to find the uniqueness factor for all cows.
Runtime: O(N * log(N)^2)
*/

import java.util.*;
import java.io.*;

public class standingout {
    int N, totalLength;
    int[] cowID, idEndI;
    long[] uniqueFactor;
    String[] cows;
    final int INF = 97654321;

    standingout(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        cows = new String[N];
        totalLength = 0;
        for (int i = 0; i < N; i++) {
            cows[i] = in.readLine();
            totalLength += cows[i].length();
        }

        StringBuilder sb = new StringBuilder();
        totalLength += N;  // Account for added dollar signs
        cowID = new int[totalLength];
        idEndI = new int[N];
        int currI = 0;
        for (int i = 0; i < N; i++) {
            sb.append(cows[i]);
            sb.append('$');
            for (int j = 0; j < cows[i].length() + 1; j++) {
                cowID[currI++] = i;
            }
            idEndI[i] = currI - 1;
        }

        String str = sb.toString();

        SuffixArray sarr = new SuffixArray(str);
        // sarr.print();

        // Evaluate all suffixes, keeping pointers to the closest suffixes that aren't from the same string
        int left = N - 1, lastID = -1;
        // Skip all suffixes starting with $
        uniqueFactor = new long[N];
        for (int i = N; i < sarr.strLen; i++) {
            int currID = cowID[sarr.sarr[i]];
            int numSubstrings = idEndI[currID] - sarr.sarr[i];  // Overcounted # of substrings

            // Move left pointer if needed
            if (lastID != currID) left = i - 1;

            // Avoid overcounting
            numSubstrings -= Math.max(sarr.lcp(sarr.sarr[left], sarr.sarr[i]), (i == sarr.strLen - 1) ? 0 : sarr.lcp(sarr.sarr[i+1], sarr.sarr[i]));
            if (numSubstrings > 0) {
                uniqueFactor[currID] += numSubstrings;
                // System.out.println("Plus " + numSubstrings);
            }
            lastID = currID;
        }

        Arrays.stream(uniqueFactor).forEach(out::println);
    }

    class SuffixArray {
        class Rank {
            int i, r, nr;
        }

        String str;
        int strLen, logLen;
        int[][] P;
        int[] POW2, sarr;
        Rank[] R;
        final int MAX_POW2 = 18;

        SuffixArray(String str) {
            POW2 = new int[MAX_POW2];
            POW2[0] = 1;
            for (int i = 1; i < MAX_POW2; i++) POW2[i] = POW2[i-1] * 2;

            this.str = str;
            strLen = str.length();
            for (int i = 1; i < MAX_POW2; i++) {
                if (POW2[i] >= strLen) {
                    logLen = i + 1;
                    break;
                }
            }
            R = new Rank[strLen];
            for (int i = 0; i < strLen; i++) R[i] = new Rank();
            P = new int[logLen][strLen];

            // Sort by 1st character
            for (int j = 0; j < strLen; j++) {
                if (str.charAt(j) == '?') P[0][j] = -INF + cowID[j];
                else P[0][j] = str.charAt(j);
            }

            // Sort by first 2^i characters
            for (int i = 1; i < logLen; i++) {
                for (int j = 0; j < strLen; j++) {
                    R[j].i = j;
                    R[j].r = P[i-1][j];
                    R[j].nr = (j + POW2[i-1] >= strLen) ? -1 : P[i-1][j+POW2[i-1]];
                }

                Arrays.sort(R, (r1, r2) -> {
                   if (r1.r == r2.r) return r1.nr - r2.nr;
                   else return r1.r - r2.r;
                });

                boolean quitEarly = true;
                for (int j = 0; j < strLen; j++) {
                    if (j != 0 && R[j-1].r == R[j].r && R[j-1].nr == R[j].nr) {
                        P[i][R[j].i] = P[i][R[j-1].i];  // First 2^i characters are the same = same next rank
                        quitEarly = false;
                    } else P[i][R[j].i] = j;
                }

                if (quitEarly) {
                    // Optimization: Suffixes are already sorted, no need to continue
                    logLen = i + 1;
                    break;
                }
            }

            // Gen final suffix array
            sarr = new int[strLen];
            for (int i = 0; i < strLen; i++) {
                sarr[P[logLen-1][i]] = i;
            }
        }

        // Finds the length of the LCP between suffixes [a, strLen) and [b, strLen).
        int lcp(int a, int b) {
            int result = 0;
            for (int i = logLen - 1; i >= 0; i--) {
                if (P[i][a] == P[i][b]) {
                    result += POW2[i];
                    a += POW2[i];
                    b += POW2[i];
                    if (a == strLen || b == strLen) break;
                }
            }
            return result;
        }

        void print() {
            for (int i = 0; i < strLen; i++) System.out.println(str.substring(sarr[i]));
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("standingout.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("standingout.out")));
        new standingout(in, out);
        in.close();
        out.close();
    }
}
