/*
NOTE - This isn't an in-contest submission; it's just for practice.

Solution: Any tree can be labeled in such a way that each subtree takes on a contiguous range of
labels. So, label the tree in DFS order, and make a segment tree out of that.

To keep from overcounting non-distinct splashes of color, do a DFS from the root, tracking the
latest time each color has been used so far. When processing a new splash query, add it's latest
time if needed, and set its remove time to be the last found splash time for that color (since any
previously added queries completely void the current query).

Now, just simulate the splashes, removing queries when they become outdated. By doing it this way,
the query just becomes a simple range sum.

Runtime: O(N + Q * log(N))
*/

import javax.swing.text.Segment;
import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class snowcow {
    int N, Q;
    // startLabel is the same as that node's label
    int[] parent, startLabel, endLabel;
    Query[] queries;
    ArrayList<Integer>[] graph;
    ArrayList<Query>[] queriesOnNode, queriesToRemove;

    snowcow() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("snowcow.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        queriesOnNode = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<>(2);
            queriesOnNode[i] = new ArrayList<>(2);
        }
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graph[a].add(b);
            graph[b].add(a);
        }

        queries = new Query[Q];
        int t, n, c;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(fin.readLine());
            t = Integer.parseInt(st.nextToken());
            n = Integer.parseInt(st.nextToken()) - 1;
            if (t == 1) c = Integer.parseInt(st.nextToken()) - 1;
            else c = -1;
            queries[i] = new Query(t, n, c, i);
            if (t == 1) queriesOnNode[n].add(queries[i]);
        }

        fin.close();

        // Tree preprocessing / labeling
        parent = new int[N];
        startLabel = new int[N];
        endLabel = new int[N];
        genTreeInfo(0, 0, 0);

        // System.out.println(Arrays.toString(startLabel));
        // System.out.println(Arrays.toString(endLabel));

        // First, find out when each query needs to be removed
        queriesToRemove = new ArrayList[Q];
        for (int i = 0; i < Q; i++) queriesToRemove[i] = new ArrayList<>(2);
        colorRemoveTimes = new Stack[100000];
        for (int i = 0; i < 100000; i++) colorRemoveTimes[i] = new Stack<>();
        findRemoveTimes(0);

        // System.out.println(Arrays.toString(queriesToRemove));

        // Now, simulate the queries with a segment tree
        PrintWriter fout = new PrintWriter("snowcow.out");
        simulateQueries(fout);
        fout.close();
    }

    void simulateQueries(PrintWriter fout) {
        SegmentTree st = new SegmentTree(N);
        Query q;
        for (int i = 0; i < Q; i++) {
            q = queries[i];
            // First, remove any previous queries
            for (Query qToRemove : queriesToRemove[i]) {
                if (!qToRemove.useless) st.update(startLabel[qToRemove.node], endLabel[qToRemove.node], -1);
            }

            if (q.type == 1) {
                // Add current splash if not useless
                if (!q.useless) st.update(startLabel[q.node], endLabel[q.node], 1);
            } else {
                // Sum range / report answer
                fout.println(st.query(startLabel[q.node], endLabel[q.node]));
            }
        }
    }

    int genTreeInfo(int n, int p, int currLabel) {
        startLabel[n] = currLabel;
        parent[n] = p;
        for (int e : graph[n]) {
            if (e != p) currLabel = genTreeInfo(e, n, ++currLabel);
        }
        endLabel[n] = currLabel;
        return currLabel;
    }

    Stack<Query>[] colorRemoveTimes;
    void findRemoveTimes(int n) {
        // Process all current queries
        for (Query q : queriesOnNode[n]) {
            // Set remove time if needed
            while (!colorRemoveTimes[q.color].isEmpty()) {
                Query otherQ = colorRemoveTimes[q.color].peek();
                if (otherQ.time < q.time) {
                    // This splash is useless
                    q.useless = true;
                    break;
                } else if (otherQ.node == q.node && q.time < otherQ.time) {
                    // The other splash is useless
                    otherQ.useless = true;
                    colorRemoveTimes[q.color].pop();
                } else {
                    // Record remove time
                    queriesToRemove[otherQ.time].add(q);
                    break;
                }
            }

            // Add to correct stack if needed
            if (!q.useless) {
                q.addedToRemove = true;
                colorRemoveTimes[q.color].add(q);
            }
        }

        // Recurse
        for (int e : graph[n]) {
            if (e != parent[n]) findRemoveTimes(e);
        }

        // Backtrack by removing queries
        for (Query q : queriesOnNode[n]) {
            if (q.addedToRemove) colorRemoveTimes[q.color].pop();
        }
    }

    public static void main(String[] args) throws IOException {
        new snowcow();
    }

    static class Query {
        int type, node, color, time;
        boolean useless, addedToRemove;
        Query(int ty, int n, int c, int ti) {
            type = ty;
            node = n;
            color = c;
            time = ti;
            useless = false;
            addedToRemove = false;
        }
        public String toString() {
            return String.format("(%d, %d, %d, %b)", node, color, time, useless);
        }
    }

    static class SegmentTree {
        int size;
        long[] vals, delta;
        SegmentTree(int size) {
            this.size = size;
            vals = new long[size * 4 + 1];
            delta = new long[size * 4 + 1];
        }

        void update(int low, int high, int val) {
            update(1, 0, size - 1, low, high, val);
        }

        void update(int n, int lb, int ub, int low, int high, int val) {
            if (lb > high || ub < low) return;
            else if (lb >= low && ub <= high) {
                delta[n] += val;
                return;
            }

            propagate(n, lb, ub);
            update(n*2, lb, (lb+ub)/2, low, high, val);
            update(n*2+1, (lb+ub)/2+1, ub, low, high, val);
            vals[n] = calc(n*2, lb, (lb+ub)/2) + calc(n*2+1, (lb+ub)/2+1, ub);
        }

        long query(int low, int high) {
            return query(1, 0, size - 1, low, high);
        }

        long query(int n, int lb, int ub, int low, int high) {
            if (lb > high || ub < low) return 0;
            else if (lb >= low && ub <= high) return calc(n, lb, ub);

            propagate(n, lb, ub);
            return query(n*2, lb, (lb+ub)/2, low, high) + query(n*2+1, (lb+ub)/2+1, ub, low, high);
        }

        void propagate(int n, int lb, int ub) {
            vals[n] = calc(n, lb, ub);
            delta[n*2] += delta[n];
            delta[n*2+1] += delta[n];
            delta[n] = 0;
        }

        long calc(int n, int lb, int ub) {
            return vals[n] + delta[n] * (ub - lb + 1);
        }
    }
}
