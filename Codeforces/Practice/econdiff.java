/*
Solution: First, find the range of devices that each node covers (if that node were
the root of the tree, what is the range of devices that its children could reach?).
Then, each node represents a 'bonus' of sorts for using the opposite grid's edges
for that node's entire range. Find these bonuses for each grid, and record them
in a N^2 sized matrix (best bonus for [a, b] on either grid).

Now, do DP on the devices connected. dp[i] = Maximum # of wires that can be removed
while connecting all devices [0, i) to either of the grids.
BC: dp[0] = 0
Trans: dp[i] = max for j=0...i-1 (dp[j] + bonus[j][i-1]) (Try to take advantage of
all the bonuses)
Answer: dp[N]

Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class econdiff {
    int N, A;
    int[] minDevice, maxDevice, numEdges;
    int[][] bonus;
    ArrayList<Integer>[] adj;
    final int INF = 98765432;

    econdiff(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        bonus = new int[N][N];
        // Process both grids the same way
        for (int i = 0; i < 2; i++) {
            st = new StringTokenizer(in.readLine());
            A = Integer.parseInt(st.nextToken());
            adj = new ArrayList[A];
            for (int j = 0; j < A; j++) adj[j] = new ArrayList<>(2);
            st = new StringTokenizer(in.readLine());
            int a;
            for (int j = 1; j < A; j++) {
                a = Integer.parseInt(st.nextToken()) - 1;
                adj[j].add(a);
                adj[a].add(j);
            }
            minDevice = new int[A];
            maxDevice = new int[A];
            numEdges = new int[A];
            Arrays.fill(minDevice, -1);
            Arrays.fill(maxDevice, -1);
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < N; j++) {
                a = Integer.parseInt(st.nextToken()) - 1;
                minDevice[a] = j;
                maxDevice[a] = j;
            }
            evalGrid(0, 0);
            bonus[0][N-1] = Math.max(numEdges[0], bonus[0][N-1]);
        }

        // for (int i = 0; i < N; i++) System.out.println(Arrays.toString(bonus[i]));

        // Now do a simple DP
        int[] dp = new int[N + 1];
        dp[0] = 0;
        for (int i = 1; i <= N; i++) {
            int newDP = -INF;
            for (int j = 0; j < i; j++) {
                newDP = Math.max(dp[j] + bonus[j][i-1], newDP);
            }
            dp[i] = newDP;
        }
        out.println(dp[N]);
    }

    void evalGrid(int n, int p) {
        if (minDevice[n] != -1) {
            // This is a leaf node
            return;
        }

        int mind = INF, maxd = -INF, edges = 0;
        for (int e : adj[n]) {
            if (e != p) {
                evalGrid(e, n);
                mind = Math.min(minDevice[e], mind);
                maxd = Math.max(maxDevice[e], maxd);
                edges += numEdges[e] + 1;

                // Set bonus for child node
                bonus[minDevice[e]][maxDevice[e]] = Math.max(numEdges[e] + 1, bonus[minDevice[e]][maxDevice[e]]);
            }
        }

        minDevice[n] = mind;
        maxDevice[n] = maxd;
        numEdges[n] = edges;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        // BufferedReader in = new BufferedReader(new FileReader("econdiff.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("econdiff.out")));
        new econdiff(in, out);
        in.close();
        out.close();
    }
}