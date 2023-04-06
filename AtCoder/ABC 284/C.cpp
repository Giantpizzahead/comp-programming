// ============================== BEGIN TEMPLATE ==============================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#ifdef LOCAL
    #include "pprint.hpp"
#else
    #define debug(...) 42
    #define dumpVars(...) 42
#endif

void solve();

int runTests(bool multiple_tests) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (multiple_tests) {
        int T; cin >> T;
        rep(i, 0, T) solve();
    } else solve();
    return 0;
}
// =============================== END TEMPLATE ===============================

int N, M;
vector<vector<int>> adj;
vector<bool> vis;

void dfs(int n) {
    vis[n] = true;
    for (int e : adj[n]) if (!vis[e]) dfs(e);
}

void solve() {
    cin >> N >> M;
    adj.resize(N);
    vis.resize(N);
    rep(i, 0, M) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int ans = 0;
    rep(n, 0, N) {
        if (!vis[n]) {
            dfs(n);
            ans++;
        }
    }
    cout << ans << "\n";
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
