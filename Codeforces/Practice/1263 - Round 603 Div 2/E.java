/*
Solution: Segment tree!
*/

import java.util.*;
import java.io.*;

public class editor {
    int N;
    SegmentTree seg;

    editor() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        char[] line = in.readLine().toCharArray();
        in.close();
        int maxSize = 1, currSize = 1;
        for (char c : line) {
            if (c == 'R') currSize++;
            else if (c == 'L') currSize = Math.max(1, currSize-1);
            maxSize = Math.max(currSize, maxSize);
        }
        seg = new SegmentTree(maxSize);

        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int currLoc = 1;
        for (int i = 0; i < line.length; i++) {
            if (line[i] == 'R') currLoc++;
            else if (line[i] == 'L') currLoc = Math.max(1, currLoc-1);
            else if (line[i] == '(') seg.set(currLoc-1, 1);
            else if (line[i] == ')') seg.set(currLoc-1, -1);
            else seg.set(currLoc-1, 0);
            out.print(seg.query());
            if (i != line.length - 1) out.print(' ');
        }
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new editor();
    }
}

class SegmentTree {
    int size;
    int[] s, minls, maxrs, maxls, ms;
    SegmentTree(int size) {
        this.size = size;
        s = new int[size * 4 + 1];
        minls = new int[size * 4 + 1];
        maxrs = new int[size * 4 + 1];
        maxls = new int[size * 4 + 1];
        ms = new int[size * 4 + 1];
    }

    void set(int i, int v) {
        set(1, 0, size-1, i, v);
    }

    void set(int n, int lb, int ub, int i, int v) {
        if (lb > i || ub < i) return;
        else if (lb == i && ub == i) {
            s[n] = v;
            minls[n] = v;
            maxrs[n] = v;
            maxls[n] = v;
            ms[n] = v;
            return;
        }

        set(n*2, lb, (lb+ub)/2, i, v);
        set(n*2+1, (lb+ub)/2+1, ub, i, v);
        update(n);
    }

    int query() {
        if (s[1] != 0 || minls[1] < 0) return -1;
        else return ms[1];
    }

    void update(int n) {
        s[n] = s[n*2] + s[n*2+1];
        minls[n] = Math.min(minls[n*2], s[n*2]+minls[n*2+1]);
        maxls[n] = Math.max(maxls[n*2], s[n*2]+maxls[n*2+1]);
        maxrs[n] = Math.max(maxrs[n*2+1], s[n*2+1]+maxrs[n*2]);
        ms[n] = Math.max(Math.max(ms[n*2], ms[n*2+1]), maxrs[n*2] + maxls[n*2+1]);
    }
}