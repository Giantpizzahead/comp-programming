#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 800005;
const int C = 21;
const ll MOD = 1e9+7;

int N;
struct Edge {
    int n, c;
};
vector<Edge> adj[MAXN];

ll currSum;

void dfs(int n, int p, int c) {
    if (n != p) currSum += c;
    for (Edge& e : adj[n]) {
        if (e.n == p) continue;
        dfs(e.n, n, min(e.c, c));
    }
}

void simulate() {
    currSum = 0;
    rep(i, 0, N) dfs(i, i, C);
    assert(currSum % 2 == 0);
    currSum /= 2;
}

void solve() {
    cin >> N;
    rep(i, 0, N) adj[i].clear();
    int a, b, c;
    rep(i, 1, N) {
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    ll answer = 1;
    rep(n, 0, N) {
        for (Edge& e : adj[n]) {
            if (e.n < n) continue;
            // Change this edge
            int saved = e.c;
            e.c = 0;
            for (Edge& f : adj[e.n]) if (f.n == n) f.c = 0;
            simulate();
            currSum %= MOD;
            answer = answer * currSum % MOD;
            e.c = saved;
            for (Edge& f : adj[e.n]) if (f.n == n) f.c = saved;
        }
    }

    cout << answer << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}