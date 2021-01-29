#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2005, MAXE = 5050;

int N, M, K, V, E;
int C[MAXE];
struct Edge {
    int n, i;
};
Edge edges[MAXE];
vector<Edge> adj[MAXN];

bool visited[MAXN];
bool fordFulkerson(int n) {
    visited[n] = true;
    if (n == V-1) {
        // Sink found
        return true;
    }
    for (Edge& e : adj[n]) {
        if (C[e.i] != 1 || visited[e.n]) continue;
        if (fordFulkerson(e.n)) {
            C[e.i] = 0;
            if (e.i % 2 == 0) C[e.i+1] = 1;
            else C[e.i-1] = 1;
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> N >> M >> K;
    V = N+M;
    rep(i, 0, K) {
        int a, b;
        cin >> a >> b; a--, b--;
        C[E] = 1;
        edges[E] = {a, b};
        adj[a].push_back({N+b, E++});
        adj[N+b].push_back({a, E++});
    }
    rep(i, 0, N) {
        C[E] = 1;
        adj[V].push_back({i, E++});
        adj[i].push_back({V, E++});
    }
    V++;
    rep(i, 0, M) {
        C[E] = 1;
        adj[N+i].push_back({V, E++});
        adj[V].push_back({N+i, E++});
    }
    V++;
    // Ford-Fulkerson
    while (true) {
        for (int i = 0; i < V; i++) visited[i] = false;
        if (!fordFulkerson(V-2)) break;
    }
    vector<pair<int, int>> pairs;
    for (int i = 0; i < K; i++) {
        if (C[i*2] == 0) {
            pairs.emplace_back(edges[i*2].n+1, edges[i*2].i+1);
        }
    }
    cout << pairs.size() << "\n";
    for (auto p : pairs) cout << p.first << " " << p.second << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}