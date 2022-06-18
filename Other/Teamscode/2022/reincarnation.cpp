#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define aint(x) x.begin(), x.end()
using ll = long long;
using namespace std;

const int MAXN = 1e6+5;
const int MAXQ = 1e5+5;
const int MAXD = 10;
const int MOD = 1e9+7;

int N, Q;
struct Query {
    int t, d, l, r, x;
};
Query queries[MAXQ];
int queryLoc[MAXQ];
int ans[MAXN][MAXD];
vector<int> adj[MAXQ];

struct SegmentTree {
    int q = 0;
    struct Change {
        int t, i;
    };
    vector<Change> changes[MAXQ];
    vector<int> V[MAXN*4+1], D[MAXN*4+1];

    void changeV(int i, int v) {
        V[i].push_back(v);
        changes[q].push_back({0, i});
    }

    void changeD(int i, int v) {
        D[i].push_back(v);
        changes[q].push_back({1, i});
    }

    int getV(int i) {
        assert(!V[i].empty());
        return V[i].back();
    }

    int getD(int i) {
        assert(!D[i].empty());
        return D[i].back();
    }

    void init(int n=1, int lb=0, int ub=N-1) {
        changeV(n, 0);
        changeD(n, -1);
        if (lb == ub) return;
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2+1, ub);
    }

    void lazySet(int n, int lb, int ub, int v) {
        changeV(n, (ll) v * (ub-lb+1) % MOD);
        changeD(n, v);
    }

    void prop(int n, int lb, int ub) {
        int d = getD(n);
        if (d != -1) {
            lazySet(n*2, lb, (lb+ub)/2, d);
            lazySet(n*2+1, (lb+ub)/2+1, ub, d);
            changeD(n, 0);
        }
    }

    void rangeSet(int l, int r, int v, int n=1, int lb=0, int ub=N-1) {
        if (lb > r || ub < l) return;
        else if (lb >= l && ub <= r) {
            lazySet(n, lb, ub, v);
            return;
        }
        prop(n, lb, ub);
        rangeSet(l, r, v, n*2, lb, (lb+ub)/2);
        rangeSet(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        rep(i, 0, MAXD) changeV(n, (getV(n*2) + getV(n*2+1)) % MOD);
    }

    void process(Query& query) {
        // cout << "process " << query.l << " " << query.r << " " << query.x << endl;
        rangeSet(query.l, query.r, query.x);
        q++;
    }

    void rollback() {
        // cout << "rollback" << endl;
        for (Change c : changes[q-1]) {
            if (c.t == 0) V[c.i].pop_back();
            else if (c.t == 1) D[c.i].pop_back();
        }
        changes[q-1].clear();
        q--;
    }

    int query() {
        // cout << "query = " << getV(1) << endl;
        return getV(1);
    }
} ds;

/*
struct Simple {
    void process(Query& query) {
        // cout << "process " << query.l << " " << query.r << " " << query.x << endl;
        rangeSet(query.l, query.r, query.x);
        q++;
    }

    void rollback() {
        // cout << "rollback" << endl;
        for (Change c : changes[q-1]) {
            if (c.t == 0) V[c.i][c.j].pop_back();
            else if (c.t == 1) D[c.i].pop_back();
        }
        changes[q-1].clear();
        q--;
    }

    int query(int d) {
        // cout << "query " << d << " = " << getV(1, d) << endl;
        return getV(1, d);
    }
} ds;
*/

void dfs(int n, int d) {
    ans[n][d] = ds.query();
    for (int e : adj[n]) {
        int v = queries[e].x;
        rep(i, 0, d) queries[e].x = (ll) queries[e].x * v % MOD;
        ds.process(queries[e]);
        queries[e].x = v;
        dfs(e, d);
        ds.rollback();
    }
}

void solve() {
    cin >> N >> Q;
    int lastLoc = 0;
    rep(i, 1, Q+1) {
        int t, d, l, r, x;
        cin >> t;
        if (t == 1) {
            cin >> d >> l >> r >> x;
            l--, r--;
            queries[i] = {t, d, l, r, x};
            adj[lastLoc].push_back(i);
            queryLoc[i] = i;
        } else {
            cin >> d >> x;
            queryLoc[i] = queryLoc[x];
            queries[i] = {t, d, -1, -1, x};
        }
        lastLoc = queryLoc[i];
    }
    Q++;

    rep(i, 0, MAXD) {
        ds.init();
        dfs(0, i);
    }
    rep(i, 1, Q) cout << ans[queryLoc[i]][queries[i].d-1] << '\n';

    // cout << "locs:\n";
    // rep(i, 0, Q) cout << queryLoc[i] << '\n';
    // rep(i, 0, Q) {
    //     cout << i << ": ";
    //     for (int x : adj[i]) cout << x << " ";
    //     cout << '\n';
    // }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}