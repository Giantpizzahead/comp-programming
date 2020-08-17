/*
Solution: Label the nodes in DFS order to make each subtree cover a contiguous range in a segment tree. Then, just
handle the queries using the segment tree. Lazily propagate the light switches; get query is just sum of a range.

Runtime: O((N + Q) * log(N))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class daniljob {
    int N, currID;
    int[] parent, startLabel, endLabel;
    boolean[] initLights;
    ArrayList<Integer>[] children;

    daniljob() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        children = new ArrayList[N];
        for (int i = 0; i < N; i++) children[i] = new ArrayList<>(2);
        st = new StringTokenizer(in.readLine());
        parent = new int[N];
        for (int i = 1; i < N; i++) {
            parent[i] = Integer.parseInt(st.nextToken()) - 1;
            children[parent[i]].add(i);
        }

        // Label nodes in DFS order
        startLabel = new int[N];
        endLabel = new int[N];
        currID = 0;
        labelDFS(0);

        initLights = new boolean[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) initLights[startLabel[i]] = st.nextToken().equals("1");

        // Handle queries online
        SegmentTree seg = new SegmentTree(N, initLights);
        int Q = Integer.parseInt(in.readLine());
        String type;
        int n;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            type = st.nextToken();
            n = Integer.parseInt(st.nextToken()) - 1;
            if (type.equals("pow")) {
                seg.flipLights(startLabel[n], endLabel[n]);
            } else {
                out.println(seg.query(startLabel[n], endLabel[n]));
            }
        }
        in.close();
        out.close();
    }

    void labelDFS(int n) {
        // Start label is also the node's actual label
        startLabel[n] = currID++;
        for (int c : children[n]) labelDFS(c);
        endLabel[n] = currID - 1;
    }

    public static void main(String[] args) throws IOException {
        new daniljob();
    }

    // All lights initally off
    static class SegmentTree {
        int size;
        int[] vals;
        boolean[] lazy;

        SegmentTree(int size, boolean[] initial) {
            this.size = size;
            vals = new int[size * 4 + 1];
            lazy = new boolean[size * 4 + 1];
            initTree(1, 0, size - 1, initial);
        }

        void initTree(int n, int lb, int ub, boolean[] initial) {
            if (lb == ub) {
                vals[n] = initial[lb] ? 1 : 0;
            } else {
                initTree(n * 2, lb, (lb + ub) / 2, initial);
                initTree(n * 2 + 1, (lb + ub) / 2 + 1, ub, initial);
                vals[n] = vals[n*2] + vals[n*2+1];
            }
        }

        void flipLights(int l, int r) {
            flipLights(1, 0, size - 1, l, r);
        }

        void flipLights(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return;
            else if (lb >= l && ub <= r) {
                lazy[n] = !lazy[n];
                vals[n] = calcVal(n, lb, ub);
                return;
            }

            propagate(n, lb, ub);
            flipLights(n*2, lb, (lb+ub)/2, l, r);
            flipLights(n*2+1, (lb+ub)/2+1, ub, l, r);
            vals[n] = vals[n*2] + vals[n*2+1];
        }

        int query(int l, int r) {
            return query(1, 0, size - 1, l, r);
        }

        int query(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return 0;
            else if (lb >= l && ub <= r) return vals[n];

            propagate(n, lb, ub);
            return query(n*2, lb, (lb+ub)/2, l, r) + query(n*2+1, (lb+ub)/2+1, ub, l, r);
        }

        // Flips lights
        int calcVal(int n, int lb, int ub) {
            return (ub - lb + 1) - vals[n];
        }

        void propagate(int n, int lb, int ub) {
            if (lazy[n]) {
                lazy[n] = false;
                vals[n*2] = calcVal(n*2, lb, (lb+ub)/2);
                lazy[n*2] = !lazy[n*2];
                vals[n*2+1] = calcVal(n*2+1, (lb+ub)/2+1, ub);
                lazy[n*2+1] = !lazy[n*2+1];
            }
        }
    }
}