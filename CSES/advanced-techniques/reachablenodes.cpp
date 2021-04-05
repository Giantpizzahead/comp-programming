/**
 * Topological sort + Bitset to track which nodes can be reached. (Bitwise OR operation in reverse topo order)
 * Pragmas may be helpful to keep the runtime low.
 * Runtime: O((N+M) * N/64)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 50000;

int N, M;
int ans[MAXN];
bitset<MAXN> R[MAXN];
vi adj[MAXN];
vi revTopo;

bool vis[MAXN];
void dfs(int n) {
    vis[n] = true;
    for (int e : adj[n]) if (!vis[e]) dfs(e);
    revTopo.push_back(n);
}

void solve() {
    cin >> N >> M;
    int a, b;
    rep(i, 0, M) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
    }
    // Topo sort
    rep(i, 0, N) if (!vis[i]) dfs(i);
    // Find reachable nodes
    for (int n : revTopo) {
        R[n].set(n, true);
        for (int e : adj[n]) {
            R[n] |= R[e];
        }
        ans[n] = R[n].count();
    }
    rep(i, 0, N) cout << ans[i] << " \n"[i == N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}