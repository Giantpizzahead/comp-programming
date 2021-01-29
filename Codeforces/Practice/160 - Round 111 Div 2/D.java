/*
Solution: Use Kruskal's algorithm (DSU) to make the MST. Handle all edges with the same weight at
one time, making a separate graph with the DSU sets the edges connect. If the edge is a bridge in
this new graph, then it's used in all MSTs; otherwise it's used in at least one MST. If an edge
connects a set to itself, then it's useless / is not included in any MST.
Runtime: O(M * log(M))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class mstedges {
    final int MAXW = 1000001;
    int N, M;
    int[] answers;
    ArrayList<Edge>[] edges;
    DisjointSet ds;

    mstedges(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        edges = new ArrayList[MAXW];
        for (int i = 0; i < MAXW; i++) edges[i] = new ArrayList<>(2);
        int a, b, w;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            w = Integer.parseInt(st.nextToken());
            edges[w].add(new Edge(a, b, w, i));
        }

        // Evaluate edges in order
        answers = new int[M];
        ds = new DisjointSet(N);
        for (int i = 0; i < MAXW; i++) {
            if (edges[i].size() != 0) evalStage(edges[i]);
        }

        for (int ans : answers) {
            if (ans == 0) out.println("any");
            else if (ans == 1) out.println("at least one");
            else out.println("none");
        }
    }

    void evalStage(ArrayList<Edge> edges) {
        int tempN = 0;
        HashMap<Integer, Integer> setToI = new HashMap<>();
        // Create a new graph
        for (Edge e : edges) {
            int setA = ds.find(e.a);
            int setB = ds.find(e.b);
            e.a = setA;
            e.b = setB;
            if (!setToI.containsKey(setA)) {
                setToI.put(setA, tempN++);
            }
            if (!setToI.containsKey(setB)) {
                setToI.put(setB, tempN++);
            }
        }

        adj = new ArrayList[tempN];
        for (int i = 0; i < tempN; i++) adj[i] = new ArrayList<>(2);
        int numEdges = 0;
        for (Edge e : edges) {
            // System.out.println(e.a + " " + e.b);
            // Actually merge them now
            ds.union(e.a, e.b);
            e.a = setToI.get(e.a);
            e.b = setToI.get(e.b);
            if (e.a == e.b) {
                // Connects same set; will never be used
                answers[e.origI] = 2;
            } else {
                // Add to temp graph
                adj[e.a].add(new TempEdge(e.b, numEdges, e.origI));
                adj[e.b].add(new TempEdge(e.a, numEdges++, e.origI));
            }
        }

        // Find bridges in this graph
        usedEdge = new boolean[numEdges];
        disc = new int[tempN];
        ll = new int[tempN];
        currDisc = 1;
        for (int i = 0; i < tempN; i++) findBridges(i);
    }

    int currDisc = 1;
    ArrayList<TempEdge>[] adj;
    int[] disc, ll;
    boolean[] usedEdge;
    void findBridges(int n) {
        disc[n] = currDisc++;
        ll[n] = disc[n];
        for (TempEdge e : adj[n]) {
            if (usedEdge[e.i]) continue;
            usedEdge[e.i] = true;
            if (disc[e.n] == 0) {
                // Node not yet visited
                findBridges(e.n);
                if (ll[e.n] > disc[n]) {
                    // This is a bridge
                    answers[e.origI] = 0;
                    // System.out.println(e.origI + " bridge");
                } else {
                    // Not a bridge
                    answers[e.origI] = 1;
                }
                ll[n] = Math.min(ll[e.n], ll[n]);
            } else {
                // Node already visited (not a bridge)
                answers[e.origI] = 1;
                ll[n] = Math.min(disc[e.n], ll[n]);
            }
        }
    }

    class TempEdge {
        int n, i, origI;
        TempEdge(int n, int i, int origI) {
            this.n = n;
            this.i = i;
            this.origI = origI;
        }
    }

    class Edge {
        int a, b, w, origI;
        Edge(int a, int b, int w, int origI) {
            this.a = a;
            this.b = b;
            this.w = w;
            this.origI = origI;
        }
    }

    class DisjointSet {
        int size;
        int[] vals;

        DisjointSet(int size) {
            this.size = size;
            vals = new int[size];
            Arrays.fill(vals, -1);
        }

        void union(int a, int b) {
            int setA = find(a);
            int setB = find(b);
            if (setA == setB) return;

            if (vals[setA] < vals[setB]) {
                vals[setA] += vals[setB];
                vals[setB] = setA;
            } else {
                vals[setB] += vals[setA];
                vals[setA] = setB;
            }
        }

        int find(int i) {
            if (vals[i] < 0) return i;
            else {
                int res = find(vals[i]);
                vals[i] = res;
                return res;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        // BufferedReader in = new BufferedReader(new FileReader("mstedges.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("mstedges.out")));
        new mstedges(in, out);
        in.close();
        out.close();
    }
}
