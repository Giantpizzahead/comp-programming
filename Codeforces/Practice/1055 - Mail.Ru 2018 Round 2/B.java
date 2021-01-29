/*
Solution: Standard DSU problem... but it doesn't even have to be solved with DSU! I'm gonna use it
anyway, but the # of sets decreases by one anytime the left and right are both taller than l.
Runtime: O(N)
*/

import java.util.*;
import java.io.*;

public class hairdresser {
    int N, M, L;
    long[] hairs;

    hairdresser(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        L = Integer.parseInt(st.nextToken());
        hairs = new long[N];
        st = new StringTokenizer(in.readLine());
        DisjointSet ds = new DisjointSet(N);
        for (int i = 0; i < N; i++) {
            hairs[i] = Integer.parseInt(st.nextToken());
            if (hairs[i] > L) {
                ds.activate(i);
            }
        }

        int a, b, c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken());
            if (a == 0) {
                // Query
                out.println(ds.numSets);
            } else {
                // Hair growth
                b = Integer.parseInt(st.nextToken()) - 1;
                c = Integer.parseInt(st.nextToken());
                if (hairs[b] <= L && hairs[b] + c > L) {
                    // Changes state
                    ds.activate(b);
                }
                hairs[b] += c;
            }
        }
    }

    static class DisjointSet {
        int size, numSets = 0;
        int[] vals;
        boolean[] active;

        DisjointSet(int size) {
            this.size = size;
            vals = new int[size];
            active = new boolean[size];
            Arrays.fill(vals, -1);
        }

        void union(int a, int b) {
            if (b < 0 || b > size - 1 || !active[b]) return;
            int setA = find(a);
            int setB = find(b);
            if (setA == setB) return;

            numSets--;
            if (vals[setA] < vals[setB]) {
                vals[setA] += vals[setB];
                vals[setB] = setA;
            } else {
                vals[setB] += vals[setA];
                vals[setA] = setB;
            }
        }

        int find(int i) {
            if (vals[i] < 0) return i;
            else {
                int res = find(vals[i]);
                vals[i] = res;
                return res;
            }
        }

        void activate(int i) {
            active[i] = true;
            numSets++;
            union(i, i-1);
            union (i, i+1);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("hairdresser.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("hairdresser.out")));
        new hairdresser(in, out);
        in.close();
        out.close();
    }
}
