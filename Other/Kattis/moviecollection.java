/*
Solution: Use a Fenwick tree to store how many movies are above each movie box. Keep a
mapping from movie box IDs to indexes in the Fenwick tree. When a movie box is taken out,
add 1 to the range from where the movie box was removed to the max index in the tree. Update
the mapped index to the next free location in the Fenwick tree (this means the Fenwick tree
will be of size 2m). Output the value at the place where the movie box was removed.

Runtime: O(r * log(m))
*/

import java.util.*;
import java.io.*;

public class moviecollection {
    int T, m, r;
    int[] queries, answers, idToIndex;

    moviecollection() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) runTestCase(in);
        in.close();
    }

    void runTestCase(BufferedReader in) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        m = Integer.parseInt(st.nextToken());
        r = Integer.parseInt(st.nextToken());
        queries = new int[r];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < r; i++) {
            queries[i] = Integer.parseInt(st.nextToken());
        }

        // Generate the Fenwick tree (filled with 1s at start)
        int ftSize = m + r;
        FenwickTree ft = new FenwickTree(ftSize);
        for (int i = r + 2; i <= ftSize; i++) {
            ft.increment(i, ftSize, 1);
        }

        // System.out.println(Arrays.toString(ft.v));

        // Generate idToIndex
        idToIndex = new int[m + 1];
        for (int i = 1; i <= m; i++) {
            idToIndex[i] = r + i;
        }

        // Run all the queries
        int nextFree = r;
        answers = new int[r];
        for (int i = 0; i < r; i++) {
            answers[i] = ft.query(idToIndex[queries[i]]);
            // Update Fenwick tree
            ft.increment(idToIndex[queries[i]], ftSize, -1);
            ft.increment(nextFree + 1, ftSize, 1);
            // Update idToIndex
            idToIndex[queries[i]] = nextFree;
            nextFree--;
        }

        // Print all the answers
        for (int i = 0; i < answers.length - 1; i++) {
            System.out.print(answers[i] + " ");
        }
        System.out.println(answers[answers.length - 1]);
    }

    public static void main(String[] args) throws IOException {
        new moviecollection();
    }

    static class FenwickTree {
        int size;
        int[] v;

        /*
        Initialize a Fenwick tree with a given size.
         */
        FenwickTree(int size) {
            this.size = size;
            v = new int[size + 1];
        }

        /*
        Increments the range of values from a to b (inclusive) by the given value.
         */
        void increment(int a, int b, int value) {
            place(a, value);
            place(b + 1, -value);
        }

        /*
        Places the given value at the given index in the Fenwick tree.
         */
        void place(int i, int value) {
            while (i <= size) {
                v[i] += value;
                i += Integer.lowestOneBit(i);
            }
        }

        /*
        Gets the value at index i in the Fenwick tree.
         */
        int query(int i) {
            int result = 0;
            while (i != 0) {
                result += v[i];
                i -= Integer.lowestOneBit(i);
            }
            return result;
        }
    }
}
