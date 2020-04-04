/*
Solution: Dijkstra.

Runtime: O(E * log(E))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class dijkstra {
    int N, M;
    ArrayList<Pair>[] graph;
    final long INF = 1_000_000_000_000L;

    dijkstra() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        int a, b, c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken());
            graph[a].add(new Pair(b, c));
            graph[b].add(new Pair(a, c));
        }
        in.close();

        Stack<Integer> path = dijkstraPath();
        PrintWriter out = new PrintWriter(System.out);
        if (path.size() == 1) out.println(-1);
        else {
            while (!path.isEmpty()) {
                out.print(path.pop() + 1);
                if (!path.isEmpty()) out.print(' ');
            }
            out.println();
        }
        out.close();
    }

    Stack<Integer> dijkstraPath() {
        long[] bestDist = new long[N];
        Arrays.fill(bestDist, INF);
        bestDist[0] = 0;
        int[] from = new int[N];
        Arrays.fill(from, -1);
        PriorityQueue<Pair> pq = new PriorityQueue<>(11, Comparator.comparingLong(x -> x.c));
        pq.add(new Pair(0, 0));

        Pair c;
        while (!pq.isEmpty()) {
            c = pq.poll();
            if (bestDist[c.n] != c.c) continue;
            for (Pair e : graph[c.n]) {
                if (c.c + e.c < bestDist[e.n]) {
                    bestDist[e.n] = c.c + e.c;
                    from[e.n] = c.n;
                    pq.add(new Pair(e.n, c.c + e.c));
                }
            }
        }

        // Generate reverse path
        Stack<Integer> path = new Stack<>();
        int n = N - 1;
        while (n != -1) {
            path.add(n);
            n = from[n];
        }
        return path;
    }

    public static void main(String[] args) throws IOException {
        new dijkstra();
    }

    class Pair {
        int n;
        long c;
        Pair(int n, long c) {
            this.n = n;
            this.c = c;
        }
    }
}
