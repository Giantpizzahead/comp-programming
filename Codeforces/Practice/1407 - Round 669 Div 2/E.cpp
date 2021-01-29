#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
using namespace std;

const int MAXN = 5e5+5;

int N, M;
struct Edge {
    int n, t;
};
vector<Edge> adj[MAXN], revAdj[MAXN];

int color[MAXN], dist[MAXN];
queue<int> q;

void handleNode(int n) {
    for (Edge& e : revAdj[n]) {
        if (dist[e.n] != -1) continue;
        if (color[e.n] == -1 || color[e.n] == e.t) {
            color[e.n] = e.t;
            continue;
        }
        // Can reach here
        dist[e.n] = dist[n] + 1;
        q.push(e.n);
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        color[i] = -1;
        dist[i] = -1;
    }
    rep(i, 0, M) {
        int u, v, t;
        cin >> u >> v >> t;
        u--, v--;
        adj[u].push_back({v, 1-t});
        revAdj[v].push_back({u, 1-t});
    }
    dist[N-1] = 0;
    q.push(N-1);
    while (!q.empty()) {
        handleNode(q.front());
        q.pop();
    }

    cout << dist[0] << '\n';
    rep(i, 0, N) {
        if (color[i] == -1) color[i] = 1;
        cout << color[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}