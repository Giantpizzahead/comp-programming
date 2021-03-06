import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class deletecutgame {
    int N, M, treeN;
    int[] compID, numNodes;
    boolean[] isBridge;
    EdgeInfo[] edges;
    ArrayList<Edge>[] adj, treeAdj;

    deletecutgame(BufferedReader in, PrintWriter out) throws IOException {
        // System.out.println(modInverse(MOD, 3));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);
        edges = new EdgeInfo[M];
        int a, b;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            if (a == b) {
                i--;
                M--;
                continue;
            }
            adj[a].add(new Edge(b, i));
            adj[b].add(new Edge(a, i));
            edges[i] = new EdgeInfo(a, b);
        }

        disc = new int[N];
        ll = new int[N];
        compID = new int[N];
        isBridge = new boolean[M];
        findBridges(0, -1);
        // System.out.println(Arrays.toString(isBridge));
        // System.out.println(Arrays.toString(disc));
        // System.out.println(Arrays.toString(ll));
        // System.out.println(Arrays.toString(compID));

        // Make a tree using the bridges
        treeN = currComp;
        if (treeN == 1) {
            // No bridges present; special case
            out.println("0 0");
            return;
        }
        numNodes = new int[treeN];
        for (int i = 0; i < N; i++) numNodes[compID[i]]++;
        treeAdj = new ArrayList[treeN];
        for (int i = 0; i < treeN; i++) treeAdj[i] = new ArrayList<>(2);
        for (int i = 0; i < M; i++) {
            if (isBridge[i]) {
                treeAdj[compID[edges[i].a]].add(new Edge(compID[edges[i].b], i));
                treeAdj[compID[edges[i].b]].add(new Edge(compID[edges[i].a], i));
            }
        }

        // Now, figure out all subtree sizes to determine which bridges will make who win
        findSTSizes(0, 0);

        // System.out.println("Even: " + numEven + ", Odd: " + numOdd);
        int A = modDiv(numEven, numEven + numOdd);
        int B = modDiv(numOdd, numEven + numOdd);
        out.println(A + " " + B);
    }

    final int MOD = 1000000007;
    int modDiv(int a, int b) {
        int inv;
        if (b == 1) inv = 1;
        else inv = (int) modInverse(MOD, b).f;
        return (int) ((long) a * inv % MOD);
    }

    Pair modInverse(long a, long b) {
        // a = bc + d
        long c = a / b;
        long d = a % b;
        // System.out.printf("%d = %d(%d) + %d\n", a, b, c, d);
        if (d == 1) {
            // Base case
            return new Pair(1, MOD - c);
        } else {
            Pair res = modInverse(b, d);
            long e = res.f;
            long f = (res.e + (-c * res.f)) % MOD;
            if (f < 0) f += MOD;
            return new Pair(e, f);
        }
    }

    class Pair {
        long e, f;
        Pair(long e, long f) {
            this.e = e;
            this.f = f;
        }

        @Override
        public String toString() {
            return "(" + e + ", " + f + ")";
        }
    }

    int numEven = 0, numOdd = 0;
    int findSTSizes(int n, int p) {
        int currSTSize = 0;
        for (Edge e : treeAdj[n]) {
            if (e.n == p) continue;
            currSTSize += findSTSizes(e.n, n);
        }
        currSTSize += numNodes[n];
        if (n != 0) {
            if (currSTSize % 2 == 0 && N % 2 == 0) numEven++;
            else numOdd++;
        }
        return currSTSize;
    }

    int currDisc = 1, currComp = 1;
    int[] disc, ll;
    Stack<Integer> nodes = new Stack<>();
    void findBridges(int n, int lastEdge) {
        disc[n] = currDisc++;
        ll[n] = disc[n];
        nodes.add(n);
        for (Edge e : adj[n]) {
            if (e.id == lastEdge) continue;
            if (disc[e.n] == 0) {
                findBridges(e.n, e.id);
                ll[n] = Math.min(ll[e.n], ll[n]);
                if (ll[e.n] > disc[n]) {
                    // Bridge!
                    isBridge[e.id] = true;
                    // Mark all nodes as the same compID
                    while (nodes.peek() != e.n) {
                        compID[nodes.pop()] = currComp;
                    }
                    compID[nodes.pop()] = currComp++;
                }
            } else {
                ll[n] = Math.min(disc[e.n], ll[n]);
            }
        }
    }

    class EdgeInfo {
        int a, b;
        EdgeInfo(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }

    class Edge {
        int n, id;
        Edge(int n, int id) {
            this.n = n;
            this.id = id;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new deletecutgame(in, out);
        in.close();
        out.close();
    }
}
