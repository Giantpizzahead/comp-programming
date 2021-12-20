package GSS;/*
Solution: Same as GSS1, but with an update function.

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class GSS3 {
    int N, M;
    int[] arr;
    SegmentTree seg;

    GSS3() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        arr = new int[N];
        for (int i = 0; i < N; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
        }
        seg = new SegmentTree(N, arr);
        // Handle queries
        M = Integer.parseInt(in.readLine());
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            if (Integer.parseInt(st.nextToken()) == 0) {
                // Modify
                seg.update(Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()));
            } else {
                // Query
                out.println(seg.query(Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1));
            }
        }
        in.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new GSS3();
    }
}

class SegmentTree {
    int size;
    int[] s, ls, rs, ms, lb, ub, origArr;
    final int INF = 987654321;

    SegmentTree(int size, int[] arr) {
        this.size = size;
        s = new int[size * 4 + 1];
        ls = new int[size * 4 + 1];
        rs = new int[size * 4 + 1];
        ms = new int[size * 4 + 1];
        lb = new int[size * 4 + 1];
        ub = new int[size * 4 + 1];
        origArr = arr;
        initTree(1, 0, size-1);
    }

    void update(int i, int val) {
        update(1, i, val);
    }

    void update(int node, int i, int val) {
        if (lb[node] > i || ub[node] < i) return;
        else if (lb[node] == ub[node]) {
            // Leaf node
            s[node] = val;
            ls[node] = val;
            rs[node] = val;
            ms[node] = val;
            return;
        }

        // Recurse
        update(node * 2, i, val);
        update(node * 2 + 1, i, val);

        // Update this node's values
        int left = node * 2;
        int right = node * 2 + 1;
        s[node] = s[left] + s[right];
        ls[node] = Math.max(ls[left], s[left] + ls[right]);
        rs[node] = Math.max(rs[right], s[right] + rs[left]);
        ms[node] = Math.max(Math.max(ms[left], ms[right]), rs[left] + ls[right]);
    }

    int query(int low, int high) {
        // System.out.println(Arrays.toString(vals));
        return query(1, low, high).ms;
    }

    Result query(int node, int low, int high) {
        if (lb[node] >= low && ub[node] <= high) return new Result(s[node], ls[node], rs[node], ms[node]);
        else if (ub[node * 2] < low) {
            // Only right node needs to be checked
            return query(node * 2 + 1, low, high);
        } else if (lb[node * 2 + 1] > high) {
            // Only left node
            return query(node * 2, low, high);
        } else {
                // Recurse / return appropriate values
                Result left = query(node * 2, low, high);
                Result right = query(node * 2 + 1, low, high);
                return new Result(
                        left.s + right.s,
                        Math.max(left.ls, left.s + right.ls),
                        Math.max(right.rs, right.s + left.rs),
                        Math.max(Math.max(left.ms, right.ms), left.rs + right.ls));
        }
    }

    void initTree(int node, int low, int high) {
        lb[node] = low;
        ub[node] = high;
        if (low == high) {
            s[node] = origArr[low];
            ls[node] = origArr[low];
            rs[node] = origArr[low];
            ms[node] = origArr[low];
            return;
        }

        // Recurse
        initTree(node * 2, low, (low + high) / 2);
        initTree(node * 2 + 1, (low + high) / 2 + 1, high);

        // Update this node's values
        int left = node * 2;
        int right = node * 2 + 1;
        s[node] = s[left] + s[right];
        ls[node] = Math.max(ls[left], s[left] + ls[right]);
        rs[node] = Math.max(rs[right], s[right] + rs[left]);
        ms[node] = Math.max(Math.max(ms[left], ms[right]), rs[left] + ls[right]);
    }
}

class Result {
    int s, ls, rs, ms;
    Result(int s, int ls, int rs, int ms) {
        this.s = s;
        this.ls = ls;
        this.rs = rs;
        this.ms = ms;
    }
}