/*
Solution: Each node x contributes to a path above it in the tree; every node y in this path has distance <= L from x. Find the highest node in the path using binary lifting, then DFS to sum the # of reachable barns for each node.
Runtime: O(N * log(N))
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2e5+5;
const int MAXK = 16;
const ll INF = 2 * 1e18;

int N;
ll L;

struct Edge {
    int n;
    ll c;
};
vector<int> adj[MAXN];
int fromN[MAXN][MAXK];
ll fromC[MAXN][MAXK];

int delta[MAXN];

void dfs(int n, int p) {
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs(e, n);
        delta[n] += delta[e];
    }
}

void solve() {
    cin >> N >> L;
    fromN[0][0] = 0;
    fromC[0][0] = INF;
    rep(i, 1, N) {
        int p;
        ll l;
        cin >> p >> l;
        p--;
        fromN[i][0] = p;
        fromC[i][0] = l;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    // Gen binary lifting
    rep(i, 1, MAXK) {
        rep(j, 0, N) {
            fromN[j][i] = fromN[fromN[j][i-1]][i-1];
            fromC[j][i] = min(fromC[j][i-1] + fromC[fromN[j][i-1]][i-1], INF);
        }
    }
    // Add deltas
    rep(n, 0, N) {
        delta[n]++;
        // Move up while total length does not exceed L
        int p = n;
        ll currC = 0;
        for (int k = MAXK-1; k >= 0; k--) {
            if (currC + fromC[p][k] <= L) {
                currC += fromC[p][k];
                p = fromN[p][k];
            }
        }
        // Next up does not work
        if (p != 0) {
            p = fromN[p][0];
            delta[p]--;
        }
    }
    // Sum deltas
    dfs(0, 0);
    rep(i, 0, N) cout << delta[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);
    solve();
    return 0;
}