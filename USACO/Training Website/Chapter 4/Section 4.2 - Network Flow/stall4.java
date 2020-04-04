/*
ID: sunnyky1
LANG: JAVA
TASK: stall4
Solution: This is a classic bipartite matching problem. Use Dinic's algorithm to find the maximum
matching in the fastest possible time.
Runtime: O(sqrt(N) * E)
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class stall4 {
    final int INF = 987654321;
    int actualN, N, M, source, sink;
    int[][] capacity;
    ArrayList<Integer>[] adj;

    stall4(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        actualN = N + M + 2;
        source = N + M;
        sink = N + M + 1;
        capacity = new int[actualN][actualN];
        adj = new ArrayList[actualN];
        for (int i = 0; i < actualN; i++) adj[i] = new ArrayList<>(2);
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            int S = Integer.parseInt(st.nextToken());
            for (int j = 0; j < S; j++) {
                int n = Integer.parseInt(st.nextToken()) - 1;
                adj[i].add(N + n);
                adj[N + n].add(i);
                capacity[i][N + n] = 1;
            }
        }
        // Add source and sink edges
        for (int i = 0; i < N; i++) {
            adj[source].add(i);
            adj[i].add(source);
            capacity[source][i] = 1;
        }
        for (int i = 0; i < M; i++) {
            adj[N + i].add(sink);
            adj[sink].add(N + i);
            capacity[N + i][sink] = 1;
        }

        // Run Dinic's algorithm
        int maxMatching = findMaxFlow();
        out.println(maxMatching);
    }

    int[] level;
    boolean[] visited;
    int findMaxFlow() {
        int currFlow = 0;
        while (true) {
            level = new int[actualN];
            Arrays.fill(level, INF);
            level[source] = 0;
            boolean sinkReached = buildLevelGraph();
            if (!sinkReached) break;
            while (true) {
                visited = new boolean[actualN];
                int bottleneck = findAugmentingPath(source, INF);
                if (bottleneck == -1) break;
                else currFlow += bottleneck;
            }
        }
        return currFlow;
    }

    int findAugmentingPath(int n, int bottleneck) {
        visited[n] = true;
        if (n == sink) return bottleneck;
        for (int e : adj[n]) {
            if (!visited[e] && level[n] + 1 == level[e] && capacity[n][e] != 0) {
                int result = findAugmentingPath(e, Math.min(capacity[n][e], bottleneck));
                if (result != -1) {
                    capacity[n][e] -= result;
                    capacity[e][n] += result;
                    return result;
                }
            }
        }
        return -1;
    }

    boolean buildLevelGraph() {
        Queue<Integer> q = new LinkedList<>();
        q.add(source);
        int currLeft = 1, nextLeft = 0, currLevel = 0;

        int c;
        while (!q.isEmpty()) {
            c = q.poll();
            if (currLeft == 0) {
                currLeft = nextLeft;
                nextLeft = 0;
                currLevel++;
            }
            currLeft--;
            for (int e : adj[c]) {
                if (level[e] == INF && capacity[c][e] != 0) {
                    level[e] = currLevel + 1;
                    nextLeft++;
                    q.add(e);
                }
            }
        }

        return level[sink] != INF;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("stall4.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("stall4.out")));
        new stall4(in, out);
        in.close();
        out.close();
    }
}