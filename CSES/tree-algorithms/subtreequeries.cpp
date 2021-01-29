#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+1;

int N, Q, currLabel = 1;
int labelS[MAXN], labelE[MAXN], V[MAXN];
vi adj[MAXN];

struct BIT {
    ll V[MAXN];

    void upd(int i, int v) {
        while (i < MAXN) {
            V[i] += v;
            i += i & -i;
        }
    }

    ll query(int i) {
        ll r = 0;
        while (i > 0) {
            r += V[i];
            i -= i & -i;
        }
        return r;
    }

    ll query(int l, int r) {
        return query(r) - query(l-1);
    }
};

BIT bit;

void dfsLabels(int n, int p) {
    labelS[n] = currLabel++;
    for (int e : adj[n]) {
        if (e != p) dfsLabels(e, n);
    }
    labelE[n] = currLabel-1;
}

void solve() {
    cin >> N >> Q;
    rep(i, 0, N) cin >> V[i];
    rep(i, 1, N) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfsLabels(0, 0);
    rep(i, 0, N) bit.upd(labelS[i], V[i]);
    rep(i, 0, Q) {
        int t, s, x;
        cin >> t >> s;
        s--;
        if (t == 1) {
            // Update
            cin >> x;
            bit.upd(labelS[s], x - V[s]);
            V[s] = x;
        } else {
            // Query
            cout << bit.query(labelS[s], labelE[s]) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}