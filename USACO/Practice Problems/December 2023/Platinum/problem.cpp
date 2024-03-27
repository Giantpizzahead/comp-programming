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
    int n, e, l;
};
vector<Edge> adj[MAXN];
vector<Edge> edges;
bool vis[MAXN];

ll simulate(int n) {
    rep(i, 0, N) vis[i] = false;
    set<pair<int, int>> active;
    int numVisited = 1;
    ll ans = 0;
    while (numVisited < N) {
        vis[n] = true;
        for (Edge& e : adj[n]) if (!vis[e.e]) active.insert({e.l, e.e});
        while (true) {
            auto ptr = active.begin();
            if (vis[ptr->second]) {
                active.erase(ptr);
                continue;
            } else {
                ans = (ans * 10 + ptr->first) % MOD;
                n = ptr->second;
                active.erase(ptr);
                numVisited++;
                break;
            }
        }
    }
    return ans;
}

void solve() {
    cin >> N >> M;
    rep(i, 1, M+1) {
        int a, b; cin >> a >> b;
        a--, b--;
        edges.push_back({a, b, i});
    }

    ds.init(N);
    sort(all(edges), [](const Edge& a, const Edge& b) { return a.l < b.l; });
    for (Edge& e : edges) {
        if (ds.merge(e.n, e.e)) {
            // Edge is useful
            adj[e.n].push_back({e.n, e.e, e.l});
            adj[e.e].push_back({e.e, e.n, e.l});
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
