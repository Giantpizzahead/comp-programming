/*
Solution: Simplify the problem by treating non-standard trails from A to B as 1 trail from A to
lca(A, B) and 1 from lca(A, B) to B. Then, do a simple DP to figure out the # of pairs of trails
that overlap. Subtract the # of overcounted trails (LCA / 2 edges are equal -> 2 bottom nodes are
equal) to get your answer.

I looked at the official solution to figure this out. Oh well. I almost had it.

Runtime: O(M * log(M))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class exercise {
    int N, M, maxDepth = 0;
    long answer = 0;
    int[] depth;
    int[][] lcaArr;
    boolean[] edgeUsed;
    ArrayList<Integer>[] graphS, nodesWithDepth;
    ArrayList<Pair>[] graphNonS;
    Pair[] nonSEdgeList, edgeLCA;
    final int MAX_LCA = 18;

    exercise() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("exercise.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        graphS = new ArrayList[N];
        graphNonS = new ArrayList[N];
        nodesWithDepth = new ArrayList[N];
        nonSEdgeList = new Pair[M - N + 1];
        for (int i = 0; i < N; i++) {
            graphS[i] = new ArrayList<>(2);
            graphNonS[i] = new ArrayList<>(2);
            nodesWithDepth[i] = new ArrayList<>(2);
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
            graphNonS[a].add(new Pair(b, i));
            graphNonS[b].add(new Pair(a, i));
            nonSEdgeList[i] = new Pair(a, b);
        }
        fin.close();

        depth = new int[N];
        lcaArr = new int[N][MAX_LCA];
        edgeLCA = new Pair[M - N + 1];
        edgeUsed = new boolean[M - N + 1];
        getNodeDepths(0, 0, 0);
        genLCAInfo();
        doDP();
        removeOvercount();

        PrintWriter fout = new PrintWriter("exercise.out");
        fout.println(answer);
        fout.close();
    }

    void removeOvercount() {
        HashMap<Long, Integer> numWithLCAs = new HashMap<>();
        for (Pair lcaResult : edgeLCA) {
            if (lcaResult.b == -1) continue;
            int temp = numWithLCAs.getOrDefault(hash(lcaResult.a, lcaResult.b), 0);
            answer -= temp;
            numWithLCAs.put(hash(lcaResult.a, lcaResult.b), temp + 1);
        }
    }

    long hash(int a, int b) {
        return (long) Math.min(a, b) * 200001 + Math.max(a, b);
    }

    void doDP() {
        int[] activePaths = new int[N];
        int[] numToAdd = new int[N];
        Queue<Integer>[] pathsToRemove = new LinkedList[N];
        for (int i = 0; i < N; i++) pathsToRemove[i] = new LinkedList<Integer>();
        for (int i = maxDepth; i >= 0; i--) {
            for (int n : nodesWithDepth[i]) {
                // Remove paths as needed
                int c;
                while (!pathsToRemove[n].isEmpty()) {
                    c = pathsToRemove[n].poll();
                    activePaths[c]--;
                }
                // Update activePaths with sum of children
                long prefix = 0;
                for (int e : graphS[n]) {
                    if (e != lcaArr[n][0]) {
                        answer += prefix * activePaths[e];
                        prefix += activePaths[e];
                        activePaths[n] += activePaths[e];
                    }
                }

                // Process any new non-standard edges
                for (Pair e : graphNonS[n]) {
                    if (!edgeUsed[e.b]) {
                        edgeUsed[e.b] = true;
                        if (edgeLCA[e.b].b == -1) {
                            // Simple edge (no split needed)
                            numToAdd[n]++;
                            pathsToRemove[e.a].add(edgeLCA[e.b].a);
                        } else {
                            // Split at LCA
                            numToAdd[n]++;
                            numToAdd[e.a]++;
                            int lca = lcaArr[edgeLCA[e.b].a][0];
                            pathsToRemove[lca].add(edgeLCA[e.b].a);
                            pathsToRemove[lca].add(edgeLCA[e.b].b);
                        }
                    }
                }

                // Handle added paths
                while (numToAdd[n] > 0) {
                    answer += activePaths[n];
                    activePaths[n]++;
                    numToAdd[n]--;
                }
            }
        }

        // System.out.println(Arrays.toString(activePaths));
    }

    Pair lca(int a, int b) {
        int n1, n2;
        if (depth[a] > depth[b]) {
            n1 = a;
            n2 = b;
        } else {
            n1 = b;
            n2 = a;
        }

        int toMove = depth[n1] - depth[n2];
        if (toMove != 0) {
            for (int i = MAX_LCA - 1; i >= 0; i--) {
                if (toMove > 1 << i) {
                    toMove -= 1 << i;
                    n1 = lcaArr[n1][i];
                }
            }

            if (lcaArr[n1][0] == n2) return new Pair(n1, -1);
            else n1 = lcaArr[n1][0];
        }

        for (int i = MAX_LCA - 1; i >= 0; i--) {
            if (lcaArr[n1][i] != lcaArr[n2][i]) {
                n1 = lcaArr[n1][i];
                n2 = lcaArr[n2][i];
            }
        }

        return new Pair(n1, n2);
    }

    void genLCAInfo() {
        for (int i = 1; i < MAX_LCA; i++) {
            for (int n = 0; n < N; n++) {
                lcaArr[n][i] = lcaArr[lcaArr[n][i-1]][i-1];
            }
        }

        // Precompute LCA for all non-standard edges
        for (int i = 0; i < M - N + 1; i++) {
            edgeLCA[i] = lca(nonSEdgeList[i].a, nonSEdgeList[i].b);
        }
        // System.out.println(Arrays.toString(edgeLCA));
    }

    void getNodeDepths(int n, int p, int d) {
        depth[n] = d;
        lcaArr[n][0] = p;
        nodesWithDepth[d].add(n);
        maxDepth = Math.max(d, maxDepth);
        for (int e : graphS[n]) {
            if (e != p) getNodeDepths(e, n, d+1);
        }
    }

    public static void main(String[] args) throws IOException {
        new exercise();
    }

    class Pair {
        int a, b;
        Pair(int aa, int bb) {
            a = aa;
            b = bb;
        }
        @Override
        public String toString() {
            return "(" + a + ", " + b + ")";
        }
    }
}
