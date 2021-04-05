#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
vi adj[MAXN];

int maxD, maxN;

void dfs(int n, int p, int d=0) {
    if (d > maxD) {
        maxD = d;
        maxN = n;
    }
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs(e, n, d+1);
    }
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
    maxD = -1;
    dfs(0, 0, 0);
    maxD = -1;
    dfs(maxN, maxN, 0);
    cout << maxD << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}