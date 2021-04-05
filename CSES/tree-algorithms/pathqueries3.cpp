#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5;

int N, Q;
int X[MAXN], par[MAXN], stSize[MAXN];
int labelS[MAXN], labelE[MAXN], hldRoot[MAXN], hldLabel[MAXN];
vi adj[MAXN];

struct SegmentTree {
    int V[MAXN*2];

    void build() {
        for (int i = N-1; i > 0; i--) {
            V[i] = max(V[i<<1], V[i<<1|1]);
        }
    }

    void upd(int i, int v) {
        i += N;
        V[i] = v;
        for (; i > 1; i >>= 1) {
            V[i>>1] = max(V[i], V[i^1]);
        }
    }

    int query(int l, int r) {
        int ans = 0;
        l += N, r += N+1;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) ans = max(V[l++], ans);
            if (r&1) ans = max(V[--r], ans);
        }
        return ans;
    }

} segt;

int currLabel;

void dfsSize(int n) {
    stSize[n] = 1;
    labelS[n] = currLabel++;
    for (int& e : adj[n]) {
        if (e == par[n]) continue;
        par[e] = n;
        dfsSize(e);
        stSize[n] += stSize[e];
        // Move largest subtree to first position
        if (adj[n][0] == par[n] || stSize[e] > stSize[adj[n][0]]) {
            swap(e, adj[n][0]);
        }
    }
    labelE[n] = currLabel-1;
}

void dfsHLD(int n) {
    hldLabel[n] = currLabel++;
    if (hldRoot[n] == -1) hldRoot[n] = n;
    for (int e : adj[n]) {
        if (e == par[n]) continue;
        if (e == adj[n][0]) hldRoot[e] = hldRoot[n];
        dfsHLD(e);
    }
}

// Returns whether a is a descendent of (in the subtree of) b, also true if a == b
bool desc(int a, int b) {
    return labelS[b] <= labelS[a] && labelE[a] <= labelE[b];
}

int query(int a, int b) {
    int ans = 0;
    // Move node a
    while (!desc(b, hldRoot[a])) {
        ans = max(segt.query(hldLabel[hldRoot[a]], hldLabel[a]), ans);
        a = par[hldRoot[a]];
    }
    // Move node b
    while (!desc(a, hldRoot[b])) {
        ans = max(segt.query(hldLabel[hldRoot[b]], hldLabel[b]), ans);
        b = par[hldRoot[b]];
    }
    // Now both in the same heavy edge, a above b
    if (labelS[a] > labelS[b]) swap(a, b);
    ans = max(segt.query(hldLabel[a], hldLabel[b]), ans);
    return ans;
}

void solve() {
    cin >> N >> Q;
    rep(i, 0, N) {
        cin >> X[i];
        hldRoot[i] = -1;
    }
    int a, b, c;
    rep(i, 1, N) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    currLabel = 0;
    dfsSize(0);
    currLabel = 0;
    dfsHLD(0);

    rep(i, 0, N) segt.V[hldLabel[i]+N] = X[i];
    segt.build();
    // rep(i, 0, 2*N) cout << segt.V[i] << " \n"[i == 2*N-1];
    bool first = true;
    rep(i, 0, Q) {
        cin >> c >> a >> b;
        if (c == 1) {
            // Change
            a--;
            segt.upd(hldLabel[a], b);
        } else {
            // Query
            a--, b--;
            if (first) first = false;
            else cout << ' ';
            cout << query(a, b);
        }
        // rep(i, 0, 2*N) cout << segt.V[i] << " \n"[i == 2*N-1];
    }
    cout << '\n';
    // rep(i, 0, N) cout << par[i]+1 << " \n"[i == N-1];
    // rep(i, 0, N) cout << adj[i][0]+1 << " \n"[i == N-1];
    // rep(i, 0, N) cout << stSize[i] << " \n"[i == N-1];
    // rep(i, 0, N) cout << hldRoot[i]+1 << " \n"[i == N-1];
    // rep(i, 0, N) cout << hldLabel[i]+1 << " \n"[i == N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}