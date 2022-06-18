// https://open.kattis.com/problems/shortestpath1

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 1e4+5;
const int INF = 1e9+7;

int N, M, Q, S;
struct Pair {
    int n, c;

    bool operator<(const Pair& o) const {
        return c > o.c;
    }
};
vector<Pair> adj[MAXN];

int best[MAXN];
priority_queue<Pair> pq;

void dijkstra() {
    rep(i, 0, N) best[i] = INF;
    best[S] = 0;
    pq.push({S, 0});
    while (!pq.empty()) {
        int n = pq.top().n, c = pq.top().c; pq.pop();
        for (Pair& e : adj[n]) {
            if (c + e.c < best[e.n]) {
                best[e.n] = c + e.c;
                pq.push({e.n, best[e.n]});
            }
        }
    }
}

void solve() {
    cin >> N >> M >> Q >> S;
    if (N == 0) exit(0);
    int u, v, w;
    rep(i, 0, M) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    dijkstra();
    rep(i, 0, Q) {
        cin >> u;
        if (best[u] == INF) cout << "Impossible\n";
        else cout << best[u] << '\n';
    }
    rep(i, 0, N) adj[i].clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (true) solve();
    return 0;
}