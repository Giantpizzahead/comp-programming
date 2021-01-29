/*
Solution: Use a disjoint set, and evaluate squares from the bottom. When joining two sets, multiply
the # of ways to fill the squares with water (a * b = new # ways). Add 1 to the # of ways for all
sets inside the current row at the end (use HashSet to avoid duplicates).
Runtime: O(NM)
*/

import java.util.*;
import java.io.*;

public class cave {
    int N, M;
    char[][] grid;
    final int MOD = 1000000007;

    cave(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        grid = new char[N][];
        for (int y = 0; y < N; y++) {
            grid[y] = in.readLine().toCharArray();
        }

        DisjointSet ds = new DisjointSet(N * M);
        for (int y = N - 1; y >= 0; y--) {
            for (int x = 0; x < M; x++) {
                if (grid[y][x] == '#') continue;
                int h = hash(x, y);
                // Initialize current cell
                ds.numWays[h] = 1;
                ds.active[h] = true;
                // Merge with previous cells
                if (x != 0) ds.union(h, hash(x-1, y));
                if (y != N - 1) ds.union(h, hash(x, y+1));
            }

            // Add 1 to all current sets
            HashSet<Integer> seenSets = new HashSet<>();
            for (int x = 0; x < M; x++) {
                if (grid[y][x] == '#') continue;
                int h = hash(x, y);
                int cSet = ds.find(h);
                if (!seenSets.contains(cSet)) {
                    seenSets.add(cSet);
                    ds.numWays[cSet]++;
                }
            }

            // System.out.println(Arrays.toString(ds.numWays));
        }

        // Final answer is multiplication of all remaining disjoint sets
        long answer = 1;
        for (int i = 0; i < ds.size; i++) {
            if (ds.numWays[i] != 0) answer = answer * ds.numWays[i] % MOD;
        }
        out.println(answer);
    }

    int hash(int x, int y) {
        return y * M + x;
    }

    class DisjointSet {
        int size;
        int[] vals;
        boolean[] active;
        long[] numWays;

        DisjointSet(int size) {
            this.size = size;
            vals = new int[size];
            Arrays.fill(vals, -1);
            active = new boolean[size];
            numWays = new long[size];
        }

        int union(int a, int b) {
            if (!(active[a] && active[b])) return -1;  // Can't merge these
            int setA = find(a);
            int setB = find(b);
            if (setA == setB) return setA;

            if (vals[setA] < vals[setB]) {
                // Merge into setA
                numWays[setA] = numWays[setA] * numWays[setB] % MOD;
                numWays[setB] = 0;
                vals[setA] += vals[setB];
                vals[setB] = setA;
                return setA;
            } else {
                // Merge into setB
                numWays[setB] = numWays[setB] * numWays[setA] % MOD;
                numWays[setA] = 0;
                vals[setB] += vals[setA];
                vals[setA] = setB;
                return setB;
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
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("cave.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cave.out")));
        new cave(in, out);
        in.close();
        out.close();
    }
}
