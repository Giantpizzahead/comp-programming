/*
Solution: Count the # of unfriendly crossing pairs of breeds using a allocated-only-if-needed
2D BIT. To avoid overcounting, only count the crosses with the top left field being a certain
breed ID.

Runtime: O(N * log(N)^2) although this is probably more like O(N * sqrt(N)) in practice
*/

import java.util.*;
import java.io.*;

public class friendcross {
    int N, K;
    int[] left, right, idToRightI;
    final int MIN_BIT_SIZE = 513;

    friendcross(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        left = new int[N];
        right = new int[N];
        idToRightI = new int[N + 1];
        for (int i = 0; i < N; i++) left[i] = Integer.parseInt(in.readLine());
        for (int i = 0; i < N; i++) {
            right[i] = Integer.parseInt(in.readLine());
            idToRightI[right[i]] = i;
        }
        in.close();

        BIT2D bit2d = new BIT2D(N);
        // Evaluate from bottom-up for easier counting
        long answer = 0;
        for (int i = N - 1; i >= 0; i--) {
            // y + 1 due to 1-indexing
            answer += bit2d.queryUnfriendly(idToRightI[left[i]] + 1, left[i]);
            bit2d.add(idToRightI[left[i]] + 1, left[i]);
        }

        out.println(answer);
        out.close();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("friendcross.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("friendcross.out")));
        new friendcross(in, out);
    }

    class BIT2D {
        int size;
        FieldHolder[] vals;

        BIT2D(int size) {
            this.size = size;
            vals = new FieldHolder[size + 1];
            // Init all vals
            for (int i = 1; i < size + 1; i++) {
                vals[i] = new FieldHolder(Integer.lowestOneBit(i));
            }
        }

        void add(int y, int id) {
            while (y <= size) {
                vals[y].add(id);
                y += Integer.lowestOneBit(y);
            }
        }

        // Returns the # of unfriendly fields ABOVE (<) the given y.
        int queryUnfriendly(int y, int id) {
            y--;
            int result = 0;
            while (y > 0) {
                result += vals[y].queryUnfriendly(id);
                y -= Integer.lowestOneBit(y);
            }
            return result;
        }
    }

    // Depending on size, will either be another BIT or just a naive field holder
    class FieldHolder {
        int size, numElements;
        int[] vals;
        ArrayList<Integer> fieldIDs;
        boolean isBIT;

        FieldHolder(int size) {
            this.size = size;
            isBIT = size >= MIN_BIT_SIZE;
            if (isBIT) {
                vals = new int[N + 1];
                numElements = 0;
            } else fieldIDs = new ArrayList<>(size);
        }

        void add(int id) {
            if (isBIT) {
                numElements++;
                while (id <= N) {
                    vals[id]++;
                    id += Integer.lowestOneBit(id);
                }
            } else {
                // Just add it naively
                fieldIDs.add(id);
            }
        }

        int queryUnfriendly(int id) {
            if (isBIT) {
                // Whole thing - part ending at last friendly + part ending before first friendly
                // = # of unfriendly
                return numElements - query(id + K) + query(id - K - 1);
            } else {
                // Iterate through each, and add to total
                int result = 0;
                for (int oid : fieldIDs) {
                    if (Math.abs(id - oid) > K) result++;
                }
                return result;
            }
        }

        // Queries # of elements in [0, id]. Assumes that a BIT is being used (which it is).
        int query(int id) {
            if (id > N) return numElements;
            int result = 0;
            while (id > 0) {
                result += vals[id];
                id -= Integer.lowestOneBit(id);
            }
            return result;
        }
    }
}
