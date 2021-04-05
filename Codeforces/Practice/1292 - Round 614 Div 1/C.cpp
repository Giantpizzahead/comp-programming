#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;

const int MAXN = 3000;

int N, R, rootSize;
int stSize[MAXN];
ll dp[MAXN][MAXN];
int toAdd[MAXN][MAXN];
int t1a[MAXN][MAXN], t1b[MAXN][MAXN], t2a[MAXN][MAXN], t2b[MAXN][MAXN];
vector<pair<int, int>> dpOrder[MAXN];
vector<int> adj[MAXN];

void dfsSize(int n, int p) {
    stSize[n] = 1;
    for (int e : adj[n]) {
        if (e == p) continue;
        dfsSize(e, n);
        stSize[n] += stSize[e];
    }
}

vector<int> nodes;
void dfsPaths(int n, int p, int d = 0) {
    nodes.push_back(n);
    if (n == p) {
        // Base
        for (int e : adj[n]) {
            if (e == p) continue;
            rootSize = N - stSize[e];
            dfsPaths(e, n, d+1);
        }
    } else {
        // Add path
        dpOrder[d].emplace_back(R, n);
        toAdd[R][n] = rootSize * stSize[n];
        t1a[R][n] = nodes[1];
        t1b[R][n] = n;
        t2a[R][n] = R;
        t2b[R][n] = nodes[sz(nodes)-2];
        for (int e : adj[n]) {
            if (e == p) continue;
            dfsPaths(e, n, d+1);
        }
    }
    nodes.pop_back();
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
    // Record all paths rooted at n
    rep(n, 0, N) {
        R = n;
        dfsSize(n, n);
        dfsPaths(n, n);
    }
    // Do DP from shortest to longest path
    ll answer = 0;
    rep(d, 1, N) {
        for (auto& p : dpOrder[d]) {
            int a = p.first, b = p.second;
            dp[a][b] = max(dp[t1a[a][b]][t1b[a][b]], dp[t2a[a][b]][t2b[a][b]]) + toAdd[a][b];
            answer = max(dp[a][b], answer);
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}