import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class skiaccidentsold {
    int N, M, numOpened;
    int[] inDegree, outDegree;
    boolean[] isOpen;
    HashSet<Integer> canBeOpened;
    ArrayList<Integer>[] adj, revAdj;

    skiaccidentsold(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        adj = new ArrayList[N];
        revAdj = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            adj[i] = new ArrayList<>(2);
            revAdj[i] = new ArrayList<>(2);
        }
        inDegree = new int[N];
        outDegree = new int[N];
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(st.nextToken()) - 1;
            int b = Integer.parseInt(st.nextToken()) - 1;
            adj[a].add(b);
            revAdj[b].add(a);
            inDegree[b]++;
            outDegree[a]++;
        }

        numOpened = 0;
        canBeOpened = new HashSet<>(N);
        for (int i = 0; i < N; i++) canBeOpened.add(i);
        isOpen = new boolean[N];
        Node[] nodes = new Node[N];
        for (int i = 0; i < N; i++) nodes[i] = new Node(i, inDegree[i]);
        Arrays.sort(nodes, new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                return o1.d - o2.d;
            }
        });
        int currNodeI = 0;
        while (!canBeOpened.isEmpty()) {
            int n = nodes[currNodeI].n;
            if (canBeOpened.contains(n)) {
                canBeOpened.remove(n);
                numOpened++;
                isOpen[n] = true;
                openNode(n);
            }
            currNodeI++;
        }

        int numClosed = 0;
        for (int i = 0; i < N; i++) if (!isOpen[i]) numClosed++;
        out.println(numClosed);
        numClosed = 0;
        for (int i = 0; i < N; i++) {
            if (!isOpen[i]) {
                if (numClosed != 0) out.print(' ');
                numClosed++;
                out.print(i+1);
            }
        }
        out.println();
    }

    void openNode(int n) {
        for (int e : adj[n]) {
            canBeOpened.remove(e);
        }
        for (int e : revAdj[n]) {
            canBeOpened.remove(e);
        }
    }

    static class Node {
        int n, d;
        Node(int n, int d) {
            this.n = n;
            this.d = d;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new skiaccidentsold(in, out);
        in.close();
        out.close();
    }
}
