template <class T, int N=100005>
class SegmentTree {
public:
    T arr[N*4+1];
    // Change if needed
    const T NULL_VALUE = 0;

    T merge(T a, T b) {
        // Fill this in
    }

    void setValue(int n, T v) {
        // Fill this in
    }

    SegmentTree() {
        for (int i = 0; i < N*4+1; i++) arr[i] = NULL_VALUE;
    }

    void update(int n, int lb, int ub, int i, T v) {
        if (lb > i || ub < i) return;
        else if (lb == ub) {
            setValue(n, v);
            return;
        }
        update(n*2, lb, (lb+ub)/2, i, v);
        update(n*2+1, (lb+ub)/2+1, ub, i, v);
        arr[n] = merge(arr[n*2], arr[n*2+1]);
    }

    void update(int i, T v) {
        update(1, 0, N-1, i, v);
    }

    T query(int n, int lb, int ub, int l, int r) {
        if (lb > r || ub < l) return NULL_VALUE;
        else if (lb >= l && ub <= r) return arr[n];
        return merge(query(n*2, lb, (lb+ub)/2, l, r), query(n*2+1, (lb+ub)/2+1, ub, l, r));
    }

    T query(int l, int r) {
        return query(1, 0, N-1, l, r);
    }
};