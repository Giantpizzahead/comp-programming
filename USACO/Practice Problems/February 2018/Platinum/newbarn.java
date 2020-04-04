/*
Solution: Centroid decomposition (longest distance to another barn can be split into log(N)
subproblems with dist(N, centroid) + max(depth of other subtrees)). Store dists, centroid IDs, and
subtree IDs in 2D arrays, along with some info for each centroid. Building and querying both need
to update info for log(N) centroids, so they both take log(N) time.

Runtime: O(Q * log(Q)) with a high constant factor
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class newbarn {
    int N, numNodes = 0;
    int[] firstActive;
    Query[] queries;
    ArrayList<Edge>[] graph;
    final int INF = 999999999;

    // Centroid info
    final int MAX_CENTROIDS = 20;
    Edge[][] distToCentroid;
    int[][] nodeCentroid, nodeSTID;
    CentroidInfo[] centroidInfo;
    boolean[] blocked;

    newbarn() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("newbarn.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        queries = new Query[N];
        // Generate the final tree while parsing input
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        firstActive = new int[N];
        char a;
        int b;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            a = st.nextToken().charAt(0);
            b = Integer.parseInt(st.nextToken());
            if (a == 'B') {
                firstActive[numNodes] = i;
                queries[i] = new Query(b-1, numNodes++, true);
            }
            else queries[i] = new Query(b-1, -1, false);
            if (queries[i].isBuild) {
                if (queries[i].a == -2) continue;  // No edge
                graph[queries[i].a].add(new Edge(queries[i].b, i));
                graph[queries[i].b].add(new Edge(queries[i].a, i));
            }
        }
        fin.close();

        // Generate centroids & required info
        distToCentroid = new Edge[N][MAX_CENTROIDS];
        nodeCentroid = new int[N][MAX_CENTROIDS];
        for (int i = 0; i < N; i++) Arrays.fill(nodeCentroid[i], -1);
        nodeSTID = new int[N][MAX_CENTROIDS];
        centroidInfo = new CentroidInfo[N];
        blocked = new boolean[N];
        parent = new int[N];
        subtreeSize = new int[N];
        // Do 'floodfill'
        for (int i = 0; i < N; i++) {
            if (!blocked[i]) divideTree(i, 0);
        }

        // Now, handle the queries
        Query q;
        ArrayList<Integer> queryResults = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            q = queries[i];
            if (q.a != -2) {  // If -2, then no new edge to update
                // System.out.println(q);
                if (q.isBuild) {
                    // Update max subtree depths
                    int centroid;
                    for (int j = 0; j < MAX_CENTROIDS; j++) {
                        centroid = nodeCentroid[q.b][j];
                        if (centroid == -1 || firstActive[centroid] >= i || centroid != nodeCentroid[q.a][j]) continue;

                        // Both nodes have the same centroid; update max subtree depth of the current sid
                        centroidInfo[centroid].updateSTDepth(nodeSTID[q.b][j], distToCentroid[q.b][j].n);
                    }
                } else {
                    // Query
                    int centroid, maxDist = 0;
                    for (int j = 0; j < MAX_CENTROIDS; j++) {
                        centroid = nodeCentroid[q.a][j];
                        if (centroid == -1 || firstActive[centroid] >= i) continue;

                        // Length of path = dist(node, centroid) + dist(centroid, max depth of other st)
//                    System.out.println("Centroid " + centroid + " info:");
//                    System.out.println(centroidInfo[centroid]);
//                    for (int n = 0; n < N; n++) System.out.print(nodeSTID[n][j] + " ");
//                    System.out.println();
                        maxDist = Math.max(distToCentroid[q.a][j].n + centroidInfo[centroid].getMaxDepth(nodeSTID[q.a][j]), maxDist);
                    }
                    // System.out.println("Result: " + maxDist);
                    queryResults.add(maxDist);
                }
            }

            // Query every node for debugging
            /*
            int[] results = new int[i+1];
            for (int n = 0; n <= i; n++) {
                // Query
                int centroid, maxDist = 0;
                for (int j = 0; j < MAX_CENTROIDS; j++) {
                    centroid = nodeCentroid[n][j];
                    if (centroid == -1 || firstActive[centroid] > i) continue;

                    // Length of path = dist(node, centroid) + dist(centroid, max depth of other st)
                    maxDist = Math.max(distToCentroid[n][j].n + centroidInfo[centroid].getMaxDepth(nodeSTID[n][j]), maxDist);
                }
                // System.out.println("Result: " + maxDist);
                results[n] = maxDist;
            }
            System.out.println(Arrays.toString(results));
            */
        }

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("newbarn.out")));
        queryResults.forEach(fout::println);
        fout.close();
    }

    Edge bestInitialDepth;
    int bestInitialSTID;
    void setupCentroid(int n, int layer) {
        // Label all nodes with the centroid, subtree ID, and calculate the distance from that node to the centroid
        // Also find the initial depth / active time of this centroid
        bestInitialDepth = new Edge(0, firstActive[n]);
        bestInitialSTID = -1;
        int currSTID = 0;
        distToCentroid[n][layer] = new Edge(0, firstActive[n]);
        nodeCentroid[n][layer] = n;
        nodeSTID[n][layer] = -1;
        for (Edge e : graph[n]) {
            if (blocked[e.n]) continue;
            recurseCentroid(e.n, n, 1, Math.max(firstActive[n], e.time), n, currSTID++, layer);
        }

        // Make centroid info
        centroidInfo[n] = new CentroidInfo(firstActive[n], bestInitialDepth.n, bestInitialSTID);
        // System.out.println("Initial " + n + ": " + centroidInfo[n]);
    }

    void recurseCentroid(int n, int p, int dist, int time, int c, int sid, int layer) {
        distToCentroid[n][layer] = new Edge(dist, time);
        nodeCentroid[n][layer] = c;
        nodeSTID[n][layer] = sid;

        // Update initial depth if this is better
        if (bestInitialDepth.time > time) {
            bestInitialDepth.n = dist;
            bestInitialDepth.time = time;
            bestInitialSTID = sid;
        } else if (bestInitialDepth.time == time && bestInitialDepth.n < dist) {
            bestInitialDepth.n = dist;
            bestInitialSTID = sid;
        }

        // Recurse on 'children'
        for (Edge e : graph[n]) {
            if (e.n != p && !blocked[e.n]) recurseCentroid(e.n, n, dist + 1, Math.max(time, Math.max(firstActive[n], e.time)), c, sid, layer);
        }
    }

    void divideTree(int n, int layer) {
        n = findCentroid(n);

        // Setup the centroid
        setupCentroid(n, layer);
        // System.out.println("Centroid (layer " + layer + "): " + (n+1));
        // System.out.println("Info: " + centroidInfo[n]);

        blocked[n] = true;
        for (Edge e : graph[n]) {
            if (!blocked[e.n]) divideTree(e.n, layer + 1);
        }
    }

    int[] parent, subtreeSize;
    int findCentroid(int n) {
        findSubtreeSizes(n, n);
        // Try all possible centroids
        Queue<Integer> q = new LinkedList<>();
        q.add(n);
        int c, centroid = n, bestSTSize = N;
        while (!q.isEmpty()) {
            c = q.poll();
            int maxSTSize = subtreeSize[n] - subtreeSize[c];
            for (Edge e : graph[c]) {
                if (parent[c] != e.n && !blocked[e.n]) {
                    maxSTSize = Math.max(subtreeSize[e.n], maxSTSize);
                    q.add(e.n);
                }
            }

            if (maxSTSize < bestSTSize) {
                centroid = c;
                bestSTSize = maxSTSize;
            }
        }
        return centroid;
    }

    int findSubtreeSizes(int n, int p) {
        int currSTSize = 1;
        for (Edge e : graph[n]) {
            if (e.n != p && !blocked[e.n]) currSTSize += findSubtreeSizes(e.n, n);
        }
        parent[n] = p;
        subtreeSize[n] = currSTSize;
        return currSTSize;
    }

    public static void main(String[] args) throws IOException {
        new newbarn();
    }

    // Store 2 max subtree depths, the time at which this centroid becomes active, and the
    // initial subtree depth.
    static class CentroidInfo {
        int activeTime, max1, max1ID, max2, max2ID;
        CentroidInfo(int activeTime, int init, int initID) {
            this.activeTime = activeTime;
            max1 = init;
            max1ID = initID;
            max2 = 0;
            max2ID = -1;
        }

        // Convenience method; gets the max depth of a subtree that's not part of the excludeID one.
        int getMaxDepth(int excludeID) {
            if (max1ID == excludeID) return max2;
            else return max1;
        }

        // Add to two maxes if better
        void updateSTDepth(int id, int depth) {
            if (max1ID == id) {
                max1 = Math.max(max1, depth);
            }
            else if (max2ID == id) {
                max2 = Math.max(max2, depth);
                if (max2 > max1) {
                    // Swap 2nd and 1st maxes
                    int temp = max1;
                    max1 = max2;
                    max2 = temp;
                    temp = max1ID;
                    max1ID = max2ID;
                    max2ID = temp;
                }
            } else {
                // Not in top 2; is this better than any of the current ones?
                if (depth > max1) {
                    // Move max1 to max2, and set this to be max1
                    max2 = max1;
                    max2ID = max1ID;
                    max1 = depth;
                    max1ID = id;
                } else if (depth > max2) {
                    // Replace max2
                    max2 = depth;
                    max2ID = id;
                }
            }
        }

        public String toString() {
            return String.format("(active=%d, max1=[%d, %d], max2=[%d, %d])", activeTime, max1, max1ID, max2, max2ID);
        }
    }

    static class Query {
        int a, b;
        boolean isBuild;
        Query(int a, int b, boolean isBuild) {
            this.a = a;
            this.b = b;
            this.isBuild = isBuild;
        }
        public String toString() {
            return String.format("(%d, %d, %b)", a, b, isBuild);
        }
    }

    static class Edge {
        int n, time;
        Edge(int n, int time) {
            this.n = n;
            this.time = time;
        }
        public String toString() {
            return "(" + n + ", " + time + ")";
        }
    }
}
