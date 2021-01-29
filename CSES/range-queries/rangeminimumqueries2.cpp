#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, Q;

template<typename T>
struct SegmentTree {
    int N;
    vector<T> V;

    void setup(vector<T> A) {
        N = A.size();
        V.resize(N*4+1);
        init(A);
    }

    void init(vector<T>& A) {
        init(A, 1, 0, N-1);
    }

    void update(int i, T v) {
        update(i, v, 1, 0, N-1);
    }

    T query(int l, int r) {
        return query(l, r, 1, 0, N-1);
    }

    void init(vector<T>& A, int n, int lb, int ub) {
        if (lb == ub) {
            V[n] = A[lb];
            return;
        }
        init(A, n*2, lb, (lb+ub)/2);
        init(A, n*2+1, (lb+ub)/2+1, ub);
        V[n] = min(V[n*2], V[n*2+1]);
    }

    void update(int i, T v, int n, int lb, int ub) {
        if (lb == ub) {
            V[n] = v;
            return;
        } else if (i > (lb+ub)/2) update(i, v, n*2+1, (lb+ub)/2+1, ub);
        else update(i, v, n*2, lb, (lb+ub)/2);
        V[n] = min(V[n*2], V[n*2+1]);
    }

    T query(int l, int r, int n, int lb, int ub) {
        if (l > ub || r < lb) return 1e9+7;
        else if (lb >= l && ub <= r) return V[n];
        return min(query(l, r, n*2, lb, (lb+ub)/2), query(l, r, n*2+1, (lb+ub)/2+1, ub));
    }
};

void solve() {
    cin >> N >> Q;
    vector<int> A;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        A.push_back(x);
    }
    SegmentTree<int> segt;
    segt.setup(A);

    int t, a, b;
    for (int i = 0; i < Q; i++) {
        cin >> t >> a >> b;
        if (t == 1) {
            segt.update(a-1, b);
        } else {
            cout << segt.query(a-1, b-1) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}