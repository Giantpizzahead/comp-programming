import java.util.*;
import java.io.*;

public class cave {
    final int MOD = 1000000007;
    int N, M;
    char[][] grid;
    DisjointSet ds;

    cave(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        grid = new char[N][];
        for (int i = 0; i < N; i++) grid[i] = in.readLine().toCharArray();

        ds = new DisjointSet(N * M);
        for (int y = N-1; y >= 0; y--) {
            for (int x = 0; x < M; x++) {
                if (grid[y][x] == '#') continue;
                int id = hash(x, y);
                ds.activate(id);
                if (y != N-1) {
                    int ny = y + 1;
                    ds.union(id, hash(x, ny));
                }
                if (x != 0) {
                    int nx = x - 1;
                    ds.union(id, hash(nx, y));
                }
            }
            // Add 1 to each numWays
            HashSet<Integer> seen = new HashSet<>();
            for (int x = 0; x < M; x++) {
                if (grid[y][x] == '#') continue;
                int id = ds.find(hash(x, y));
                if (!seen.contains(id)) {
                    seen.add(id);
                    ds.numWays[id] = (ds.numWays[id] + 1) % MOD;
                }
            }
        }

        // Final calculation
        int answer = 1;
        for (int i = 0; i < N * M; i++) {
            if (ds.numWays[i] != 0) answer = (int) ((long) answer * ds.numWays[i] % MOD);
        }
        out.println(answer);
    }

    int hash(int x, int y) {
        return x + y * M;
    }

    class DisjointSet {
        int size;
        int[] vals;
        int[] numWays;
        boolean[] isActive;

        DisjointSet(int size) {
            this.size = size;
            vals = new int[size];
            Arrays.fill(vals, -1);
            numWays = new int[size];
            isActive = new boolean[size];
        }

        void union(int a, int b) {
            if (!(isActive[a] && isActive[b])) return;
            int setA = find(a);
            int setB = find(b);
            if (setA == setB) return;

            if (vals[setA] < vals[setB]) {
                numWays[setA] = (int) ((long) numWays[setA] * numWays[setB] % MOD);
                numWays[setB] = 0;
                vals[setA] += vals[setB];
                vals[setB] = setA;
            } else {
                numWays[setB] = (int) ((long) numWays[setB] * numWays[setA] % MOD);
                numWays[setA] = 0;
                vals[setB] += vals[setA];
                vals[setA] = setB;
            }
        }

        void activate(int i) {
            numWays[i] = 1;
            isActive[i] = true;
        }

        int find(int i) {
            if (vals[i] < 0) return i;
            else {
                int result = find(vals[i]);
                vals[i] = result;
                return result;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("cave.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cave.out")));
        new cave(in, out);
        in.close();
        out.close();
    }
}
