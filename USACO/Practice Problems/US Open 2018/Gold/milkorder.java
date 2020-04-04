/*
Solution: Binary search on the # of observations that can be followed. Simulate the current # of observations, seeing
if you can make a valid ordering. Once the max # of observations is found, simulate it again to make the best ordering,
using a priority queue instead of just a queue when adding new cows to the ordering.

Store the observations as directed edges, with recorded observation #s.

In a simulation:
First, iterate through all the edges and track the # of inedges for each node.
Then, find all the nodes with 0 inedges.
Now, while you can, pick a node with no inedges, and -1 from all cows that this node has an edge to. Add node to 0
inedge list if needed. Only check edges with observation # below or equal to target observation #.
If you can get through all cows using this, then return true. Else, return false.

Runtime: O((log M) * (N + 3E) + (N * log N + 3E))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class milkorder {
    int N, M;
    ArrayList<Edge>[] graph;

    milkorder() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(3);
        int numCows;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            numCows = Integer.parseInt(st.nextToken());
            int lastCow = Integer.parseInt(st.nextToken()) - 1;
            for (int j = 1; j < numCows; j++) {
                int currCow = Integer.parseInt(st.nextToken()) - 1;
                graph[lastCow].add(new Edge(currCow, i+1));
                lastCow = currCow;
            }
        }
        fin.close();

        // Binary search on the answer
        int low = 0;
        int high = M;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (check(mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }

        // System.out.println(low);

        // Find the actual answer
        int[] ordering = findOrdering(low);

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milkorder.out")));
        StringBuilder sb = new StringBuilder();
        for (int n : ordering) sb.append(n).append(' ');
        fout.println(sb.substring(0, sb.length() - 1));
        fout.close();
    }

    int[] findOrdering(int maxO) {
        // Generate # of inEdges
        // System.out.println(Arrays.deepToString(graph));
        int[] inEdges = new int[N];
        for (ArrayList<Edge> edges : graph) {
            for (Edge edge : edges) {
                if (edge.o <= maxO) inEdges[edge.n]++;
            }
        }
        // System.out.println(Arrays.toString(inEdges));

        // Find nodes with 0 inEdges
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int i = 0; i < N; i++) {
            if (inEdges[i] == 0) pq.add(i);
        }

        // Main loop
        int numNodesAdded = 0;
        int index = 0;
        int c;
        int[] ordering = new int[N];
        while (!pq.isEmpty()) {
            c = pq.poll();
            ordering[index] = c + 1;
            index++;
            // Minus 1 from inEdges for all c's neighbors
            for (Edge edge : graph[c]) {
                if (edge.o > maxO) break;
                inEdges[edge.n]--;
                if (inEdges[edge.n] == 0) pq.add(edge.n);
            }
        }

        return ordering;
    }

    boolean check(int maxO) {
        // Generate # of inEdges
        int[] inEdges = new int[N];
        for (ArrayList<Edge> edges : graph) {
            for (Edge edge : edges) {
                if (edge.o <= maxO) inEdges[edge.n]++;
            }
        }

        // Find nodes with 0 inEdges
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < N; i++) {
            if (inEdges[i] == 0) q.add(i);
        }

        // Main loop
        int numNodesAdded = 0;
        int c;
        while (!q.isEmpty()) {
            c = q.poll();
            numNodesAdded++;
            // Minus 1 from inEdges for all c's neighbors
            for (Edge edge : graph[c]) {
                if (edge.o > maxO) break;
                inEdges[edge.n]--;
                if (inEdges[edge.n] == 0) q.add(edge.n);
            }
        }

        return numNodesAdded == N;
    }

    public static void main(String[] args) throws IOException {
        new milkorder();
    }

    static class Edge {
        int n, o;
        Edge(int n, int o) {
            this.n = n;
            this.o = o;
        }

        @Override
        public String toString() {
            return "(" + n + ", " + o + ")";
        }
    }
}
