/*
Solution: Dijkstra!
Runtime: Dijkstra!
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class dijkstra2 {
    final long INF = 999999999999L;
    int N, M;
    ArrayList<Pair>[] adj;

    dijkstra2(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);

        int a, b, w;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            w = Integer.parseInt(st.nextToken());
            adj[a].add(new Pair(b, w));
            adj[b].add(new Pair(a, w));
        }

        Stack<Integer> res = doDijkstra();
        if (res == null) out.println(-1);
        else {
            boolean notFirst = false;
            while (!res.isEmpty()) {
                if (notFirst) out.print(' ');
                else notFirst = true;
                out.print(res.pop() + 1);
            }
        }
    }

    Stack<Integer> doDijkstra() {
        long[] bestDist = new long[N];
        int[] from = new int[N];
        Arrays.fill(bestDist, INF);
        bestDist[0] = 0;
        from[0] = -1;
        PriorityQueue<Pair> pq = new PriorityQueue<>(new Comparator<Pair>() {
            @Override
            public int compare(Pair o1, Pair o2) {
                long res = o1.b - o2.b;
                if (res < 0) return -1;
                else if (res > 0) return 1;
                else return 0;
            }
        });
        pq.add(new Pair(0, 0));
        Pair c;
        while (!pq.isEmpty()) {
            c = pq.poll();
            for (Pair e : adj[c.a]) {
                if (c.b + e.b < bestDist[e.a]) {
                    bestDist[e.a] = c.b + e.b;
                    from[e.a] = c.a;
                    pq.add(new Pair(e.a, bestDist[e.a]));
                }
            }
        }

        if (bestDist[N-1] == INF) return null;
        Stack<Integer> path = new Stack<>();
        int cn = N-1;
        while (cn != -1) {
            path.add(cn);
            cn = from[cn];
        }
        return path;
    }

    static class Pair {
        int a;
        long b;
        Pair(int aa, long bb) {
            a = aa;
            b = bb;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("dijkstra.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("dijkstra.out")));
        new dijkstra2(in, out);
        in.close();
        out.close();
    }
}
