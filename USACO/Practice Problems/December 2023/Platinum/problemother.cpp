#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 2e5+5;
const ll MOD = 1e9+7;

struct DisjointSet {
    int V[MAXN];

    void init(int N) {
        rep(i, 0, N) V[i] = -1;
    }

    int find(int n) {
        if (V[n] < 0) return n;
        else return V[n] = find(V[n]);
    }

    bool merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (V[a] > V[b]) swap(a, b);
        V[a] += V[b];
        V[b] = a;
        return true;
    }
} ds;

int N, M;
struct Edge {
    int n, e;
};
vector<int> adj[MAXN];
vector<Edge> edges;
bool vis[MAXN];
priority_queue<int, vector<int>, greater<int>> active;

ll simulate(int n) {
    rep(i, 0, N) vis[i] = false;
    ll ans = 0;
    for (int i = 0; i < N-1; i++) {
        vis[n] = true;
        for (int id : adj[n]) active.push(id);
        int x = -1, e = n;
        while (vis[e]) {
            x = active.top(); active.pop();
            if (edges[x].n == n) e = edges[x].e;
            else e = edges[x].n;
        }
        ans = (ans * 10 + x+1) % MOD;
        n = e;
    }
    while (!active.empty()) active.pop();
    return ans;
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int a, b; cin >> a >> b;
        a--, b--;
        edges.push_back({a, b});
    }

    // Only keep MST edges
    ds.init(N);
    rep(i, 0, M) {
        if (ds.merge(edges[i].n, edges[i].e)) {
            // Edge is useful
            adj[edges[i].n].push_back(i);
            adj[edges[i].e].push_back(i);
        }
    }

    // Simulate for all nodes
    rep(n, 0, N) {
        cout << simulate(n) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("test.in", "r", stdin);
    solve();
    return 0;
}
