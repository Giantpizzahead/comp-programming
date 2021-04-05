#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, Q;
int A[MAXN];

struct SegmentTree {
    ll V[MAXN*4+1], D[MAXN*4+1];

    void set(int n, ll v, int lb, int ub) {
        V[n] = v * (ub-lb+1);
        D[n] = -v;
    }

    void add(int n, ll v, int lb, int ub) {
        V[n] += v * (ub-lb+1);
        if (D[n] >= 0) D[n] += v;
        else D[n] -= v;
    }

    void prop(int n, int lb, int ub) {
        if (D[n] < 0) {
            set(n*2, -D[n], lb, (lb+ub)/2);
            set(n*2+1, -D[n], (lb+ub)/2+1, ub);
        } else if (D[n] > 0) {
            add(n*2, D[n], lb, (lb+ub)/2);
            add(n*2+1, D[n], (lb+ub)/2+1, ub);
        }
        D[n] = 0;
    }

    void merge(int n) {
        V[n] = V[n*2] + V[n*2+1];
    }

    void init(int n=1, int lb=0, int ub=N-1) {
        if (lb == ub) {
            set(n, A[lb], lb, ub);
            return;
        }
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    void updSet(int l, int r, ll v, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            set(n, v, lb, ub);
            return;
        }
        prop(n, lb, ub);
        updSet(l, r, v, n*2, lb, (lb+ub)/2);
        updSet(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    void updAdd(int l, int r, ll v, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            add(n, v, lb, ub);
            return;
        }
        prop(n, lb, ub);
        updAdd(l, r, v, n*2, lb, (lb+ub)/2);
        updAdd(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    ll query(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return V[n];
        prop(n, lb, ub);
        return query(l, r, n*2, lb, (lb+ub)/2) + query(l, r, n*2+1, (lb+ub)/2+1, ub);
    }
} segt;

void solve() {
    cin >> N >> Q;
    rep(i, 0, N) cin >> A[i];
    segt.init();
    int t, a, b, x;
    rep(i, 0, Q) {
        cin >> t >> a >> b;
        a--, b--;
        if (t == 1) {
            // Increase
            cin >> x;
            segt.updAdd(a, b, x);
        } else if (t == 2) {
            // Set
            cin >> x;
            segt.updSet(a, b, x);
        } else {
            // Query
            cout << segt.query(a, b) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}