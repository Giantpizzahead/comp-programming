/*
Solution: Trying the centroid decomposition solution, since I've never done centroid decomp before... Well, there's a
first time for everything! :)

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class yinyangDecomp {
    int N, offset, seenMin, seenMax, maxSTSize;
    ArrayList<Edge>[] graph;
    boolean[] blocked;
    int[] stSizes, parent, preNoRest, preRest;
    Queue<Path> currPaths;

    yinyangDecomp() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("yinyang.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        offset = N - 1;
        graph = new ArrayList[N];
        blocked = new boolean[N];
        stSizes = new int[N];
        parent = new int[N];
        preNoRest = new int[N * 2 - 1];
        preRest = new int[N * 2 - 1];
        currPaths = new LinkedList<>();
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        int a, b, c;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            c = (Integer.parseInt(st.nextToken()) == 1) ? 1 : -1;
            graph[a].add(new Edge(b, c));
            graph[b].add(new Edge(a, c));
        }
        fin.close();

        // for (int i = 0; i < N; i++) System.out.println((i + 1) + " -> " + solveTree(i, N-1));
        long answer = divideTree(0);

        PrintWriter fout = new PrintWriter("yinyang.out");
        fout.println(answer);
        fout.close();
    }

    long divideTree(int n) {
        // Readjust n to be the centroid of the tree
        n = findCentroid(n);
        // System.out.println("Centroid: " + (n + 1));
        long answer = solveTree(n, maxSTSize);
        blocked[n] = true;
        for (Edge e : graph[n]) {
            if (!blocked[e.n]) answer += divideTree(e.n);
        }
        return answer;
    }

    long solveTree(int n, int maxSTSize) {
        // Reset part of array as needed
        Arrays.fill(preNoRest, offset - maxSTSize, offset + maxSTSize + 1, 0);
        Arrays.fill(preRest, offset - maxSTSize, offset + maxSTSize + 1, 0);
        long answer = 0;

        for (Edge e : graph[n]) {
            if (!blocked[e.n]) {
                seenMin = 999999;
                seenMax = e.c;
                findPaths(e.n, n, e.c);
                // System.out.println(currPaths);

                // Add found paths to answer
                for (Path p : currPaths) {
                    if (p.r || p.c == 0) {
                        // Can be paired with no rest path
                        answer += preNoRest[-p.c + offset];
                    }
                    answer += preRest[-p.c + offset];

                    if (p.r && p.c == 0) answer++;  // Special case; endpoint is the root node
                }

                // Add found paths to prefix subtrees
                Path p;
                while (!currPaths.isEmpty()) {
                    p = currPaths.poll();
                    if (p.r) preRest[p.c + offset]++;
                    else preNoRest[p.c + offset]++;
                }
            }
        }
        // System.out.println("solveTree(" + n + ") = " + answer);
        return answer;
    }

    void findPaths(int n, int p, int sum) {
        int toChange;
        if (seenMin > sum) {
            seenMin = sum;
            toChange = -1;
            currPaths.add(new Path(sum, false));
        } else if (seenMax < sum) {
            seenMax = sum;
            toChange = 1;
            currPaths.add(new Path(sum, false));
        } else {
            // Seen before; this path has a rest point
            toChange = 0;
            currPaths.add(new Path(sum, true));
        }

        for (Edge e : graph[n]) {
            if (e.n != p && !blocked[e.n]) {
                findPaths(e.n, n, sum + e.c);
            }
        }

        // Do backpropagation
        if (toChange == -1) seenMin++;
        else if (toChange == 1) seenMax--;
    }

    int getSTSizes(int n, int p) {
        parent[n] = p;
        int stSize = 1;
        for (Edge e : graph[n]) {
            if (e.n != p && !blocked[e.n]) {
                stSize += getSTSizes(e.n, n);
            }
        }
        stSizes[n] = stSize;
        return stSize;
    }

    int findCentroid(int root) {
        getSTSizes(root, root);
        Queue<Integer> q = new LinkedList<>();
        q.add(root);
        int centroid = root;
        maxSTSize = stSizes[root];
        int c, currSTSize;
        while (!q.isEmpty()) {
            c = q.poll();
            currSTSize = stSizes[root] - stSizes[c];
            for (Edge e : graph[c]) {
                if (e.n != parent[c] && !blocked[e.n]) {
                    currSTSize = Math.max(stSizes[e.n], currSTSize);
                    q.add(e.n);
                }
            }

            if (currSTSize < maxSTSize) {
                // New best centroid
                centroid = c;
                maxSTSize = currSTSize;
            }
        }
        return centroid;
    }

    public static void main(String[] args) throws IOException {
        new yinyangDecomp();
    }

    static class Edge {
        int n, c;
        Edge(int nn, int cc) {
            n = nn;
            c = cc;
        }
    }

    static class Path {
        int c;
        boolean r;
        Path(int cc, boolean rr) {
            c = cc;
            r = rr;
        }
        @Override
        public String toString() {
            return "(" + c + ", " + r + ")";
        }
    }
}