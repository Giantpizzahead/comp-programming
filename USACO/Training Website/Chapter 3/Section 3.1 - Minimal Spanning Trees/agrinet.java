/*
ID: sunnyky1
LANG: JAVA
TASK: agrinet

Solution: Standard MST implementation. Use Prim's algorithm.

Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

public class agrinet {
    int N;
    int[][] graph;
    final int INF = 987654321;

    agrinet() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("agrinet.in"));
        StreamTokenizer st = new StreamTokenizer(fin);
        st.nextToken();
        N = (int) st.nval;
        graph = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                st.nextToken();
                graph[i][j] = (int) st.nval;
            }
        }
        fin.close();

        int answer = findMST();
        PrintWriter fout = new PrintWriter("agrinet.out");
        fout.println(answer);
        fout.close();
    }

    int findMST() {
        int[] bestDist = new int[N];
        Arrays.fill(bestDist, INF);
        bestDist[0] = 0;
        boolean[] visited = new boolean[N];

        int c = 0, cost = 0;
        for (int i = 0; i < N; i++) {
            visited[c] = true;
            cost += bestDist[c];
            for (int j = 0; j < N; j++) {
                if (!visited[j]) bestDist[j] = Math.min(graph[c][j], bestDist[j]);
            }

            // Find next node
            int minCost = INF;
            for (int j = 0; j < N; j++) {
                if (!visited[j] && bestDist[j] < minCost) {
                    c = j;
                    minCost = bestDist[j];
                }
            }
        }

        return cost;
    }

    public static void main(String[] args) throws IOException {
        new agrinet();
    }
}