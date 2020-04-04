import java.util.*;

@SuppressWarnings("unchecked")
public class highway {
    int N, M, A, B;
    long lightResult, heavyResult;
    ArrayList<Pair>[] adj;
    boolean[] blocked;

    // Assumes the input graph is a tree.
    void find_pair(int N, int[] U, int[] V, int A, int B) {
        this.N = N;
        this.M = U.length;
        this.A = A;
        this.B = B;
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);
        for (int i = 0; i < M; i++) {
            adj[U[i]].add(new Pair(V[i], i));
            adj[V[i]].add(new Pair(U[i], i));
        }

        // Do base queries
        queryWeights = new int[M];
        lightResult = highway_lib.ask(queryWeights);
        Arrays.fill(queryWeights, 1);
        heavyResult = highway_lib.ask(queryWeights);
        Arrays.fill(queryWeights, 0);

        blocked = new boolean[N];
        stSize = new int[N];
        visited = new boolean[N];
        stage1(0);
    }

    int[] queryWeights;
    void stage1(int sn) {
        // System.out.println("Stage 1: " + Arrays.toString(blocked));
        int centroid = findCentroid(sn);
        // System.out.println("Centroid: " + centroid);
        if (stSize[sn] == 2) {
            // Base case; already found answer
            answerBC(sn);
            return;
        }

        // Choose a bunch of heavy STs (want about half nodes)
        ArrayList<Integer> heavySTs = new ArrayList<>(2);
        ArrayList<Integer> lightSTs = new ArrayList<>(2);
        blocked[centroid] = true;
        boolean makeHeavy = true;
        for (Pair e : adj[centroid]) {
            if (!blocked[e.n]) {
                if (makeHeavy) {
                    heavySTs.add(e.n);
                    addHeavyWeights(e.n, e.n, 1);
                } else {
                    lightSTs.add(e.n);
                }
                makeHeavy = !makeHeavy;
            }
        }

        // System.out.println(heavySTs);
        // System.out.println(lightSTs);

        // Do the actual query
        // System.out.println(Arrays.toString(queryWeights));
        long result = highway_lib.ask(queryWeights);

        // Reverse operation
        for (int st : heavySTs) addHeavyWeights(st, st, 0);
        blocked[centroid] = false;

        if (result == lightResult) {
            // Both nodes in non-chosen STs or centroid
            for (int st : heavySTs) blocked[st] = true;
            stage1(centroid);
        } else if (result == heavyResult) {
            // Both nodes in chosen ST or centroid
            for (int st : lightSTs) blocked[st] = true;
            stage1(centroid);
        } else {
            // Go to stage 2 with known dists
            // System.out.println(result);
            int distToA = (int) ((result - lightResult) / (B - A));
            int distToB = (int) ((heavyResult - result) / (B - A));
            stage2(centroid, heavySTs, lightSTs, distToA, distToB);
        }
    }

    ArrayList<Pair> heavyNodes = new ArrayList<>();
    ArrayList<Pair> lightNodes = new ArrayList<>();
    void stage2(int centroid, ArrayList<Integer> heavySTs, ArrayList<Integer> lightSTs, int distHeavy, int distLight) {
        // System.out.println("centroid = " + centroid + ", heavyST = " + heavyST + ", distHeavy = " + distHeavy + ", distLight = " + distLight);
        // Get initial nodes
        int heavyI = 0, lightI = 0;
        heavySTs.add(-1);
        lightSTs.add(-1);
        for (Pair e : adj[centroid]) {
            if (blocked[e.n]) continue;
            if (e.n == heavySTs.get(heavyI)) {
                addWithDist(e.n, e.i, distHeavy - 1, heavyNodes);
                heavyI++;
            } else {
                addWithDist(e.n, e.i, distLight - 1, lightNodes);
                lightI++;
            }
        }

        // Now, binary search on each list
        int S = doBinarySearch(heavyNodes);
        int T = doBinarySearch(lightNodes);
        highway_lib.answer(S, T);
    }

    int doBinarySearch(ArrayList<Pair> nodes) {
        int low = 0, high = nodes.size() - 1;
        while (low < high) {
            int mid = (low + high) / 2;
            if (check(nodes, low, mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return nodes.get(low).n;
    }

    // Returns true if 1 of the nodes in the range [l, r] is S or T.
    boolean check(ArrayList<Pair> nodes, int l, int r) {
        for (int i = l; i <= r; i++) queryWeights[nodes.get(i).i] = 1;
        long result = highway_lib.ask(queryWeights);
        for (int i = l; i <= r; i++) queryWeights[nodes.get(i).i] = 0;
        return result != lightResult;
    }

    void addWithDist(int n, int prevEdge, int dist, ArrayList<Pair> list) {
        if (dist == 0) {
            list.add(new Pair(n, prevEdge));
            return;
        }
        for (Pair e : adj[n]) {
            if (e.i != prevEdge && !blocked[e.n]) addWithDist(e.n, e.i, dist - 1, list);
        }
    }

    void addHeavyWeights(int n, int p, int v) {
        for (Pair e : adj[n]) {
            queryWeights[e.i] = v;
            if (e.n != p && !blocked[e.n]) {
                addHeavyWeights(e.n, n, v);
            }
        }
    }

    void answerBC(int sn) {
        int otherN = -1;
        for (Pair e : adj[sn]) {
            if (!blocked[e.n]) {
                otherN = e.n;
                break;
            }
        }
        highway_lib.answer(sn, otherN);
    }

    int[] stSize;
    boolean[] visited;
    Queue<Integer> q = new LinkedList<>();
    int findCentroid(int sn) {
        genSTSize(sn, sn);
        // System.out.println(Arrays.toString(stSize));
        int bestSTSize = 99999999, centroid = -1;
        q.clear();
        q.add(sn);
        visited[sn] = true;
        int c, maxSTSize;
        while (!q.isEmpty()) {
            c = q.poll();
            maxSTSize = stSize[sn] - stSize[c];
            for (Pair e : adj[c]) {
                if (!visited[e.n] && !blocked[e.n]) {
                    visited[e.n] = true;
                    q.add(e.n);
                    maxSTSize = Math.max(stSize[e.n], maxSTSize);
                }
            }
            if (maxSTSize < bestSTSize) {
                bestSTSize = maxSTSize;
                centroid = c;
            }
        }
        return centroid;
    }

    void genSTSize(int n, int p) {
        stSize[n] = 1;
        visited[n] = false;
        for (Pair e : adj[n]) {
            if (e.n != p && !blocked[e.n]) {
                genSTSize(e.n, n);
                stSize[n] += stSize[e.n];
            }
        }
    }

    class Pair {
        int n, i;
        Pair(int n, int i) {
            this.n = n;
            this.i = i;
        }
    }
}
