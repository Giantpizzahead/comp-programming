#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;
using namespace std;

const int MAXN = 1e6+5;
const int MAXQ = 1e5+5;
const int MAXD = 11;
const ll MOD = 1e9+7;

int N, Q;
struct Query {
    int t, d, l, r, x;
};
vector<Query> queries;
vector<int> queryFrom;

struct SegmentTree {
    ll V[MAXN*4+1][MAXD], D[MAXN*4+1];
 
    void init(int n=1, int lb=0, int ub=N-1) {
        if (lb == ub) {
            rep(i, 0, MAXD) V[n][i] = 0;
            D[n] = -1;
            return;
        }
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2+1, ub);
        D[n] = -1;
    }

    void lazySet(int n, int lb, int ub, ll v) {
        ll curr = 1;
        rep(i, 0, MAXD) {
            V[n][i] = (ub-lb+1) * curr;
            curr = curr * v % MOD;
        }
    }
 
    void prop(int n, int lb, int ub) {
        if (D[n] == -1) return;
        lazySet(n*2, lb, (lb+ub)/2, D[n]);
        lazySet(n*2+1, (lb+ub)/2+1, ub, D[n]);
        D[n*2] = D[n];
        D[n*2+1] = D[n];
        D[n] = -1;
    }
 
    void rangeSet(int l, int r, ll v, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            lazySet(n, lb, ub, v);
            D[n] = v;
            return;
        }
        prop(n, lb, ub);
        rangeSet(l, r, v, n*2, lb, (lb+ub)/2);
        rangeSet(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        rep(i, 0, MAXD) V[n][i] = (V[n*2][i] + V[n*2+1][i]) % MOD;
    }
 
    ll rangeSum(int l, int r, int d, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return V[n][d];
        prop(n, lb, ub);
        return (rangeSum(l, r, d, n*2, lb, (lb+ub)/2) + rangeSum(l, r, d, n*2+1, (lb+ub)/2+1, ub)) % MOD;
    }
} segt;

void runQuery(Query& q, int z) {
    if (q.t == 1) {
        segt.rangeSet(q.l, q.r, q.x);
    } else {
        vector<int> vals;
        vals.push_back(q.x);
        z = q.x;
        while (z != -1) {
            z = queryFrom[z];
            if (z == -1) break;
            vals.push_back(z);
        }
        reverse(all(vals));
        segt.init();
        for (int i : vals) runQuery(queries[i], i);
    }
}

void solve() {
    cin >> N >> Q;
    rep(i, 0, Q) {
        int t, d, l, r, x;
        cin >> t;
        if (t == 1) {
            cin >> d >> l >> r >> x;
            l--, r--;
            queryFrom.push_back(i-1);
        } else {
            cin >> d >> x;
            queryFrom.push_back(x);
        }
        Query q = {t, d, l, r, x};
        runQuery(q, i);
        queries.push_back(q);
        cout << segt.rangeSum(0, N-1, d) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}