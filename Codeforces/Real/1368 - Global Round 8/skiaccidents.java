import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class skiaccidents {
    int N, M, numOpened;
    int[] inDegree, outDegree;
    boolean[] isOpen, mustBeClosed;
    ArrayList<Integer>[] adj, revAdj;

    skiaccidents(BufferedReader in, PrintWriter out) throws IOException {
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

        while (true) {
            numOpened = 0;
            mustBeClosed = new boolean[N];
            isOpen = new boolean[N];
            int[] nodes = new int[N];
            for (int i = 0; i < N; i++) nodes[i] = i;
            Random rnd = new Random();
            for (int i = N - 1; i >= 0; i--) {
                int x = rnd.nextInt(i + 1);
                int t = nodes[i];
                nodes[i] = nodes[x];
                nodes[x] = t;
            }
            // System.out.println(Arrays.toString(nodes));
            int currNodeI = 0;
            while (currNodeI != N) {
                int n = nodes[currNodeI];
                if (!mustBeClosed[n]) {
                    mustBeClosed[n] = true;
                    numOpened++;
                    isOpen[n] = true;
                    openNode(n);
                }
                currNodeI++;
            }

            int numClosed = 0;
            for (int i = 0; i < N; i++) if (!isOpen[i]) numClosed++;
            if (numClosed > N * 4 / 7) continue;
            out.println(numClosed);
            numClosed = 0;
            for (int i = 0; i < N; i++) {
                if (!isOpen[i]) {
                    if (numClosed != 0) out.print(' ');
                    numClosed++;
                    out.print(i + 1);
                }
            }
            out.println();
            break;
        }
    }

    void openNode(int n) {
        for (int e : adj[n]) {
            mustBeClosed[e] = true;
        }
        for (int e : revAdj[n]) {
            mustBeClosed[e] = true;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new skiaccidents(in, out);
        in.close();
        out.close();
    }
}
