import java.util.*;
import java.io.*;

public class hopscotch {
    final int MOD = 1000000007;
    int R, C, K;
    int[][] grid;
    int[] count;
    BIT totalBIT;
    BIT[] bits;

    hopscotch(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        grid = new int[R][C];
        count = new int[K];
        for (int i = 0; i < R; i++) {
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < C; j++) {
                grid[i][j] = Integer.parseInt(st.nextToken()) - 1;
                count[grid[i][j]]++;
            }
        }

        // Generate BITs
        totalBIT = new BIT(C, R*C);
        bits = new BIT[K];
        for (int i = 0; i < K; i++) bits[i] = new BIT(C, count[i]);

        // Do optimized DP
        Stack<Insert> toAdd = new Stack<>();
        int answer = -1;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                int currWays = totalBIT.query(j) - bits[grid[i][j]].query(j);
                if (currWays < 0) currWays += MOD;
                if (i == 0 && j == 0) currWays = 1;  // Base case
                else if (i == R - 1 && j == C - 1) answer = currWays;  // Answer found
                // Transition to bottom-right square
                toAdd.push(new Insert(j+1, C-1, grid[i][j], currWays));
            }
            while (!toAdd.isEmpty()) {
                Insert insert = toAdd.pop();
                totalBIT.add(insert.l, insert.r, insert.v);
                bits[insert.id].add(insert.l, insert.r, insert.v);
            }
        }
        out.println(answer);
    }

    static class Insert {
        int l, r, id, v;
        Insert(int l, int r, int id, int v) {
            this.l = l;
            this.r = r;
            this.id = id;
            this.v = v;
        }
    }

    class BIT {
        final int MIN_BIT_SIZE = 30;
        int size;
        int[] vals;
        ArrayList<Range> ranges;
        boolean isBIT;

        BIT(int size, int numInserts) {
            this.size = size;
            isBIT = (numInserts >= MIN_BIT_SIZE);
            if (isBIT) vals = new int[size + 1];
            else ranges = new ArrayList<>(numInserts);
        }

        void add(int l, int r, int v) {
            if (l > r) return;
            l++;
            r++;
            if (isBIT) {
                add0(l, v);
                add0(r + 1, -v);
            } else ranges.add(new Range(l, r, v));
        }

        void add0(int i, int v) {
            while (i <= size) {
                vals[i] = (vals[i] + v) % MOD;
                if (vals[i] < 0) vals[i] += MOD;
                i += Integer.lowestOneBit(i);
            }
        }

        int query(int i) {
            i++;
            int result = 0;
            if (isBIT) {
                while (i > 0) {
                    result = (result + vals[i]) % MOD;
                    i -= Integer.lowestOneBit(i);
                }
            } else {
                for (Range r : ranges) {
                    if (r.l <= i && r.r >= i) result = (result + r.v) % MOD;
                }
            }
            if (result < 0) result += MOD;
            return result;
        }
    }

    static class Range {
        int l, r, v;
        Range(int l, int r, int v) {
            this.l = l;
            this.r = r;
            this.v = v;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("hopscotch.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("hopscotch.out")));
        new hopscotch(in, out);
        in.close();
        out.close();
    }
}
