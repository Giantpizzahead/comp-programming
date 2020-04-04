/*
Solution: Centroid decomposition practice! Also, implementation. Fun!
Runtime: O(Q * log(Q)) with large constant factor
 */

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class newbarn {
    final int MAX_CENTROIDS = 18;
    final int INF = 987654321;
    int N, Q;
    Query[] queries;
    ArrayList<Integer>[] adj;
    boolean[] blocked;
    CentroidInfo[] centroidInfo;
    int[][] centroid, depth, subtreeID;

    newbarn(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        Q = Integer.parseInt(st.nextToken());
        queries = new Query[Q];
        N = 0;
        char t;
        int n;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            t = st.nextToken().charAt(0);
            n = Integer.parseInt(st.nextToken()) - 1;
            queries[i] = new Query(t == 'B', n);
            if (t == 'B') N++;
        }

        // Now, generate the finished forest
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);
        int currN = 0;
        for (Query q : queries) {
            if (q.isBuild) {
                if (q.n != -2) {
                    adj[currN].add(q.n);
                    adj[q.n].add(currN);
                }
                currN++;
            }
        }

        // Find the centroids
        stSize = new int[N];
        blocked = new boolean[N];
        centroid = new int[MAX_CENTROIDS][N];
        for (int i = 0; i < MAX_CENTROIDS; i++) Arrays.fill(centroid[i], -1);
        depth = new int[MAX_CENTROIDS][N];
        subtreeID = new int[MAX_CENTROIDS][N];
        centroidInfo = new CentroidInfo[N];
        for (int i = 0; i < N; i++) if (!blocked[i]) genCentroids(i, 0);

        // Answer the queries
        currN = 0;
        blocked = new boolean[N];
        Arrays.fill(blocked, true);
        for (Query q : queries) {
            if (q.isBuild) {
                // Initialize this centroid by finding the furthest distance within its nodes
                initCentroid(currN, currN, currN, centroidInfo[currN].centroidDepth);
                // System.out.println(centroidInfo[currN]);
                // Update distances for all centroids
                for (int i = 0; i < MAX_CENTROIDS; i++) {
                    if (centroid[i][currN] == -1) break;
                    centroidInfo[centroid[i][currN]].update(depth[i][currN], subtreeID[i][currN]);
                }
                blocked[currN] = false;
                currN++;
            } else {
                // Query distance for all centroids
                int maxDist = 0;
                for (int i = 0; i < MAX_CENTROIDS; i++) {
                    if (centroid[i][q.n] == -1 || blocked[centroid[i][q.n]]) continue;
                    // System.out.println(centroid[i][q.n]);
                    maxDist = Math.max(depth[i][q.n] + centroidInfo[centroid[i][q.n]].getMaxDist(subtreeID[i][q.n]), maxDist);
                }
                // System.out.println("Query " + q.n + ": " + maxDist);
                out.println(maxDist);
            }
        }
    }

    void initCentroid(int n, int p, int c, int d) {
        centroidInfo[c].update(depth[d][n], subtreeID[d][n]);
        for (int e : adj[n]) {
            if (e != p && centroid[d][e] == c && !blocked[e]) initCentroid(e, n, c, d);
        }
    }

    int[] stSize;
    void genCentroids(int n, int d) {
        genSTSize(n, n);
        tempRoot = n;
        bestCentroid = 0;
        bestSTSize = INF;
        findCentroid(n, n);

        int centroid = bestCentroid;
        // System.out.println("Centroid " + centroid + ", Depth " + d);
        // Split up each subtree individually
        blocked[centroid] = true;
        setupCentroid(centroid, d);
        for (int e : adj[centroid]) {
            if (!blocked[e]) genCentroids(e, d+1);
        }
    }

    // Sets up the centroid by marking the node depths & subtree IDs that are connected to it.
    void setupCentroid(int n, int d) {
        centroidInfo[n] = new CentroidInfo(d);
        depth[d][n] = 0;
        subtreeID[d][n] = -1;
        centroid[d][n] = n;
        int currID = 0;
        for (int e : adj[n]) {
            if (!blocked[e]) setupDFS(e, n, n, d, currID++, 1);
        }
    }

    void setupDFS(int n, int p, int c, int centID, int stID, int cDepth) {
        depth[centID][n] = cDepth;
        subtreeID[centID][n] = stID;
        centroid[centID][n] = c;
        for (int e : adj[n]) {
            if (e != p && !blocked[e]) setupDFS(e, n, c, centID, stID, cDepth+1);
        }
    }

    int tempRoot, bestCentroid, bestSTSize;
    void findCentroid(int n, int p) {
        int maxSTSize = stSize[tempRoot] - stSize[n];
        for (int e : adj[n]) {
            if (e != p && !blocked[e]) {
                maxSTSize = Math.max(stSize[e], maxSTSize);
                findCentroid(e, n);
            }
        }
        if (maxSTSize < bestSTSize) {
            bestSTSize = maxSTSize;
            bestCentroid = n;
        }
    }

    void genSTSize(int n, int p) {
        stSize[n] = 1;
        for (int e : adj[n]) {
            if (e != p && !blocked[e]) {
                genSTSize(e, n);
                stSize[n] += stSize[e];
            }
        }
    }

    class CentroidInfo {
        int centroidDepth;
        int maxD1 = 0, maxD2 = 0;
        int maxST1 = -1, maxST2 = -1;

        CentroidInfo(int centroidDepth) {
            this.centroidDepth = centroidDepth;
        }

        int getMaxDist(int fromST) {
            if (fromST == maxST1) return maxD2;
            else return maxD1;
        }

        void update(int d, int st) {
            if (d > maxD1) {
                if (st == maxST1) maxD1 = d;
                else {
                    maxD2 = maxD1;
                    maxST2 = maxST1;
                    maxD1 = d;
                    maxST1 = st;
                }
            } else if (d > maxD2 && st != maxST1) {
                maxD2 = d;
                maxST2 = st;
            }
        }

        @Override
        public String toString() {
            return "CentroidInfo{" +
                    "centroidDepth=" + centroidDepth +
                    ", maxD1=" + maxD1 +
                    ", maxD2=" + maxD2 +
                    ", maxST1=" + maxST1 +
                    ", maxST2=" + maxST2 +
                    '}';
        }
    }

    class Query {
        boolean isBuild;
        int n;

        Query(boolean isBuild, int n) {
            this.isBuild = isBuild;
            this.n = n;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("newbarn.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("newbarn.out")));
        new newbarn(in, out);
        in.close();
        out.close();
    }
}
