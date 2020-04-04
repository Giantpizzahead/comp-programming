/*
ID: sunnyky1
LANG: JAVA
TASK: comehome

Solution: There are only 52 nodes, so just store the barns in an adjacency
matrix, run Floyd Warshall on it, and find the minimum distance from A-Y to Z.

Runtime: O(N^3)
*/

import java.util.*;
import java.io.*;

public class comehome {
    int P, N = 52;
    int[][] graph;
    final int INF = 987654321;

    comehome() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("comehome.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        P = Integer.parseInt(st.nextToken());
        // Graph stored as a-z, then A-Z
        graph = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i != j) graph[i][j] = INF;
            }
        }
        char a, b;
        int ai, bi, c;
        for (int i = 0; i < P; i++) {
            st = new StringTokenizer(fin.readLine());
            a = st.nextToken().charAt(0);
            b = st.nextToken().charAt(0);
            c = Integer.parseInt(st.nextToken());
            if (a >= 'a') ai = a - 'a';
            else ai = a - 39;
            if (b >= 'a') bi = b - 'a';
            else bi = b - 39;
            graph[ai][bi] = Math.min(c, graph[ai][bi]);
            graph[bi][ai] = Math.min(c, graph[bi][ai]);
        }
        fin.close();
        
        // Floyd Warshall
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
                }
            }
        }

        // Output shortest
        int shortestDist = INF, shortestI = -1;
        for (int i = 26; i < N-1; i++) {
            if (graph[i][N-1] < shortestDist) {
                shortestI = i;
                shortestDist = graph[i][N-1];
            }
        }

        PrintWriter fout = new PrintWriter("comehome.out");
        fout.print((char) (shortestI + 39));
        fout.print(' ');
        fout.println(shortestDist);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new comehome();
    }
}