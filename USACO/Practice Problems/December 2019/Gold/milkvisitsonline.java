/*
Solution: Solving this problem online in O((N+M) * log(N)).
Each query can be solved by counting the # of nodes of the target type on
the path. If this is non-zero, then the query answer is 1.
Reduce the queries to (root, a) + (root, b) - (root, lca(a, b)). That way,
you only have to keep track of the # of nodes of a specific type from the
root. This can be done in linearithmic time.

Runtime: O((N+M) * log(N))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class milkvisitsonline {
    final int MAX_LCA = 18, MAX_TYPE = 100000;
    int N, M;
    int[] type, depth, slabel, elabel;
    int[][] lcaArr;
    Pair[][] typeLookup;
    ArrayList<Integer>[] adj;
    ArrayList<Pair>[] typePairs;

    milkvisitsonline(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        type = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) type[i] = Integer.parseInt(st.nextToken()) - 1;
        adj = new ArrayList[N];
        typePairs = new ArrayList[MAX_TYPE];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);
        for (int i = 0; i < MAX_TYPE; i++) {
            typePairs[i] = new ArrayList<>(2);
            typePairs[i].add(new Pair(0, 0));
        }
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            adj[a].add(b);
            adj[b].add(a);
        }

        // Label nodes / generate LCA array
        depth = new int[N];
        slabel = new int[N];
        elabel = new int[N];
        lcaArr = new int[MAX_LCA][N];
        genTreeInfo(0, 0, 0);
        fillLCAArr();

        // Generate # of nodes lookup table for all types
        // Later on, use floor() to get the # of nodes from this table
        typeLookup = new Pair[MAX_TYPE][];
        for (int i = 0; i < MAX_TYPE; i++) {
            typeLookup[i] = new Pair[typePairs[i].size()];
            int currNum = 0;
            for (int j = 0; j < typeLookup[i].length; j++) {
                currNum += typePairs[i].get(j).b;
                typeLookup[i][j] = new Pair(typePairs[i].get(j).a, currNum);
            }
            // if (typeLookup[i].length != 1) System.out.println(Arrays.toString(typeLookup[i]));
        }

        // Answer queries online
        int t;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            t = Integer.parseInt(st.nextToken()) - 1;
            int lca = getLCA(a, b);
            int numNodes = getNum(slabel[a], t) + getNum(slabel[b], t);
            numNodes -= 2 * getNum(slabel[lca], t);
            if (type[lca] == t || numNodes > 0) out.print(1);
            else out.print(0);
        }
        out.println();
    }

    int getNum(int loc, int t) {
        int res = Arrays.binarySearch(typeLookup[t], new Pair(loc, 0));
        if (res < 0) res = -res - 2;
        // System.out.println(Arrays.toString(typeLookup[t]));
        // System.out.println("bin " + loc + ", res " + typeLookup[t][res]);
        return typeLookup[t][res].b;
    }

    int getLCA(int a, int b) {
        int n1, n2;
        if (depth[a] < depth[b]) {
            n1 = a;
            n2 = b;
        } else {
            n1 = b;
            n2 = a;
        }

        int toMove = depth[n2] - depth[n1];
        for (int i = MAX_LCA - 1; i >= 0; i--) {
            if ((1 << i) <= toMove) {
                n2 = lcaArr[i][n2];
                toMove -= 1 << i;
            }
        }

        if (n1 == n2) return n1;

        for (int i = MAX_LCA - 1; i >= 0; i--) {
            if (lcaArr[i][n1] != lcaArr[i][n2]) {
                n1 = lcaArr[i][n1];
                n2 = lcaArr[i][n2];
            }
        }
        return lcaArr[0][n1];
    }

    int clabel = 1;
    void genTreeInfo(int n, int p, int d) {
        lcaArr[0][n] = p;
        depth[n] = d;
        Pair last = typePairs[type[n]].get(typePairs[type[n]].size() - 1);
        if (last.a == clabel) last.b++;
        else typePairs[type[n]].add(new Pair(clabel, 1));
        slabel[n] = clabel++;
        for (int e : adj[n]) {
            if (e != p) genTreeInfo(e, n, d+1);
        }
        elabel[n] = clabel - 1;
        last = typePairs[type[n]].get(typePairs[type[n]].size() - 1);
        if (last.a == clabel) last.b--;
        else typePairs[type[n]].add(new Pair(clabel, -1));
    }

    void fillLCAArr() {
        for (int i = 1; i < MAX_LCA; i++) {
            for (int n = 0; n < N; n++) {
                lcaArr[i][n] = lcaArr[i-1][lcaArr[i-1][n]];
            }
        }
    }

    class Pair implements Comparable<Pair> {
        int a, b;
        Pair(int aa, int bb) {
            a = aa;
            b = bb;
        }

        public String toString() {
            return "(" + a + ", " + b + ")";
        }

        @Override
        public int compareTo(Pair o) {
            return a - o.a;
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        BufferedReader in = new BufferedReader(new FileReader("milkvisits.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("milkvisits.out")));
        new milkvisitsonline(in, out);
        in.close();
        out.close();
    }
}