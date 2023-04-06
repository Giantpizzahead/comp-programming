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

int N, M, cnt;
vector<vector<int>> adj;
vector<bool> used;

void dfs(int n) {
    cnt++;
    used[n] = true;
    for (int e : adj[n]) {
        if (!used[e] && cnt < 1000000) dfs(e);
    }
    used[n] = false;
}

void solve() {
    cin >> N >> M;
    adj.resize(N);
    used.resize(N);
    rep(i, 0, M) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cnt = 0;
    dfs(0);
    cout << min(cnt, 1000000) << "\n";
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
