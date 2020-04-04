/*
ID: sunnyky1
LANG: JAVA
TASK: cowtour

Solution: First, Floyd Warshall to find the APSP of the graph (N^3). Then, find the connected components of the graph,
and find the diameter of each individual component.

Next, try connecting every pair of pastures (N^2). To evaluate the new diameter, either the diameter goes through the
newly created path, or it doesn't. If it doesn't, then the diameter is just the max of the 2 component diameters. If it
does go through, then the diameter is max(Distance from any node in component to node 1 used in the path) + Path length
+ max(Dist from component to node 2). These can both be calculated in linear time. Finally, output the minimum of all
these diameters.

Runtime: O(2 * N^3)
*/

import java.util.*;
import java.io.*;

public class cowtour {
    int N;
    Point[] pastures;
    int[] pastureID;
    double[] diameters;
    double[][] graph;
    final double INF = 1_000_000_000_000D;

    cowtour() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cowtour.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        pastures = new Point[N];
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            pastures[i] = new Point(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
        }

        // Generate adjacency matrix
        graph = new double[N][N];
        for (int i = 0; i < N; i++) Arrays.fill(graph[i], INF);
        for (int i = 0; i < N; i++) {
            String line = fin.readLine();
            for (int j = 0; j < N; j++) {
                // Only set edge if it actually exists
                if (line.charAt(j) == '1') {
                    graph[i][j] = dist(i, j);
                } else if (i == j) graph[i][j] = 0;
            }
        }
        fin.close();

        floydWarshall();

//        for (int i = 0; i < N; i++) {
//            System.out.println(Arrays.toString(graph[i]));
//        }

        findDiameters();

//        System.out.println(Arrays.toString(diameters));

        double answer = INF;
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                if (pastureID[i] != pastureID[j]) answer = Math.min(makeDiameter(i, j), answer);
            }
        }

        PrintWriter fout = new PrintWriter("cowtour.out");
        fout.printf("%.6f\n", answer);
        fout.close();
    }

    double makeDiameter(int a, int b) {
        // Case 1: Diameter does not cross new edge
        double diameter = Math.max(diameters[a], diameters[b]);

        // Case 2: Diameter crosses new edge
        double bestA = 0, bestB = 0;
        for (int i = 0; i < N; i++) {
            if (graph[a][i] != INF) bestA = Math.max(graph[a][i], bestA);
            if (graph[b][i] != INF) bestB = Math.max(graph[b][i], bestB);
        }

        diameter = Math.max(bestA + dist(a, b) + bestB, diameter);
        return diameter;
    }

    void findDiameters() {
        boolean[] visited = new boolean[N];
        diameters = new double[N];
        pastureID = new int[N];
        for (int i = 0; i < N; i++) {
            if (!visited[i]) explore(i, visited);
        }
    }

    void explore(int start, boolean[] visited) {
        ArrayList<Integer> nodes = new ArrayList<>();
        nodes.add(start);
        visited[start] = true;
        Queue<Integer> q = new LinkedList<>();
        q.add(start);
        int c;
        while (!q.isEmpty()) {
            c = q.poll();
            for (int i = 0; i < N; i++) {
                if (graph[c][i] != INF && !visited[i]) {
                    visited[i] = true;
                    nodes.add(i);
                    q.add(i);
                }
            }
        }

        // Find the diameter
        double maxDiameter = 0;
        for (int i = 0; i < nodes.size(); i++) {
            for (int j = i; j < nodes.size(); j++) {
                if (graph[nodes.get(i)][nodes.get(j)] != INF) {
                    maxDiameter = Math.max(graph[nodes.get(i)][nodes.get(j)], maxDiameter);
                }
            }
        }

        // Record the diamater
        for (int n : nodes) {
            diameters[n] = maxDiameter;
            pastureID[n] = start;
        }
    }

    void floydWarshall() {
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
                }
            }
        }
    }

    double dist(int i, int j) {
        return Math.sqrt(Math.pow(Math.abs(pastures[i].x - pastures[j].x), 2) +
                         Math.pow(Math.abs(pastures[i].y - pastures[j].y), 2));
    }

    public static void main(String[] args) throws IOException {
        new cowtour();
    }

    class Point {
        int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}
