#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 250, MAXM = 5000;
const int INF_I = 1e9;
const ll INF_L = 1e18;

int N, M, S, T;
int A[MAXM*2], B[MAXM*2], C[MAXM*2];
ll W[MAXM*2];

int from[MAXN];
ll dist[MAXN];
bool bellmanFordIter() {
    bool changed = false;
    rep(i, 0, M) {
        if (C[i] == 0) continue;
        ll nd = dist[A[i]] + W[i];
        if (nd < dist[B[i]]) {
            dist[B[i]] = nd;
            from[B[i]] = i;
            changed = true;
        }
    }
    return changed;
}

pair<int, ll> augmentPath() {
    // Bellman-Ford
    rep(i, 0, N) {
        dist[i] = INF_L;
        from[i] = -1;
    }
    dist[S] = 0;
    rep(i, 0, N-1) bellmanFordIter();
    // No negative cycles should exist
    assert(!bellmanFordIter());

    // Augment flow along shortest path
    if (from[T] == -1) return {0, 0};
    vector<int> edges;
    int n = T;
    while (from[n] != -1) {
        edges.push_back(from[n]);
        n = A[from[n]];
    }
    int toPush = INF_I;
    for (int e : edges) toPush = min(C[e], toPush);
    ll chgCost = 0;
    for (int e : edges) {
        C[e] -= toPush;
        C[e^1] += toPush;
        chgCost += W[e] * toPush;
    }
    return {toPush, chgCost};
}

pair<int, ll> minCostMaxFlow() {
    int flow = 0;
    ll cost = 0;
    while (true) {
        pair<int, ll> res = augmentPath();
        if (res.first == 0) break;
        // cout << "pushed " << res.first << " units with cost " << res.second << endl;
        flow += res.first;
        cost += res.second;
    }
    return {flow, cost};
}

void addEdge(int a, int b, int c, int w) {
    A[M] = a, B[M] = b, C[M] = c, W[M] = w;
    M++;
    A[M] = b, B[M] = a, C[M] = 0, W[M] = -w;
    M++;
}

void solve() {
    int tempM;
    M = 0;
    cin >> N >> tempM >> S >> T;
    int a, b, c, w;
    rep(i, 0, tempM) {
        cin >> a >> b >> c >> w;
        addEdge(a, b, c, w);
    }
    pair<int, ll> res = minCostMaxFlow();
    cout << res.first << ' ' << res.second << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}