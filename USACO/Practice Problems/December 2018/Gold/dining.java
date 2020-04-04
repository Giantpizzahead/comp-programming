/*
Solution: First, Dijkstra from the barn to find the maximum distance where the haybales are still
viable to eat (won't delay too long). This value means that if a cow got to that haybale in a distance
<= D, then it can eat that haybale and not lose any time.

Then, Dijkstra with all the haybale locations as starting points in the priority queue. Set them all to
value -D. Do a Dijkstra as normal; when you come across a node, check if the cost is less than or equal
to the cost for that node to get to the barn (don't check this if the node is the barn). If it's true,
that node is a 1 (can reach a haybale without losing time). Else, it's a 0.

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class dining {
    int N, M, K;
    int[] distToBarn;
    boolean[] canEat;
    ArrayList<Pair>[] graph;
    Pair[] haybales;
    final int INF = 1000000007;

    dining() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("dining.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>();
        int n1, n2, c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            n1 = Integer.parseInt(st.nextToken()) - 1;
            n2 = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken());
            graph[n1].add(new Pair(n2, c));
            graph[n2].add(new Pair(n1, c));
        }
        haybales = new Pair[K];
        for (int i = 0; i < K; i++) {
            st = new StringTokenizer(fin.readLine());
            n1 = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken());
            haybales[i] = new Pair(n1, c);
        }
        fin.close();

        // Dijkstra from barn to find distance to all nodes
        findDistToBarn();

        // System.out.println(Arrays.toString(distToBarn));

        // Do a 2nd Dijkstra with haybales / cost -D as starting locations
        dijkstraHaybales();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("dining.out")));
        for (int i = 0; i < N-1; i++) {
            fout.println(canEat[i] ? 1 : 0);
        }
        fout.close();
    }

    void dijkstraHaybales() {
        PriorityQueue<Pair> pq = new PriorityQueue<>((a, b) -> { return a.b - b.b; });
        int[] distToHaybale = new int[N];
        for (int i = 0; i < N; i++) distToHaybale[i] = INF;
        boolean[] visited = new boolean[N];
        canEat = new boolean[N];

        // Starting states are the haybales
        for (Pair haybale : haybales) {
            pq.add(new Pair(haybale.a, distToBarn[haybale.a] - haybale.b));
            distToHaybale[haybale.a] = Math.min(distToBarn[haybale.a] - haybale.b, distToHaybale[haybale.a]);
        }

        Pair curr;
        while (!pq.isEmpty()) {
            curr = pq.poll();
            if (visited[curr.a]) continue;
            visited[curr.a] = true;
            // Check if cow can eat
            canEat[curr.a] = curr.b <= distToBarn[curr.a];

            // Explore neighbors
            for (Pair edge : graph[curr.a]) {
                int newDist = curr.b + edge.b;
                if (!visited[edge.a] && newDist < distToHaybale[edge.a]) {
                    // Add to evaluate
                    pq.add(new Pair(edge.a, newDist));
                    distToHaybale[edge.a] = newDist;
                }
            }
        }

        // System.out.println(Arrays.toString(distToHaybale));
    }

    void findDistToBarn() {
        PriorityQueue<Pair> pq = new PriorityQueue<>((a, b) -> { return a.b - b.b; });
        pq.add(new Pair(N-1, 0));
        boolean[] visited = new boolean[N];
        distToBarn = new int[N];
        for (int i = 0; i < N; i++) distToBarn[i] = INF;
        distToBarn[N-1] = 0;

        Pair curr;
        while (!pq.isEmpty()) {
            curr = pq.poll();
            if (visited[curr.a]) continue;
            visited[curr.a] = true;
            // Explore neighbors
            for (Pair edge : graph[curr.a]) {
                int newDist = curr.b + edge.b;
                if (!visited[edge.a] && newDist < distToBarn[edge.a]) {
                    // Add to evaluate
                    pq.add(new Pair(edge.a, newDist));
                    distToBarn[edge.a] = newDist;
                }
            }
        }

    }

    public static void main(String[] args) throws IOException {
        new dining();
    }

    static class Pair {
        int a, b;
        Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }
}
