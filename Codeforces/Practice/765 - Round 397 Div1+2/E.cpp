/*
https://codeforces.com/contest/765/problem/E

Solution: DFS, merging paths greedily when needed. If you reach a point where paths can't be merged, that must be the
root (final merges happen here), so just try another DFS from there. Divide by 2 as long as possible at the end.
Runtime: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, R;
vi adj[MAXN];

int dfs(int n, int p) {
    set<int> paths;
    for (int e : adj[n]) {
        if (e == p) continue;
        int res = dfs(e, n);
        if (res == -1) return -1;
        else paths.insert(res + 1);
    }
    if (paths.empty()) return 0;
    else if (sz(paths) == 1) return *paths.begin();
    else if (n != p) {
        R = n;
        return -1;
    }
    // Root and has multiple paths
    if (sz(paths) == 2) return *paths.begin() + *prev(paths.end());
    else return -1;
}

void solve() {
    cin >> N;
    rep(i, 1, N) {
        int a, b; cin >> a >> b; a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    R = 0;
    dfs(R, R);  // Set the right root
    int ans = dfs(R, R);
    while (ans != -1 && ans % 2 == 0) ans /= 2;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}