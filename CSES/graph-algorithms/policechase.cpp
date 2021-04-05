#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 500, MAXM = 1000;

int N, M;
int C[MAXM*2];
struct Edge {
    int n, id;
};
vector<Edge> adj[MAXN];

int iter = 1, flow = 0;
int vis[MAXN];
int fordFulkerson(int n, int v=100) {
    vis[n] = iter;
    if (n == N-1) {
        flow += v;
        return v;
    }
    for (Edge& e : adj[n]) {
        if (vis[e.n] == iter || !C[e.id]) continue;
        int ret = fordFulkerson(e.n, min(v, C[e.id]));
        if (ret) {
            C[e.id] -= ret;
            C[e.id ^ 1] += ret;
            return ret;
        }
    }
    return 0;
}

void solve() {
    cin >> N >> M;
    int a, b;
    rep(i, 0, M) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back({b, i*2});
        adj[b].push_back({a, i*2+1});
        C[i*2] = 1, C[i*2+1] = 1;
    }
    for (; fordFulkerson(0); iter++);
    cout << flow << '\n';
    rep(i, 0, N) {
        if (vis[i] != iter) continue;
        for (Edge& e : adj[i]) {
            if (vis[e.n] != iter) cout << i+1 << ' ' << e.n+1 << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}