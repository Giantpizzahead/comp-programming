import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class hiddenpair {
    static BufferedReader in;
    int N, maxDepth, root, minDist;
    int[] depth;
    ArrayList<Integer>[] adj;

    hiddenpair() throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(st.nextToken()) - 1;
            int b = Integer.parseInt(st.nextToken()) - 1;
            adj[a].add(b);
            adj[b].add(a);
        }
        depth = new int[N];
        depth[0] = -1;
        maxDepth = 0;
        root = findCentroid();
        // System.out.println("centroid " + root);
        genTreeInfo(root, root);

        // Find base depth
        ArrayList<Integer> toQuery = new ArrayList<>(N);
        for (int i = 0; i < N; i++) toQuery.add(i+1);
        Pair result = query(toQuery);
        minDist = result.d;

        Pair correctResult = null;
        // Binary search on depth
        int low = 0, high = maxDepth;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            result = check(mid);
            if (minDist == result.d) {
                low = mid;
                correctResult = result;
            } else {
                high = mid - 1;
            }
        }

        // One of the nodes is found; find the other one
        int firstNode = correctResult.n;
        // System.out.println("first node is " + firstNode);
        int secondNode = findSecondNode(firstNode);
        System.out.printf("! %d %d\n", firstNode+1, secondNode+1);
        System.out.flush();

        if (in.readLine().equals("Incorrect")) System.exit(0);
    }

    ArrayList<Pair> nodesWithDist;
    int findSecondNode(int firstNode) {
        // Find nodes with right distance
        nodesWithDist = new ArrayList<>();
        findNodesWithDist(firstNode, firstNode, 0);

        ArrayList<Integer> toQuery = new ArrayList<>();
        for (Pair p : nodesWithDist) {
            toQuery.add(p.d);
        }
        Pair res = query(toQuery);
        for (Pair p : nodesWithDist) {
            if (p.d-1 == res.n) return p.n;
        }
        return -1;
    }

    void findNodesWithDist(int n, int p, int d) {
        if (d == minDist) {
            nodesWithDist.add(new Pair(n, n+1));
        }
        for (int e : adj[n]) {
            if (e != p) findNodesWithDist(e, n, d+1);
        }
    }

    int findCentroid() {
        stSize = new int[N];
        genSTSizes(0, 0);
        int n = 0, p = 0;
        boolean moved = true;
        while (moved) {
            moved = false;
            for (int e : adj[n]) {
                if (e == p) continue;
                if (stSize[e] > N / 2) {
                    p = n;
                    n = e;
                    moved = true;
                    break;
                }
            }
        }
        return n;
    }

    int[] stSize;
    void genSTSizes(int n, int p) {
        stSize[n] = 1;
        for (int e : adj[n]) {
            if (e != p) {
                genSTSizes(e, n);
                stSize[n] += stSize[e];
            }
        }
    }

    Pair check(int d) {
        ArrayList<Integer> toQuery = new ArrayList<>(2);
        for (int i = 0; i < N; i++) {
            if (depth[i] >= d) toQuery.add(i+1);
        }
        return query(toQuery);
    }

    Pair query(ArrayList<Integer> toQuery) {
        System.out.printf("? %d", toQuery.size());
        for (int q : toQuery) System.out.printf(" %d", q);
        System.out.println();
        System.out.flush();

        try {
            StringTokenizer st = new StringTokenizer(in.readLine());
            return new Pair(Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()));
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    void genTreeInfo(int n, int p) {
        depth[n] = depth[p] + 1;
        maxDepth = Math.max(depth[n], maxDepth);
        for (int e : adj[n]) {
            if (e != p) genTreeInfo(e, n);
        }
    }

    static class Pair {
        int n, d;
        Pair(int n, int d) {
            this.n = n;
            this.d = d;
        }
    }

    public static void main(String[] args) throws IOException {
        in = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new hiddenpair();
        in.close();
    }
}
