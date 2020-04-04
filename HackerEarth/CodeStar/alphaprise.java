package CodeStar;/*
Solution: Treat reverse edges as - values, and regular edges as + values.
*/

import java.util.*;
import java.io.*;

public class alphaprise {
    int N, M, startNode;
    int[] locs;
    int[][] graph;
    HashSet<Integer> usedNodes;
    final int INF = 999999999;

    alphaprise() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        M = Integer.parseInt(st.nextToken());
        N = 200;
        graph = new int[N][N];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i != j) graph[i][j] = INF;
            }
        }

        usedNodes = new HashSet<>();
        int x, y, z;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            x = Integer.parseInt(st.nextToken()) - 1;
            y = Integer.parseInt(st.nextToken()) - 1;
            z = Integer.parseInt(st.nextToken());
            graph[x][y] = z;
            graph[y][x] = -z;
            usedNodes.add(x);
            usedNodes.add(y);
            if (i == 0) startNode = x;
        }

        doBFS();

        // Output in the right format
        // System.out.println(Arrays.toString(locs));
        Integer[] sorted = new Integer[N];
        for (int i = 0; i < N; i++) sorted[i] = i;
        Arrays.sort(sorted, new Comparator<Integer>() {
            @Override
            public int compare(Integer a, Integer b) {
                return locs[a] - locs[b];
            }
        });

        int prevValue = -INF;
        int printNext = sorted[0];
        ArrayList<Integer> toPrint = new ArrayList<>();
        for (int i = 1; i < N; i++) {
            if (locs[sorted[i]] == INF) break;
            if (locs[sorted[i]] != prevValue) {
                for (int n : toPrint) System.out.print((n + 1) + " ");
                toPrint.clear();
                System.out.println(printNext + 1);
                prevValue = locs[sorted[i]];
                printNext = sorted[i];
            } else {
                toPrint.add(printNext);
                printNext = sorted[i];
            }
        }

        // Final print
        for (int n : toPrint) System.out.print((n + 1) + " ");
        System.out.println(printNext + 1);

        in.close();
    }

    void doBFS() {
        Queue<Integer> q = new LinkedList<>();
        q.add(startNode);
        locs = new int[N];
        for (int i = 0; i < N; i++) locs[i] = INF;
        locs[startNode] = 0;
        boolean[] visited = new boolean[N];
        visited[startNode] = true;

        int c;
        while (!q.isEmpty()) {
            c = q.poll();
            // Iterate through neighbors
            for (int n = 0; n < N; n++) {
                if (c != n && !visited[n] && !(graph[c][n] == INF)) {
                    locs[n] = locs[c] + graph[c][n];
                    q.add(n);
                    visited[n] = true;
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        new alphaprise();
    }
}
