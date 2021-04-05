#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 5005;
const ll INF = 1e18;

int N, M;
struct Edge {
    int a, b, c;
};
Edge edges[MAXN], revEdges[MAXN];

ll dist[MAXN];
bool diff1[MAXN], diff2[MAXN];

void bellmanIter(Edge E[MAXN]) {
    rep(i, 0, M) {
        Edge& e = E[i];
        if (dist[e.a] == -INF || dist[e.a] + e.c <= dist[e.b]) continue;
        dist[e.b] = dist[e.a] + e.c;
        diff1[e.b] = true;
    }
}

void bellmanFord(int s, Edge E[MAXN]) {
    rep(i, 0, N) dist[i] = -INF;
    dist[s] = 0;
    rep(i, 1, N) bellmanIter(E);
    rep(i, 0, N) diff1[i] = false;
    rep(i, 0, N) bellmanIter(E);
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        cin >> edges[i].a >> edges[i].b >> edges[i].c;
        edges[i].a--, edges[i].b--;
        revEdges[i].a = edges[i].b;
        revEdges[i].b = edges[i].a;
        revEdges[i].c = edges[i].c;
    }
    bellmanFord(N-1, revEdges);
    swap(diff1, diff2);
    bellmanFord(0, edges);
    rep(i, 0, N) {
        if (diff1[i] && diff2[i]) {
            cout << -1 << '\n';
            return;
        }
    }
    cout << dist[N-1] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}