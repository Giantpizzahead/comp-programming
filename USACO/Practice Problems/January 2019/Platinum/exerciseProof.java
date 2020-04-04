/*
Solution: The key realization is that any 2 non-standard trails that form a simple cycle must share at
least 1 edge in the paths between their nodes (Trail 1 connects A and B, 2 connects C and D, then path
from A->B and C->D must share at least 1 edge).

For now, do a proof of concept to make sure the realization is correct. Try each pair of non-standard
trails, doing a DFS to find the path from A to B / storing the edges used in a HashSet of longs. If
in the DFS from C to D, an edge is reused, then add 1 to the answer.

Runtime: O(M^2 * N) - Definitely not fast enough, but it's a proof of concept so who cares
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class exerciseProof {
    int N, M, mapSize, numNonS;
    long answer;
    boolean[] visited;
    ArrayList<Edge>[] graphS, graphNonS;
    Pair[] nonStandardEdges;

    exerciseProof() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("exercise.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        graphS = new ArrayList[N];
        graphNonS = new ArrayList[N];
        numNonS = M - N + 1;
        nonStandardEdges = new Pair[numNonS];
        for (int i = 0; i < N; i++) {
            graphS[i] = new ArrayList<>(2);
            graphNonS[i] = new ArrayList<>(2);
        }
        int a, b;
        for (int i = 0; i < N - 1; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graphS[a].add(new Edge(b));
            graphS[b].add(new Edge(a));
        }
        for (int i = N - 1; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graphNonS[a].add(new Edge(b));
            graphNonS[b].add(new Edge(a));
            nonStandardEdges[i - N + 1] = new Pair(Math.min(a, b), Math.max(a, b));
        }
        fin.close();

        // Find edges in all paths
        visited = new boolean[N];
        for (int i = 0; i < numNonS; i++) {
            Arrays.fill(visited, false);
            visited[nonStandardEdges[i].a] = true;
            nonStandardEdges[i].edges = hashDFS(nonStandardEdges[i].a, nonStandardEdges[i].b, new HashSet<>());
        }

        if (N > 10) visited[-1] = false;

        // Try all possible pairs
        answer = 0;
        for (int i = 0; i < numNonS; i++) {
            for (int j = i + 1; j < numNonS; j++) {
                answer += testEdges(nonStandardEdges[i], nonStandardEdges[j]) ? 1 : 0;
            }
        }

        PrintWriter fout = new PrintWriter("exercise.out");
        fout.println(answer);
        fout.close();
    }

    // Check if the 2 edges share at least 1 edge in their standard paths
    boolean testEdges(Pair e1, Pair e2) {
        for (long l : e1.edges) {
            if (e2.edges.contains(l)) {
                // System.out.println("Pair " + e1 + " " + e2 + " works");
                return true;
            }
        }
        return false;
    }

    HashSet<Long> hashDFS(int n, int target, HashSet<Long> edges) {
        for (Edge o : graphS[n]) {
            if (!visited[o.n]) {
                edges.add(hash(n, o.n));
                visited[o.n] = true;
                if (o.n == target || hashDFS(o.n, target, edges) != null) return edges;
                edges.remove(hash(n, o.n));
            }
        }
        // No path found
        return null;
    }

    long hash(int a, int b) {
        return (long) N * Math.max(a, b) + Math.min(a, b);
    }

    public static void main(String[] args) throws IOException {
        new exerciseProof();
    }
}

class Pair {
    int a, b;
    HashSet<Long> edges;
    Pair(int a, int b) {
        this.a = a;
        this.b = b;
    }
    @Override
    public String toString() {
        return "(" + a + ", " + b + ")";
    }
}

class Edge {
    int n;
    Edge(int n) {
        this.n = n;
    }
}
