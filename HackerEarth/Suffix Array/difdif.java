/*
Solution: Use a suffix array with an LCP array to find the # of distinct substrings.
Runtime: O(|S| * log(|S|)^2)
*/

import java.util.*;
import java.io.*;

public class difdif {
    String str;

    difdif(BufferedReader in, PrintWriter out) throws IOException {
        str = in.readLine();
        SuffixArr sarr = new SuffixArr(str);
        // System.out.println(sarr);
        // System.out.println(sarr.LCP(0, 6));
        long answer = (long) str.length() * (str.length() + 1) / 2;
        // Remove overcounted strings
        for (int i = 1; i < str.length(); i++) {
            answer -= sarr.LCP(sarr.sarr[i-1], sarr.sarr[i]);
        }
        System.out.println(answer);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("difdif.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("difdif.out")));
        new difdif(in, out);
    }

    class SuffixArr {
        class Rank {
            int i, r, nr;
        }

        String str;
        int N, maxI;
        int[][] P;
        int[] POW2, sarr;
        Rank[] R;
        final int MAX_POW2 = 15;

        SuffixArr(String str) {
            POW2 = new int[MAX_POW2];
            POW2[0] = 1;
            for (int i = 1; i < MAX_POW2; i++) POW2[i] = POW2[i-1] * 2;

            this.str = str;
            N = str.length();
            for (int i = 1; i < MAX_POW2; i++) {
                if (POW2[i] >= N) {
                    maxI = i + 1;
                    break;
                }
            }
            P = new int[maxI][N];
            R = new Rank[N];

            // Sort by first character
            for (int j = 0; j < N; j++) {
                P[0][j] = str.charAt(j);
                R[j] = new Rank();
            }

            for (int i = 1; i < maxI; i++) {
                for (int j = 0; j < N; j++) {
                    R[j].i = j;
                    R[j].r = P[i-1][j];
                    R[j].nr = (j + POW2[i-1] >= N) ? -1 : P[i-1][j+POW2[i-1]];
                }

                Arrays.sort(R, (r1, r2) -> {
                    if (r1.r == r2.r) return r1.nr - r2.nr;
                    else return r1.r - r2.r;
                });

                for (int j = 0; j < N; j++) {
                    if (j != 0 && R[j-1].r == R[j].r && R[j-1].nr == R[j].nr) {
                        // This suffix gets same next rank as prev one
                        P[i][R[j].i] = P[i][R[j-1].i];
                    } else P[i][R[j].i] = j;
                }
            }

            sarr = new int[N];
            for (int i = 0; i < N; i++) sarr[P[maxI-1][i]] = i;
        }

        // Returns the LCP length between the suffixes [a, N-1] and [b, N-1] using a variant of binary lifting.
        int LCP(int a, int b) {
            int lcp = 0;
            for (int i = maxI - 1; i >= 0; i--) {
                if (P[i][a] == P[i][b]) {
                    // This means that [a, a + 2^i] and [b, b + 2^i] are the same
                    lcp += POW2[i];
                    a += POW2[i];
                    b += POW2[i];
                    if (a >= N || b >= N) break;
                }
            }
            return lcp;
        }

        public String toString() {
            StringBuilder sb = new StringBuilder("[");
            for (int i = 0; i < N; i++) {
                if (i != 0) sb.append(", ");
                sb.append(str.substring(sarr[i]));
            }
            sb.append("]");
            return sb.toString();
        }
    }
}
