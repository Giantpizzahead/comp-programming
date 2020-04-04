/*
Solution: Centroid decomposition with a bunch of stuff that I really don't want to describe right now. Basically, solve
the problem for all paths that go through / use the centroid, then recurse on the subtrees.

Runtime: O(N * log(N)^2)
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class exerciseDecomp {
    int N, M, currIterationID;
    long answer, toAddToAnswer;
    ArrayList<Integer>[] graphS, graphNonS;
    HashSet<Integer> nodesInST;
    int[] parent, stSize, depth, stID, iterationID, numPathsParentEdge;
    int[][] lcaArr;
    boolean[] blocked;
    final int MAX_LCA = 17;
    Queue<Path> currSTPaths, sameSTPaths;
    HashMap<Integer, Integer> pathsFromST = new HashMap<>(N);
    HashMap<Long, Integer> pathsFromTwoSTs = new HashMap<>(N);

    exerciseDecomp() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("exercise.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        graphS = new ArrayList[N];
        graphNonS = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            graphS[i] = new ArrayList<>(2);
            graphNonS[i] = new ArrayList<>(2);
        }
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graphS[a].add(b);
            graphS[b].add(a);
        }
        for (int i = 0; i < M - N + 1; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            if (a == b) continue;
            graphNonS[a].add(b);
            graphNonS[b].add(a);
        }
        fin.close();

        // Do centroid decomposition
        answer = 0;
        blocked = new boolean[N];
        parent = new int[N];
        depth = new int[N];
        stSize = new int[N];
        stID = new int[N];
        iterationID = new int[N];
        numPathsParentEdge = new int[N];
        lcaArr = new int[MAX_LCA][N];
        currSTPaths = new LinkedList<>();
        sameSTPaths = new LinkedList<>();
        currIterationID = 1;
        nodesInST = new HashSet<>();
        divideAndConquer(0);
        // solveTree(0);

        PrintWriter fout = new PrintWriter("exercise.out");
        fout.println(answer);
        fout.close();
    }

    void solveTree(int n) {
        // Label which subtree each node is in / setup the LCA array
        lcaArr[0][n] = n;
        depth[n] = 0;
        stID[n] = -1;
        nodesInST.clear();
        nodesInST.add(n);
        iterationID[n] = currIterationID;
        int currID = 0;
        for (int e : graphS[n]) {
            if (!blocked[e]) setupTree(e, n, currID++);
        }
        genLCAArray();
        // System.out.println(Arrays.toString(iterationID));
        // System.out.println(Arrays.toString(stID));
        // for (int i = 0; i < MAX_LCA; i++) System.out.println(Arrays.toString(lcaArr[i]));

        // Iterate through each subtree
        pathsFromST.clear();
        pathsFromTwoSTs.clear();
        for (int e : graphS[n]) {
            if (blocked[e]) continue;
            solveSubtree(e, n);
            // System.out.println(currSTPaths);
            // System.out.println("Num parent: " + Arrays.toString(numPathsParentEdge));

            // First, handle intersections between 1 path that goes through the vertex and a path that stays in the same
            // subtree
            toAddToAnswer = 0;
            handleInsidePaths();

            // Now, handle the rest of the intersections
            Path p;
            while (!currSTPaths.isEmpty()) {
                p = currSTPaths.poll();
                if (p.sta == p.stb) {
                    // Special case; just add it normally
                    int pathsFromA = pathsFromST.getOrDefault(p.sta, 0);
                    toAddToAnswer += pathsFromA;
                    pathsFromST.put(p.sta, pathsFromA + 1);
                } else {
                    // Inclusion-exclusion counting
                    int pathsFromA = pathsFromST.getOrDefault(p.sta, 0);
                    int pathsFromB = pathsFromST.getOrDefault(p.stb, 0);
                    int pathsFromAB = pathsFromTwoSTs.getOrDefault(hash(p.sta, p.stb), 0);
                    toAddToAnswer += pathsFromA + pathsFromB - pathsFromAB;
                    pathsFromST.put(p.sta, pathsFromA + 1);
                    pathsFromST.put(p.stb, pathsFromB + 1);
                    pathsFromTwoSTs.put(hash(p.sta, p.stb), pathsFromAB + 1);
                }
                // System.out.println("Added " + toAddToAnswer);
                // System.out.println(pathsFromST);
                // System.out.println(pathsFromTwoSTs);
            }
            answer += toAddToAnswer;
        }

        // System.out.println("solveTree(" + n + ") = " + result);
    }

    long hash(int a, int b) {
        return (long) a * 100001 + b;
    }

    void handleInsidePaths() {
        int a, b;
        Path p;
        while (!sameSTPaths.isEmpty()) {
            p = sameSTPaths.poll();
            // System.out.println(p);
            // Modified LCA algorithm
            a = (depth[p.sta] > depth[p.stb]) ? p.sta : p.stb;
            b = (depth[p.sta] > depth[p.stb]) ? p.stb : p.sta;

            // a may need to be moved up
            int amountToMove = depth[a] - depth[b];
            if (amountToMove != 0) {
                for (int i = MAX_LCA - 1; i >= 0; i--) {
                    if (amountToMove > 1 << i) {
                        amountToMove -= 1 << i;
                        a = lcaArr[i][a];
                    }
                }

                // amountToMove should now be 1; check if the top node is the LCA
                if (lcaArr[0][a] == b) {
                    // b is the LCA; # of intersecting paths is just the # of paths that crossed a's parent edge
                    // System.out.println("Adding # parent paths " + (a+1));
                    toAddToAnswer += numPathsParentEdge[a];
                    continue;
                }

                a = lcaArr[0][a];
            }

            // Find the LCA
            for (int i = MAX_LCA - 1; i >= 0; i--) {
                if (lcaArr[i][a] != lcaArr[i][b]) {
                    a = lcaArr[i][a];
                    b = lcaArr[i][b];
                }
            }

            // LCA is the parent of a and b; # of intersecting paths is the # of paths in both a and b's parent edges
            // System.out.println("Adding # parent paths " + (a+1) + " and " + (b+1));
            toAddToAnswer += numPathsParentEdge[a] + numPathsParentEdge[b];
        }
    }

    // Returns a queue with all the paths in the current subtree. Also adds the # of paths that intersect strictly
    // inside this subtree to the answer (1 that goes to centroid, 1 that stays inside).
    int solveSubtree(int n, int p) {
        int currPathsParentEdge = 0;

        // Add any non-standard paths to the queue
        for (int e : graphNonS[n]) {
            // To avoid overcounting, only add to curr paths if e > n
            if (iterationID[e] != currIterationID) continue;  // Other endpoint not in currently divided tree
            if (stID[n] == stID[e]) {
                // In the same subtree; handle this later
                if (e > n) sameSTPaths.add(new Path(n, e));
            } else if (stID[e] == -1) {
                // Connected to vertex; treat as same subtree, but add it
                currPathsParentEdge++;
                currSTPaths.add(new Path(stID[n], stID[n]));
            } else {
                // In two different subtrees
                currPathsParentEdge++;
                if (e > n) currSTPaths.add(new Path(stID[n], stID[e]));
            }
        }

        // DFS
        for (int e : graphS[n]) {
            if (e != p && !blocked[e]) {
                currPathsParentEdge += solveSubtree(e, n);
            }
        }

        numPathsParentEdge[n] = currPathsParentEdge;
        return currPathsParentEdge;
    }

    void genLCAArray() {
        Integer[] nodeArr = nodesInST.toArray(new Integer[0]);
        for (int i = 1; i < MAX_LCA; i++) {
            for (int n : nodeArr) {
                lcaArr[i][n] = lcaArr[i-1][lcaArr[i-1][n]];
            }
        }
    }

    void setupTree(int n, int p, int id) {
        lcaArr[0][n] = p;
        depth[n] = depth[p] + 1;
        stID[n] = id;
        iterationID[n] = currIterationID;
        nodesInST.add(n);
        for (int e : graphS[n]) {
            if (e != p && !blocked[e]) {
                setupTree(e, n, id);
            }
        }
    }

    void divideAndConquer(int n) {
        currIterationID++;
        n = findCentroid(n);
        solveTree(n);

        blocked[n] = true;
        for (int e : graphS[n]) {
            if (!blocked[e]) divideAndConquer(e);
        }
    }

    int findCentroid(int n) {
        findSubtreeSizes(n, n);
        int centroid = n, maxST = n, maxSTSize = 999999;
        Queue<Integer> q = new LinkedList<>();
        q.add(n);
        int c;
        while (!q.isEmpty()) {
            c = q.poll();
            int cmaxSTSize = stSize[n] - stSize[c];
            for (int e : graphS[c]) {
                if (e != parent[c] && !blocked[e]) {
                    cmaxSTSize = Math.max(stSize[e], cmaxSTSize);
                    q.add(e);
                }
            }

            if (cmaxSTSize < maxSTSize) {
                centroid = c;
                maxSTSize = cmaxSTSize;
            }
        }
//        while (true) {
//            maxSTSize = 0;
//            for (int e : graphS[centroid]) {
//                if (e != parent[centroid] && !blocked[e] && stSize[e] > maxSTSize) {
//                    maxST = e;
//                    maxSTSize = stSize[e];
//                }
//            }
//
//            int upSTSize = stSize[n] - stSize[centroid];
//            if (upSTSize > maxSTSize) {
//                maxST = parent[centroid];
//                maxSTSize = upSTSize;
//            }
//
//            // Check if it's a valid centroid
//            if (maxSTSize <= stSize[n] / 2) {
//                break;
//            } else centroid = maxST;
//        }
//        System.out.println("Centroid: " + (centroid + 1));
        return centroid;
    }

    int findSubtreeSizes(int n, int p) {
        parent[n] = p;
        int currSTSize = 1;
        for (int e : graphS[n]) {
            if (e != p && !blocked[e]) {
                currSTSize += findSubtreeSizes(e, n);
            }
        }
        stSize[n] = currSTSize;
        return currSTSize;
    }

    public static void main(String[] args) throws IOException {
        new exerciseDecomp();
    }

    class Path {
        int sta, stb;
        Path(int sta, int stb) {
            this.sta = Math.min(sta, stb);
            this.stb = Math.max(sta, stb);
        }
        @Override
        public String toString() {
            return "(" + sta + ", " + stb + ")";
        }
    }
}
