/*
Solution: For every min flow possible (1 to 1000), do 1 Dijkstra, only allowing those edges to be
used. Do this by sorting the pipes in order of flow rate, and adding the edges as you go.

Runtime: O(NE * log(E))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class pump {
    int N, M;
    Pipe[] pipes;
    final int INF = 987654321;
    ArrayList<Pair>[] graph;

    pump() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("pump.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        pipes = new Pipe[M];
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        int a, b, c, f;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken());
            f = Integer.parseInt(st.nextToken());
            pipes[i] = new Pipe(a, b, c, f);
        }
        fin.close();

        Arrays.sort(pipes, Comparator.comparingInt(x -> -x.f));

        long bestAnswer = -1;
        for (int maxFlow = 1000, pipeI = 0; maxFlow > 0; maxFlow--) {
            boolean pipeAdded = false;
            while (pipeI < M && pipes[pipeI].f >= maxFlow) {
                Pipe p = pipes[pipeI];
                graph[p.a].add(new Pair(p.b, p.c));
                graph[p.b].add(new Pair(p.a, p.c));
                pipeI++;
                pipeAdded = true;
            }

            if (!pipeAdded) continue;
            
            // Try with this max flow
            int currCost = dijkstra();
            // System.out.println("Max flow " + maxFlow + " = " + currCost);

            if (currCost != INF) {
                // Record possible new best flow
                bestAnswer = Math.max((long) maxFlow * 1000000 / currCost, bestAnswer);
            }
        }

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("pump.out")));
        fout.println(bestAnswer);
        fout.close();
    }
    
    int dijkstra() {
        boolean[] visited = new boolean[N];
        int[] bestDist = new int[N];
        Arrays.fill(bestDist, INF);
        PriorityQueue<Pair> pq = new PriorityQueue<>(Comparator.comparingInt(x -> x.c));
        pq.add(new Pair(0, 0));

        Pair c;
        while (!pq.isEmpty()) {
            c = pq.poll();
            if (visited[c.n]) continue;
            visited[c.n] = true;
            for (Pair e : graph[c.n]) {
                if (!visited[e.n] && c.c + e.c < bestDist[e.n]) {
                    // New best dist found
                    bestDist[e.n] = c.c + e.c;
                    pq.add(new Pair(e.n, c.c + e.c));
                }
            }
        }

        return bestDist[N-1];
    }

    public static void main(String[] args) throws IOException {
        new pump();
    }

    class Pair {
        int n, c;
        Pair(int n, int c) {
            this.n = n;
            this.c = c;
        }
    }

    class Pipe {
        int a, b, c, f;
        Pipe(int a, int b, int c, int f) {
            this.a = a;
            this.b = b;
            this.c = c;
            this.f = f;
        }
    }
}
