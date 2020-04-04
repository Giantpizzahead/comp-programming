/*
Solution: Generate all the subarrays of the possible distances that you can
make by choosing two meadows in each farm. Then, treat the rest as a DP problem.

Clearer picture of DP:
All the things must be included, so that makes this a lot easier.
Yeah ok, let's do this.
*/

import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class mooriokartbetter {
    int N, M, X, Y;
    ArrayList<int[]> arrays;
    ArrayList<Edge>[] graph;

    mooriokartbetter() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("dining.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        X = Integer.parseInt(st.nextToken());
        Y = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        int a, b, c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken());
            graph[a].add(new Edge(b, c));
            graph[b].add(new Edge(a, c));
        }
        fin.close();

        // Generate the subarrays
        genArrays();

        /*
        for (int[] arr : arrays) {
            System.out.println(Arrays.toString(arr));
        }
        */

        // Do the DP
        long answer = doDP();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("mooriokart.out")));
        fout.println(answer);
        fout.close();
    }

    long doDP() {
        int numArrays = arrays.size();
        // dp at index Y is for dpOver only
        long[][] dp = new long[numArrays][Y+1];
        int indexToAdd;
        for (int i = 0; i < Y; i++) {
            indexToAdd = Math.min(i+X, Y);
            if (indexToAdd != Y) {
                dp[0][indexToAdd] += arrays.get(0)[i];
            } else {
                // Add sum of tracks, not # of ways
                dp[0][indexToAdd] += arrays.get(0)[i] * (i + X);
            }
        }
        dp[0][Y] = arrays.get(0)[Y];

        // Main DP loop
        for (int i = 0; i < numArrays - 1; i++) {
            for (int j = 0; j < Y+1; j++) {
                for (int k = 0; k < Y+1; k++) {
                    indexToAdd = Math.min(j + k + X, Y);
                    if (indexToAdd != Y) {
                        // Multiply by 2 to simulate being able to connect both sides of a farm
                        dp[i + 1][indexToAdd] += dp[i][j] * arrays.get(i + 1)[k] * 2;
                    } else {
                        // Add sum of tracks, not # of ways
                        // if (arrays.get(i+1)[k] != 0 && dp[i][j] != 0) System.out.println(j + k + X);
                        dp[i + 1][indexToAdd] += (dp[i][j] * arrays.get(i + 1)[k]) * 2 * (j + k + X);
                    }
                    dp[i + 1][indexToAdd] %= 1000000007;
                }
            }
        }

        // System.out.println(Arrays.deepToString(dp));

        return dp[numArrays - 1][Y];
    }

    /*
    Nothing special here, just generate all the subarrays with a simple DFS.
     */
    void genArrays() {
        boolean[] visited = new boolean[N];
        arrays = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                // Start BFS
                arrays.add(__genArrays(i, visited));
            }
        }
    }

    int[] __genArrays(int start, boolean[] visited) {
        Queue<Integer> q = new LinkedList<>();
        q.add(start);
        int c;
        ArrayList<Integer> inFarm = new ArrayList<>();
        HashMap<Integer, Integer> nodeToIndex = new HashMap<>();
        visited[start] = true;
        // Find all nodes in this farm
        while (!q.isEmpty()) {
            c = q.poll();
            nodeToIndex.put(c, inFarm.size());
            inFarm.add(c);
            for (Edge e : graph[c]) {
                if (!visited[e.n]) {
                    visited[e.n] = true;
                    q.add(e.n);
                }
            }
        }

        // The simplest way to generate the required array is by doing N
        // Dijkstras, so do that
        // Note: Index Y represents everything >=Y
        int[] currArr = new int[Y + 1];
        for (int s : inFarm) {
            boolean[] bfsVisited = new boolean[inFarm.size()];
            bfsVisited[nodeToIndex.get(s)] = true;
            Queue<Edge> sq = new LinkedList<>();
            sq.add(new Edge(s, 0));
            Edge curr;
            while (!sq.isEmpty()) {
                curr = sq.poll();
                if (curr.c >= Y) {
                    // Add sum of tracks to over
                    currArr[Y] += curr.c + X;
                } else {
                    currArr[curr.c]++;
                }
                for (Edge e : graph[curr.n]) {
                    if (!bfsVisited[nodeToIndex.get(e.n)]) {
                        bfsVisited[nodeToIndex.get(e.n)] = true;
                        sq.add(new Edge(e.n,curr.c + e.c));
                    }
                }
            }
        }

        // Remove costs with only one node
        currArr[0] -= inFarm.size();

        // Divide everything by 2 (BFS double counts)
        for (int i = 0; i < currArr.length; i++) {
            currArr[i] /= 2;
        }

        return currArr;
    }

    public static void main(String[] args) throws IOException {
        new mooriokartbetter();
    }

    static class Edge {
        int n, c;
        Edge(int n, int c) {
            this.n = n;
            this.c = c;
        }
    }
}
