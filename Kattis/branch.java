import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class branch {
    int N, B, R, S;
    long[][] dp;
    long[] prefix;
    Integer[] cost;
    ArrayList<Pair>[] graph, revGraph;
    final int INF = 1000000007;

    branch() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        B = Integer.parseInt(st.nextToken());
        S = Integer.parseInt(st.nextToken());
        R = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        revGraph = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<>(10);
            revGraph[i] = new ArrayList<>(10);
        }
        int n1, n2, l;
        for (int i = 0; i < R; i++) {
            st = new StringTokenizer(in.readLine());
            n1 = Integer.parseInt(st.nextToken()) - 1;
            n2 = Integer.parseInt(st.nextToken()) - 1;
            l = Integer.parseInt(st.nextToken());
            graph[n1].add(new Pair(n2, l));
            revGraph[n2].add(new Pair(n1, l));
        }
        in.close();
        
        // Generate cost array from the graph
        int[] dists1 = dijkstra(graph);
        int[] dists2 = dijkstra(revGraph);
        cost = new Integer[B];
        for (int i = 0; i < B; i++) {
            cost[i] = dists1[i] + dists2[i];
        }
        Arrays.sort(cost, Comparator.reverseOrder());

        // System.out.println(Arrays.toString(cost));

        // Generate prefix sum array for cost
        prefix = new long[B];
        prefix[0] = cost[0];
        for (int i = 1; i < B; i++) {
            prefix[i] = prefix[i-1] + cost[i];
        }

        // Divide and conquer DP
        // First, set base cases (dp[1][0...B-1])
        dp = new long[S + 1][B];
        for (int j = 0; j < B; j++) {
            dp[1][j] = getCost(0, j);
        }

        // Do divide and conquer
        for (int i = 2; i < S + 1; i++) {
            divideAndConquer(i, 0, B-1, 0, B-1);
        }

        /*
        for (int i = 0; i < S + 1; i++) {
            System.out.println(Arrays.toString(dp[i]));
        }
         */

        PrintWriter out = new PrintWriter(System.out);
        out.println(dp[S][B-1]);
        out.close();
    }

    void divideAndConquer(int i, int start, int end, int optLow, int optHigh) {
        // System.out.println("i = " + i + ", start = " + start + ", end = " + end + ", optLow = " + optLow + ", optHigh = " + optHigh);
        if (start > end || end == 0) return;

        // Calculate optimal value for midpoint
        // Everything is inclusive
        int mid = (start + end + 1) / 2;
        int bestLoc = optLow;
        long bestCost = dp[i-1][optLow] + getCost(optLow + 1, mid);
        int bound = Math.min(mid - 1, optHigh);

        for (int j = optLow + 1; j <= bound; j++) {
            long newCost = dp[i-1][j] + getCost(j + 1, mid);
            if (newCost < bestCost) {
                bestLoc = j;
                bestCost = newCost;
            }
        }

        // System.out.println("dp[" + i + "][" + mid + "] = " + bestCost);
        dp[i][mid] = bestCost;

        // Recursively evaluate left and right values using the found bestLoc
        divideAndConquer(i, start, mid - 1, optLow, bestLoc);
        divideAndConquer(i, mid + 1, end, bestLoc, optHigh);
    }

    long getCost(int start, int end) {
        // System.out.println("getCost(" + start + ", " + end + ") = " + ((long) (prefix[end] - ((start == 0) ? 0 : prefix[start - 1])) * (end - start)));;
        return (long) (prefix[end] - ((start == 0) ? 0 : prefix[start - 1])) * (end - start);
    }
    
    int[] dijkstra(ArrayList<Pair>[] g) {
        PriorityQueue<Pair> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a.l));
        pq.add(new Pair(B, 0));
        int[] bestDist = new int[N];
        for (int i = 0; i < N; i++) bestDist[i] = INF;
        bestDist[B] = 0;
        boolean[] visited = new boolean[N];

        Pair c;
        while (!pq.isEmpty()) {
            c = pq.poll();
            if (visited[c.n]) continue;
            visited[c.n] = true;

            for (Pair edge : g[c.n]) {
                if (!visited[edge.n]) {
                    int dist = c.l + edge.l;
                    if (dist < bestDist[edge.n]) {
                        bestDist[edge.n] = dist;
                        pq.add(new Pair(edge.n, dist));
                    }
                }
            }
        }

        return bestDist;
    }

    public static void main(String[] args) throws IOException {
        new branch();
    }
}

class Pair {
    int n, l;
    Pair(int n, int l) {
        this.n = n;
        this.l = l;
    }
}