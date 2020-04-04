/*
ID: sunnyky1
LANG: JAVA
TASK: fence6

Solution: Create 2 nodes for each fence; a top node and a bottom node. Then, parse the
input by marking the adjacent fences for each top and bottom node (don't make actual
connections yet). Then, for each adjacent fence, look through that fence's adjacent
fences on its top node. If the current fence is found, this connects to the other fence's
top node; else it connects to the bottom node. Do this for all adjacent fences to create
a graph with 2N nodes (edge cost 0 for adjacent fences, edge cost L for top to bottom
node of the same fence). Finally, to find the shortest cycle (perimeter), try 'removing'
each edge, and find the shortest path between the 2 nodes that the edge connects. The
perimeter would be the shortest path length + the edge length.
Runtime: O((16N)^2 * log(16N))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class fence6 {
    final int INF = 987654321;
    int N, nodeN, E, bestPerimeter = INF;
    int[] topNode, botNode;
    int[][] topAdj, botAdj;
    ArrayList<EdgeInfo> edgeList = new ArrayList<>();
    ArrayList<Edge>[] adj;

    fence6(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        nodeN = N * 2;
        E = 0;
        topNode = new int[N];
        botNode = new int[N];
        topAdj = new int[N][];
        botAdj = new int[N][];
        for (int i = 0; i < N; i++) {
            topNode[i] = i * 2;
            botNode[i] = i * 2 + 1;
        }
        adj = new ArrayList[nodeN];
        for (int i = 0; i < nodeN; i++) adj[i] = new ArrayList<>(2);
        int s, l, n1, n2;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            s = Integer.parseInt(st.nextToken()) - 1;
            l = Integer.parseInt(st.nextToken());
            n1 = Integer.parseInt(st.nextToken());
            n2 = Integer.parseInt(st.nextToken());
            topAdj[s] = new int[n1];
            botAdj[s] = new int[n2];
            addEdge(topNode[s], botNode[s], l);
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < n1; j++) {
                int f = Integer.parseInt(st.nextToken()) - 1;
                topAdj[s][j] = f;
            }
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < n2; j++) {
                int f = Integer.parseInt(st.nextToken()) - 1;
                botAdj[s][j] = f;
            }
        }

        // Generate graph by linking adjacent fences at the right nodes
        for (int i = 0; i < N; i++) {
            for (int f : topAdj[i]) {
                boolean isTop = false;
                for (int g : topAdj[f]) {
                    if (g == i) {
                        isTop = true;
                        break;
                    }
                }
                if (isTop) {
                    // Top to top connection
                    addEdge(topNode[i], topNode[f], 0);
                } else {
                    // Top to bottom connection
                    addEdge(topNode[i], botNode[f], 0);
                }
            }
            for (int f : botAdj[i]) {
                boolean isTop = false;
                for (int g : topAdj[f]) {
                    if (g == i) {
                        isTop = true;
                        break;
                    }
                }
                if (isTop) {
                    // Bottom to top connection
                    addEdge(botNode[i], topNode[f], 0);
                } else {
                    // Bottom to bottom connection
                    addEdge(botNode[i], botNode[f], 0);
                }
            }
        }

        // Remove each edge to try and form the shortest cycle possible
        bestDist = new int[nodeN];
        pq = new PriorityQueue<>(new Comparator<State>() {
            @Override
            public int compare(State o1, State o2) {
                return o1.c - o2.c;
            }
        });
        for (int i = 0; i < E; i++) {
            EdgeInfo e = edgeList.get(i);
            if (e.c == 0) continue;
            ignoreEdgeID = i;
            pruneDist = bestPerimeter - e.c;
            bestPerimeter = Math.min(dijkstra(e.a, e.b) + e.c, bestPerimeter);
        }
        out.println(bestPerimeter);
    }

    int ignoreEdgeID, pruneDist;
    int[] bestDist;
    PriorityQueue<State> pq;
    int dijkstra(int start, int end) {
        Arrays.fill(bestDist, INF);
        bestDist[start] = 0;
        pq.clear();
        pq.add(new State(start, 0));

        State c;
        while (!pq.isEmpty()) {
            c = pq.poll();
            if (c.c != bestDist[c.n]) continue;
            if (c.n == end) return c.c;
            for (Edge e : adj[c.n]) {
                if (e.id == ignoreEdgeID) continue;
                int nc = c.c + e.c;
                if (nc < bestDist[e.n] && nc < pruneDist) {
                    bestDist[e.n] = nc;
                    pq.add(new State(e.n, nc));
                }
            }
        }
        return INF;
    }

    void addEdge(int a, int b, int c) {
        adj[a].add(new Edge(b, c, E));
        adj[b].add(new Edge(a, c, E++));
        edgeList.add(new EdgeInfo(a, b, c));
    }

    static class Edge {
        int n, c, id;
        Edge(int n, int c, int id) {
            this.n = n;
            this.c = c;
            this.id = id;
        }
    }

    static class EdgeInfo {
        int a, b, c;
        EdgeInfo(int a, int b, int c) {
            this.a = a;
            this.b = b;
            this.c = c;
        }
    }

    static class State {
        int n, c;
        State(int n, int c) {
            this.n = n;
            this.c = c;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("fence6.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fence6.out")));
        new fence6(in, out);
        in.close();
        out.close();
    }
}
