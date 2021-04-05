#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

struct Edge {
    int a, b, x;
};

bool bellmanFord(vector<ll>& dists, vector<Edge>& edges, vector<bool>& ignore) {
    bool upd = false;
    for (Edge& e : edges) {
        if (ignore[e.a] || ignore[e.b]) continue;
        ll nc = dists[e.a] + e.x;
        if (nc > dists[e.b]) {
            upd = true;
            dists[e.b] = nc;
        }
    }
    return upd;
}

void solve() {
    int N, M;
    cin >> N >> M;
    vector<Edge> edges(M), revEdges(M);
    rep(i, 0, M) {
        cin >> edges[i].a >> edges[i].b >> edges[i].x;
        revEdges[i].a = edges[i].b;
        revEdges[i].b = edges[i].a;
        revEdges[i].x = 1;
    }
    vector<ll> dists(N+1);
    rep(i, 1, N+1) dists[i] = -1e18;
    dists[N] = 0;
    vector<bool> ignore(N+1);

    rep(i, 0, N-1) {
        bellmanFord(dists, revEdges, ignore);
    }
    rep(i, 1, N+1) {
        if (dists[i] < -1e17) ignore[i] = true;
        dists[i] = -1e18;
    }
    dists[1] = 0;
    rep(i, 0, N-1) {
        bellmanFord(dists, edges, ignore);
    }
    rep(i, 1, N+1) {
        if (dists[i] < -1e17) ignore[i] = true;
    }
    bool bad = bellmanFord(dists, edges, ignore);
    cout << (bad ? -1 : dists[N]) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}