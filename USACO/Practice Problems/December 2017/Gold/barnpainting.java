/*
Solution: DP with the # of ways to paint a node's subtree, with the current node painted as R, G, or B.
This is equal to the multiplication of (sum of other 2 colors) of all child nodes. If the current node is colored, set
the other 2 color # ways to 0. BC for leafs is [1, 1, 1], removing # ways if colored.

Runtime: O(N)
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class barnpainting {
    int N, K;
    long[][] dp;
    int[] color;
    ArrayList<Integer>[] graph;
    final long MOD = 1000000007;

    barnpainting() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("barnpainting.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        color = new int[N];
        Arrays.fill(color, -1);
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graph[a].add(b);
            graph[b].add(a);
        }
        for (int i = 0; i < K; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            color[a] = b;
        }
        fin.close();
        // System.out.println(Arrays.toString(color));

        // Do the DP
        dp = new long[N][3];
        go(0, 0);

        long answer = 0;
        for (int i = 0; i < 3; i++) answer += dp[0][i];
        answer %= MOD;
        // System.out.println(Arrays.deepToString(dp));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("barnpainting.out")));
        fout.println(answer);
        fout.close();
    }

    void go(int n, int p) {
        // First, do dp on child nodes
        boolean isChild = true;
        for (int e : graph[n]) {
            if (e != p) {
                go(e, n);
                isChild = false;
            }
        }

        if (isChild) {
            // Set dp to base case
            for (int i = 0; i < 3; i++) dp[n][i] = 1;
        } else {
            // Combine dp values of children
            for (int i = 0; i < 3; i++) {
                long currMult = 1;
                for (int e : graph[n]) {
                    if (e != p) {
                        long sum = 0;
                        for (int j = 0; j < 3; j++) if (i != j) sum += dp[e][j];
                        currMult = (currMult * sum) % MOD;
                    }
                }
                dp[n][i] = currMult;
            }
        }

        // If node is colored, remove required values
        if (color[n] != -1) {
            for (int i = 0; i < 3; i++) if (color[n] != i) dp[n][i] = 0;
        }
    }

    public static void main(String[] args) throws IOException {
        new barnpainting();
    }
}