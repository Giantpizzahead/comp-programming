/**
 * Find strongly connected components. Then, use the same bitset approach as in "Reachable Nodes" (the problem before
 * this one).
 * Surprisingly, this problem appears to be an open one in CS (according to https://en.wikipedia.org/wiki/Reachability).
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

const int MAXN = 5e4;

int N, M, Q, compN = 0;
int compID[MAXN];
vi adj[MAXN], revAdj[MAXN], compAdj[MAXN];

bool vis[MAXN];
stack<int> finishTime;

void dfsFirst(int n) {
    vis[n] = true;
    for (int e : adj[n]) if (!vis[e]) dfsFirst(e);
    finishTime.push(n);
}

void dfsSecond(int n) {
    compID[n] = compN;
    for (int e : revAdj[n]) if (compID[e] == -1) dfsSecond(e);
}

bitset<MAXN> compDP[MAXN];

void solve() {
    cin >> N >> M >> Q;
    int a, b;
    rep(i, 0, M) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        revAdj[b].push_back(a);
    }
    rep(i, 0, N) {
        if (!vis[i]) dfsFirst(i);
        compID[i] = -1;
    }
    while (!finishTime.empty()) {
        int n = finishTime.top(); finishTime.pop();
        if (compID[n] == -1) {
            dfsSecond(n);
            compN++;
        }
    }
    rep(n, 0, N) {
        for (int e : adj[n]) {
            if (compID[n] != compID[e]) {
                compAdj[compID[n]].push_back(compID[e]);
            }
        }
    }
    rep(n, 0, compN) {
        sort(all(compAdj[n]));
        compAdj[n].resize(distance(compAdj[n].begin(), unique(all(compAdj[n]))));
        compDP[n].set(n, true);
    }
    for (int n = compN-1; n >= 0; n--) {
        for (int e : compAdj[n]) {
            compDP[n] |= compDP[e];
        }
    }
    rep(i, 0, Q) {
        cin >> a >> b;
        a--, b--;
        a = compID[a], b = compID[b];
        cout << (compDP[a][b] ? "YES" : "NO") << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}