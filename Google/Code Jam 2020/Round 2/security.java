import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class security {
    final int INF = 1017654321;
    int C, D;
    int[] info, latency;
    ArrayList<Edge>[] adj;

    security(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        C = Integer.parseInt(st.nextToken());
        D = Integer.parseInt(st.nextToken());
        info = new int[C];
        st = new StringTokenizer(in.readLine());
        for (int i = 1; i < C; i++) info[i] = Integer.parseInt(st.nextToken());

        adj = new ArrayList[C];
        for (int i = 0; i < C; i++) adj[i] = new ArrayList<>(2);

        int a, b;
        for (int i = 0; i < D; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            adj[a].add(new Edge(b, i));
            adj[b].add(new Edge(a, i));
        }

        int numVisited = 1, currTime = 0;
        int[] visitTime = new int[C];
        Arrays.fill(visitTime, INF);
        visitTime[0] = 0;
        int[] latency = new int[D];
        Arrays.fill(latency, 1000000);

        PriorityQueue<Node> pqDist = new PriorityQueue<>(11, Comparator.comparingInt(x -> x.c));
        ArrayList<Integer>[] groupAdd = new ArrayList[C + 1];
        for (int i = 0; i <= C; i++) groupAdd[i] = new ArrayList<>(2);

        for (int i = 1; i < C; i++) {
            if (info[i] < 0) groupAdd[-info[i]].add(i);
            else pqDist.add(new Node(i, info[i]));
        }

        while (numVisited != C) {
            if (!groupAdd[numVisited].isEmpty()) {
                // These computers must be added at the same time
                int earliestAddTime = currTime + 1;
                for (int n : groupAdd[numVisited]) {
                    int bestAddTime = INF;
                    for (Edge e : adj[n]) {
                        bestAddTime = Math.min(visitTime[e.n] + 1, bestAddTime);
                    }
                    earliestAddTime = Math.max(bestAddTime, earliestAddTime);
                }

                // Add all computers at this time
                currTime = earliestAddTime;
                for (int n : groupAdd[numVisited]) {
                    for (Edge e : adj[n]) {
                        if (visitTime[e.n] + 1 <= earliestAddTime) {
                            latency[e.id] = earliestAddTime - visitTime[e.n];
                            visitTime[n] = earliestAddTime;
                            numVisited++;
                            break;
                        }
                    }
                }
            } else {
                int n = pqDist.poll().n;
                currTime = info[n];
                // Find an edge that can link to this one
                for (Edge e : adj[n]) {
                    if (visitTime[e.n] < info[n]) {
                        latency[e.id] = info[n] - visitTime[e.n];
                        visitTime[n] = info[n];
                        numVisited++;
                        break;
                    }
                }
            }
        }

        out.print("Case #" + tn + ":");
        for (int i = 0; i < D; i++) {
            out.print(' ');
            out.print(latency[i]);
        }
        out.println();
    }

    class Node {
        int n, c;
        Node(int n, int c) {
            this.n = n;
            this.c = c;
        }
    }

    class Edge {
        int n, id;
        Edge(int nn, int idd) {
            n = nn;
            id = idd;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new security(in, out, i);
        in.close();
        out.close();
    }
}
