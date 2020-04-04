/*
ID: sunnyky1
LANG: JAVA
TASK: ditch
Solution: This is exactly the maximum flow problem. Use a PFS to solve it.
Runtime: O(M^2 * log(M) * log(10^7))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class ditch {
    final int INF = 987654321;
    int N, M, source, sink;
    int[][] capacity;
    ArrayList<Integer>[] adj;

    ditch(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        M = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        source = 0;
        sink = N - 1;
        capacity = new int[N][N];
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);
        int s, e, c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            s = Integer.parseInt(st.nextToken()) - 1;
            e = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken());
            if (capacity[s][e] == 0 && capacity[e][s] == 0) {
                adj[s].add(e);
                adj[e].add(s);
            }
            capacity[s][e] += c;
        }
        int maxFlow = findMaxFlow();
        out.println(maxFlow);
    }

    int findMaxFlow() {
        pq = new PriorityQueue<>(new Comparator<State>() {
            @Override
            public int compare(State o1, State o2) {
                return o2.c - o1.c;
            }
        });
        bestCapacity = new int[N];
        from = new int[N];
        int currFlow = 0;
        while (true) {
            int bottleneck = findAugmentingPath();
            if (bottleneck == -1) break;
            else currFlow += bottleneck;
        }
        return currFlow;
    }

    int[] bestCapacity, from;
    PriorityQueue<State> pq;
    int findAugmentingPath() {
        Arrays.fill(bestCapacity, 0);
        bestCapacity[source] = INF;
        from[source] = -1;
        pq.clear();
        pq.add(new State(source, INF));

        State c;
        while (!pq.isEmpty()) {
            c = pq.poll();
            if (c.c != bestCapacity[c.n]) continue;
            if (c.n == sink) {
                // Backtrace the path
                int n = c.n;
                while (from[n] != -1) {
                    capacity[from[n]][n] -= c.c;
                    capacity[n][from[n]] += c.c;
                    n = from[n];
                }
                return c.c;
            }
            for (int e : adj[c.n]) {
                int nc = Math.min(c.c, capacity[c.n][e]);
                if (nc > bestCapacity[e]) {
                    bestCapacity[e] = nc;
                    from[e] = c.n;
                    pq.add(new State(e, nc));
                }
            }
        }
        return -1;
    }

    class State {
        int n, c;
        State(int n, int c) {
            this.n = n;
            this.c = c;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("ditch.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ditch.out")));
        new ditch(in, out);
        in.close();
        out.close();
    }
}
