#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, ans;
vi adj[MAXN];

bool dfs(int n, int p) {
    bool childFree = false;
    for (int e : adj[n]) {
        if (e == p) continue;
        childFree |= dfs(e, n);
    }
    if (childFree) ans++;
    return !childFree;
}

void solve() {
    cin >> N;
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, 0);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}