#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 40;

int N, M, S, T, flowN;
struct Edge {
    int n, r, c;
};
vector<Edge> adj[MAXN];

int level[MAXN], ptr[MAXN];

void addEdge(int a, int b, int c) {
    adj[a].push_back({b, sz(adj[b]), c});
    adj[b].push_back({a, sz(adj[a])-1, 0});
}

bool bfs() {
    rep(i, 0, flowN) level[i] = -1;
    level[S] = 0;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int n = q.front(); q.pop();
        for (Edge& e : adj[n]) {
            if (level[e.n] != -1 || !e.c) continue;
            level[e.n] = level[n] + 1;
            q.push(e.n);
        }
    }
    return (level[T] != -1);
}

int dfs(int n, int f) {
    if (n == T) return f;
    for (; ptr[n] < sz(adj[n]); ptr[n]++) {
        Edge& e = adj[n][ptr[n]];
        if (level[n] + 1 != level[e.n] || e.c == 0) continue;
        if (int ret = dfs(e.n, min(f, e.c))) {
            e.c -= ret;
            adj[e.n][e.r].c += ret;
            return ret;
        }
    }
    return 0;
}

int findFlow() {
    int flow = 0;
    while (bfs()) {
        rep(i, 0, flowN) ptr[i] = 0;
        while (int ret = dfs(0, INT32_MAX)) {
            flow += ret;
        }
    }
    return flow;
}

void solve(int tn) {
    cin >> N >> M;
    S = 0, T = N+M+1, flowN = N+M+2;
    rep(i, 0, flowN) adj[i].clear();
    int K; cin >> K;
    // Initial stickers Bob has
    rep(i, 0, K) {
        int x; cin >> x;
        addEdge(S, x, 1);
    }
    // Final number of distinct stickers
    rep(x, 1, M+1) {
        addEdge(x, T, 1);
    }
    rep(i, 1, N) {
        // Every person has a "trading post"
        int tradePost = M+i;
        cin >> K;
        int cnt[M+1];
        rep(j, 1, M+1) cnt[j] = 0;
        rep(j, 0, K) {
            int x; cin >> x;
            if (cnt[x]++ >= 1) {
                // Person trades duplicate stickers
                addEdge(tradePost, x, 1);
            }
        }
        rep(x, 1, M+1) {
            // Person accepts stickers they don't have
            if (cnt[x] == 0) addEdge(x, tradePost, 1);
        }
    }
    cout << "Case #" << tn << ": " << findFlow() << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    rep(i, 1, t+1) solve(i);
    return 0;
}