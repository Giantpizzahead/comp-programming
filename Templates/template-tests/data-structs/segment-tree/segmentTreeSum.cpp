#include <iostream>
#include <time.h>

using namespace std;
using ll = long long;

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

const ll MOD = 1e9+7;
const int MAXN = 1000005;

ll genRandom(ll maxNum) {
    return abs(rand() * 1829475931 + rand() * 61929 + rand()) % maxNum;
}

void stressTest(int N, int Q, bool debug) {
    SegmentTree<ll, MAXN> segt;
    ll arr[MAXN];
    for (int i = 0; i < MAXN; i++) arr[i] = 0;

    srand(time(NULL));
    cout << "Stress testing with " << N << " elements and " << Q << " queries (debug " << (debug ? "on" : "off") << ")..." << endl;
    int t, l, r;
    ll v;
    for (int i = 0; i < Q; i++) {
        t = genRandom(2);
        l = genRandom(N);
        r = genRandom(N);
        if (l > r) swap(l, r);
        if (t == 0) {
            // Update
            v = genRandom(1e9);
            segt.update(l, r, v);
            if (debug) for (int j = l; j <= r; j++) arr[j] = (arr[j] + v);
        } else {
            // Query
            ll a1 = segt.query(l, r);
            if (debug) {
                ll a2 = 0;
                for (int j = l; j <= r; j++) a2 = (a2 + arr[j]);
                if (a1 != a2) {
                    cerr << "Query #" << i+1 << " answers mismatched! (" << a1 << " != " << a2 << ")" << endl;
                    return;
                }
            }
        }
    }
    cout << "Test complete!" << endl;
}

int main() {
    stressTest(200, 1000000, true);
    stressTest(30000, 30000, true);
    stressTest(1000000, 1000, true);
    stressTest(1000000, 1000000, false);
}