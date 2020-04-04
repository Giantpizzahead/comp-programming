/*
Solution: First, convert the cow heights to a 0-1 array, where 0 is a
height that doesn't meet the median threshold, and 1 does.

Keep track of the location of 0 in a Fenwick tree. Anything >= 0 means
that the median will be a 1 (equal or more 1s than 0s). Used to query
the sum of the range of all locations where there are enough cows to take
a photo.

Then, iterate through the cows. If the current cow is 1, move the 0 location
to the left 1 (all current locations get +1 1 cow). Else, move the 0 location
to the right 1. If the cow is 1, add 1 to the current 0 location +1; else,
add 1 to the current 0 location -1. Finally, query from the current 0 location
to the maximum index in the Fenwick tree, and add that to the answer.
 */

import java.util.*;
import java.io.*;

public class median {
    int N, X;
    boolean[] cows;

    median() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        X = Integer.parseInt(st.nextToken());
        cows = new boolean[N];
        int c;
        for (int i = 0; i < N; i++) {
            c = Integer.parseInt(in.readLine());
            cows[i] = c >= X;
        }
        in.close();

        // Run the algorithm
        long answer = 0;
        int zeroLoc = N;
        FenwickTree ft = new FenwickTree(N*2+1);
        for (int i = 0; i < N; i++) {
            ft.increment(zeroLoc, 1);
            if (cows[i]) {
                zeroLoc--;
            } else {
                zeroLoc++;
            }
            answer += ft.query(zeroLoc);
        }

        System.out.println(answer);
    }

    public static void main(String[] args) throws IOException {
        new median();
    }

    static class FenwickTree {
        int size;
        int[] values;

        FenwickTree(int size) {
            this.size = size;
            values = new int[size];
        }

        /*
        Increment the value at i by v.
         */
        void increment(int i, int v) {
            if (i >= size) return;
            values[i] += v;
            increment(i + Integer.lowestOneBit(i), v);
        }

        /*
        Query a range from i to the size of the Fenwick tree (inclusive).
         */
        int query(int i) {
            return __query(size - 1) - ((i == 0) ? 0 : __query(i - 1));
        }

        /*
        Query from 0 to i (inclusive).
         */
        int __query(int i) {
            if (i == 0) return values[0];
            else return values[i] + __query(i - Integer.lowestOneBit(i));
        }
    }
}
