import java.util.*;

@SuppressWarnings("unchecked")
public class werewolf {
    int N, M, Q;
    int[] queryL, queryR, queryS, queryE;
    ArrayList<Integer>[] adj;

    int[] check_validity(int N, int[] X, int[] Y, int[] S, int[] E, int[] L, int[] R) {
        this.N = N;
        Q = S.length;
        M = X.length;
        queryS = S;
        queryE = E;
        queryL = L;
        queryR = R;
        int[] numEdges = new int[N];
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);
        for (int i = 0; i < M; i++) {
            adj[X[i]].add(Y[i]);
            adj[Y[i]].add(X[i]);
            numEdges[X[i]]++;
            numEdges[Y[i]]++;
        }

        // Subtask 3?
        int maxEdges = 0, first1Edge = -1;
        for (int i = 0; i < N; i++) {
            if (numEdges[i] == 1 && first1Edge == -1) {
                first1Edge = i;
            }
            maxEdges = Math.max(numEdges[i], maxEdges);
            if (maxEdges > 2) break;
        }

        if (maxEdges <= 2) {
            return solveLine(first1Edge);
        } else {
            return solveSmall();
        }
    }

    int[] solveSmall() {
        // Simulate all the queries using a BFS
        int[] ans = new int[Q];
        for (int i = 0; i < Q; i++) {
            ans[i] = check(queryS[i], queryE[i], queryL[i], queryR[i]);
        }
        return ans;
    }

    int check(int s, int e, int l, int r) {
        boolean[] visitedHuman = new boolean[N];
        boolean[] visitedWolf = new boolean[N];
        visitedHuman[s] = true;
        Queue<State> q = new LinkedList<>();
        q.add(new State(s, true));

        State c;
        while (!q.isEmpty()) {
            c = q.poll();
            // Switch to werewolf here?
            if (c.isHuman && c.n <= r && !visitedWolf[c.n]) {
                visitedWolf[c.n] = true;
                q.add(new State(c.n, false));
            }
            // Has the end been reached?
            if (!c.isHuman && c.n == e) return 1;  // Yes!
            // Explore neighbors
            if (c.isHuman) {
                for (int o : adj[c.n]) {
                    if (o >= l && !visitedHuman[o]) {
                        visitedHuman[o] = true;
                        q.add(new State(o, true));
                    }
                }
            } else {
                for (int o : adj[c.n]) {
                    if (o <= r && !visitedWolf[o]) {
                        visitedWolf[o] = true;
                        q.add(new State(o, false));
                    }
                }
            }
        }
        return 0;  // End couldn't be reached
    }

    static class State {
        int n;
        boolean isHuman;
        State(int n, boolean isHuman) {
            this.n = n;
            this.isHuman = isHuman;
        }
    }

    int[] iToNode, nodeToI;
    Query[] queries;
    int[] solveLine(int first1Edge) {
        queries = new Query[Q];
        for (int i = 0; i < Q; i++) queries[i] = new Query(queryS[i], queryE[i], queryL[i], queryR[i], i);
        // Sort by decreasing L
        Arrays.sort(queries, new Comparator<Query>() {
            @Override
            public int compare(Query o1, Query o2) {
                return o2.l - o1.l;
            }
        });

        // Traverse the line
        iToNode = new int[N];
        nodeToI = new int[N];
        int curr = first1Edge, last = -1;
        for (int i = 0; i < N; i++) {
            iToNode[i] = curr;
            nodeToI[curr] = i;
            for (int e : adj[curr]) {
                if (e != last) {
                    last = curr;
                    curr = e;
                    break;
                }
            }
        }
        // System.out.println(Arrays.toString(iToNode));
        // System.out.println(Arrays.toString(nodeToI));

        // Generate segment tree
        SegmentTree segt = new SegmentTree(N);

        // Keep disjoint set with furthest reachable locations for each L
        DisjointSet ds = new DisjointSet(N);
        int[] ans = new int[Q];
        int lastL = N - 1;
        for (Query q : queries) {
            int startI = nodeToI[q.s];
            int endI = nodeToI[q.e];

            // Add new nodes that can now be used
            while (lastL >= q.l) {
                ds.activate(nodeToI[lastL]);
                for (int e : adj[lastL]) ds.merge(nodeToI[e], nodeToI[lastL]);
                lastL--;
            }

            if (q.s <= lastL) {
                // Can't be human at the start node (edge case)
                ans[q.origI] = 0;
                continue;
            }

            if (startI < endI) {
                // Traveling right; can the other node be reached in werewolf form?
                int maxRightLoc = Math.min(ds.setMaxRight[ds.find(startI)], endI);
                int maxLabel = segt.query(maxRightLoc, endI);
                if (maxLabel > q.r) {
                    // Cannot transform and reach target city
                    ans[q.origI] = 0;
                } else {
                    // Can transform and reach target city
                    ans[q.origI] = 1;
                }
            } else {
                // Traveling left
                int maxLeftLoc = Math.max(ds.setMaxLeft[ds.find(startI)], endI);
                int maxLabel = segt.query(endI, maxLeftLoc);
                // System.out.println(q.s + " " + q.e + " -> " + maxLeftLoc + ", " + maxLabel);
                if (maxLabel > q.r) {
                    // Cannot transform and reach target city
                    ans[q.origI] = 0;
                } else {
                    // Can transform and reach target city
                    ans[q.origI] = 1;
                }
            }
        }
        return ans;
    }

    // Max segment tree
    class SegmentTree {
        int size;
        int[] vals;

        SegmentTree(int size) {
            this.size = size;
            vals = new int[size * 4 + 1];
            initTree(1, 0, size - 1);
        }

        int query(int l, int r) {
            return query(1, 0, size - 1, l, r);
        }

        int query(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return 0;
            else if (lb >= l && ub <= r) return vals[n];
            else return Math.max(query(n*2, lb, (lb+ub)/2, l, r), query(n*2+1, (lb+ub)/2+1, ub, l, r));
        }

        void initTree(int n, int lb, int ub) {
            if (lb == ub) {
                vals[n] = iToNode[lb];
            } else {
                initTree(n*2, lb, (lb+ub)/2);
                initTree(n*2+1, (lb+ub)/2+1, ub);
                vals[n] = Math.max(vals[n*2], vals[n*2+1]);
            }
        }
    }

    static class DisjointSet {
        int size;
        int[] vals, setMaxLeft, setMaxRight;
        boolean[] isActive;

        DisjointSet(int size) {
            this.size = size;
            vals = new int[size];
            Arrays.fill(vals, -1);
            setMaxLeft = new int[size];
            setMaxRight = new int[size];
            isActive = new boolean[size];
        }
        
        void merge(int a, int b) {
            if (!(isActive[a] && isActive[b])) return;
            int setA = find(a);
            int setB = find(b);
            if (setA == setB) return;
            if (vals[setA] < vals[setB]) {
                vals[setA] += vals[setB];
                setMaxLeft[setA] = Math.min(setMaxLeft[setA], setMaxLeft[setB]);
                setMaxRight[setA] = Math.max(setMaxRight[setA], setMaxRight[setB]);
                setMaxLeft[setB] = -1;
                setMaxRight[setB] = -1;
                vals[setB] = setA;
            } else {
                vals[setB] += vals[setA];
                setMaxLeft[setB] = Math.min(setMaxLeft[setB], setMaxLeft[setA]);
                setMaxRight[setB] = Math.max(setMaxRight[setB], setMaxRight[setA]);
                setMaxLeft[setA] = -1;
                setMaxRight[setA] = -1;
                vals[setA] = setB;
            }
        }

        void activate(int i) {
            isActive[i] = true;
            setMaxLeft[i] = i;
            setMaxRight[i] = i;
        }

        int find(int i) {
            if (vals[i] < 0) return i;
            else {
                int res = find(vals[i]);
                vals[i] = res;
                return res;
            }
        }
    }

    static class Query {
        int s, e, l, r, origI;
        Query(int ss, int ee, int ll, int rr, int i) {
            s = ss;
            e = ee;
            l = ll;
            r = rr;
            origI = i;
        }
    }
}
