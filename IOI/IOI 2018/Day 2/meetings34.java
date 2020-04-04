import java.util.*;

public class meetings {
    int N, Q;
    Range[] queries;

    long[] minimum_costs(int[] H, int[] L, int[] R) {
        N = H.length;
        Q = L.length;
        queries = new Range[Q];
        for (int i = 0; i < Q; i++) queries[i] = new Range(L[i], R[i], i);
        Arrays.sort(queries, new Comparator<Range>() {
            @Override
            public int compare(Range o1, Range o2) {
                return o2.l - o1.l;
            }
        });
        return new long[0];
    }
}

class Range {
    int l, r, i;
    Range(int l, int r, int i) {
        this.l = l;
        this.r = r;
        this.i = i;
    }
}

class Point {
    int i;
    long v;
    Point(int i, long v) {
        this.i = i;
        this.v = v;
    }
}

class SegmentTree2D {
    int size;
    SegmentTree[] vals;
}

class SegmentTree {
    final long INF = 98765432356789L;
    final int MAX_SEGTREE_SIZE = 100;
    boolean isSegTree;
    int size;
    long[] vals, delta;
    TreeSet<Point> ranges;

    SegmentTree(int size) {
        this.size = size;
        isSegTree = size > MAX_SEGTREE_SIZE;
        if (isSegTree) {
            vals = new long[size * 4 + 1];
            delta = new long[size * 4 + 1];
        } else ranges = new TreeSet<>(new Comparator<Point>() {
            @Override
            public int compare(Point o1, Point o2) {
                return o1.i - o2.i;
            }
        });
    }

    void update(int l, int r, long v) {
        if (isSegTree) update(1, 0, size - 1, l, r, v);
        else {
            ranges.add(new Point(l, v));
            ranges.add(new Point(r, -v));
        }
    }

    void update(int n, int lb, int ub, int l, int r, long v) {
        if (lb > r || ub < l) return;
        else if (lb >= l && ub <= r) {
            vals[n] += v;
            delta[n] += v;
            return;
        }
        propagate(n);
        update(n*2, lb, (lb+ub)/2, l, r, v);
        update(n*2+1, (lb+ub)/2+1, ub, l, r, v);
        merge(n);
    }

    long query(int l, int r) {
        if (isSegTree) return query(1, 0, size - 1, l, r);
        else {
            long result = 0;
            return result;
        }
    }

    long query(int n, int lb, int ub, int l, int r) {
        if (lb > r || ub < l) return INF;
        else if (lb >= l && ub <= r) return vals[n];
        propagate(n);
        return Math.min(query(n*2, lb, (lb+ub)/2, l, r), query(n*2+1, (lb+ub)/2+1, ub, l, r));
    }

    void propagate(int n) {
        if (delta[n] != 0) {
            vals[n*2] += delta[n];
            vals[n*2+1] += delta[n];
            delta[n*2] += delta[n];
            delta[n*2+1] += delta[n];
            delta[n] = 0;
        }
    }

    void merge(int n) {
        vals[n] = Math.min(vals[n*2], vals[n*2+1]);
    }
}