#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;

int N;
ll ans[MAXN];
vector<int> adj[MAXN];

void dfs(int n, int p, ll d, int r) {
    ans[r] += d * d;
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs(e, n, d+1, r);
    }
}

void solve() {
    cin >> N;
    int u, v;
    rep(i, 1, N) {
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    rep(i, 0, N) dfs(i, i, 0, i);
    rep(i, 0, N) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}