#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, Q, currLabel;
int V[MAXN], labelS[MAXN], labelE[MAXN];
vi adj[MAXN];

struct BIT {
    ll V[MAXN];

    void upd(int i, int v) {
        i++;
        while (i < MAXN) {
            V[i] += v;
            i += i & -i;
        }
    }

    ll query(int i) {
        i++;
        ll R = 0;
        while (i > 0) {
            R += V[i];
            i -= i & -i;
        }
        return R;
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
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfsLabels(0, 0);
    rep(i, 0, N) {
        bit.upd(labelS[i], V[i]);
        bit.upd(labelE[i]+1, -V[i]);
    }
    int t, s, x;
    rep(i, 0, Q) {
        cin >> t >> s;
        s--;
        if (t == 1) {
            // Update
            cin >> x;
            bit.upd(labelS[s], x - V[s]);
            bit.upd(labelE[s]+1, V[s] - x);
            V[s] = x;
        } else {
            // Query
            cout << bit.query(labelS[s]) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}