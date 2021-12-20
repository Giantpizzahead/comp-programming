template <class T, int N=100005>
class SegmentTree {
public:
    T arr[N*4+1], delta[N*4+1];
    const T MOD = 1e9+7;
    const T NULL_VALUE = 0;

    void propagate(int n, int lb, int ub) {
        arr[n*2] = (arr[n*2] + delta[n] * ((lb+ub)/2 - lb + 1));
        arr[n*2+1] = (arr[n*2+1] + delta[n] * (ub - ((lb+ub)/2+1) + 1));
        delta[n*2] = (delta[n*2] + delta[n]);
        delta[n*2+1] = (delta[n*2+1] + delta[n]);
        delta[n] = NULL_VALUE;
    }

    T merge(T a, T b) {
        return (a + b);
    }

    void lazyTag(int n, int lb, int ub, T v) {
        arr[n] = (arr[n] + v * (ub-lb+1));
        delta[n] = (delta[n] + v);
    }

    SegmentTree() {
        for (int i = 0; i < N*4+1; i++) {
            arr[i] = NULL_VALUE;
            delta[i] = NULL_VALUE;
        }
    }

    void update(int n, int lb, int ub, int l, int r, T v) {
        if (lb > r || ub < l) return;
        else if (lb >= l && ub <= r) {
            lazyTag(n, lb, ub, v);
            return;
        }
        propagate(n, lb, ub);
        update(n*2, lb, (lb+ub)/2, l, r, v);
        update(n*2+1, (lb+ub)/2+1, ub, l, r, v);
        arr[n] = merge(arr[n*2], arr[n*2+1]);
    }

    T query(int n, int lb, int ub, int l, int r) {
        if (lb > r || ub < l) return NULL_VALUE;
        else if (lb >= l && ub <= r) return arr[n];
        propagate(n, lb, ub);
        return merge(query(n*2, lb, (lb+ub)/2, l, r), query(n*2+1, (lb+ub)/2+1, ub, l, r));
    }

    void update(int l, int r, T v) {
        update(1, 0, N-1, l, r, v);
    }

    T query(int l, int r) {
        return query(1, 0, N-1, l, r);
    }
};