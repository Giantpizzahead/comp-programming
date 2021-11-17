#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const ll MOD = 1e9+7, MAXN = 1e5+5;

int N, K;
int C[MAXN];
vector<int> adj[MAXN];

ll dp[MAXN][3];

void dfs(int n, int p) {
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs(e, n);
    }
    // Paint with each color
    rep(c, 0, 3) {
        if (C[n] != c && C[n] != -1) continue;
        dp[n][c] = 1;
        for (int e : adj[n]) {
            if (e == p) continue;
            ll toMult = 0;
            rep(d, 0, 3) if (d != c) toMult += dp[e][d];
            dp[n][c] = dp[n][c] * toMult % MOD;
        }
    }
}

void solve() {
    cin >> N >> K;
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    rep(i, 0, N) C[i] = -1;
    rep(i, 0, K) {
        cin >> a >> b;
        a--, b--;
        C[a] = b;
    }
    dfs(0, 0);
    // rep(i, 0, N) rep(j, 0, 3) cout << dp[i][j] << " \n"[j==2];
    cout << (dp[0][0] + dp[0][1] + dp[0][2]) % MOD << '\n';
}

int main() {
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}