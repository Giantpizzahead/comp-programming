#include <iostream>
#include <vector>
#include <queue>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5, INF = 1e9+7;

int N, M;
ll mstCost = 0;
bool inMST[MAXN];
struct Edge {
    int n, c, id;
};
Edge edges[MAXN];
vector<Edge> adj[MAXN], treeAdj[MAXN];

bool vis[MAXN];
int dist[MAXN], from[MAXN];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
void genMST() {
    rep(i, 0, N) dist[i] = INF;
    dist[0] = 0;
    from[0] = -1;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        int n = p.second, c = p.first;
        if (vis[n]) continue;
        vis[n] = true;
        mstCost += c;
        if (from[n] != -1) inMST[from[n]] = true;
        for (auto& e : adj[n]) {
            if (e.c < dist[e.n]) {
                dist[e.n] = e.c;
                from[e.n] = e.id;
                pq.emplace(e.c, e.n);
            }
        }
    }
}

const int MAXK = 20;
int depth[MAXN], lca[MAXK][MAXN], maxEdge[MAXK][MAXN];

void genInfo(int n, int p, int f) {
    depth[n] = depth[p] + 1;
    lca[0][n] = p;
    maxEdge[0][n] = f;
    for (auto& e : treeAdj[n]) {
        if (e.n == p) continue;
        genInfo(e.n, n, e.c);
    }
}

int findLCAMax(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int delta = depth[a] - depth[b];
    int ans = -INF;
    for (int i = MAXK-1; i >= 0; i--) {
        if (delta >= (1 << i)) {
            delta -= (1 << i);
            ans = max(maxEdge[i][a], ans);
            a = lca[i][a];
        }
    }
    if (a == b) return ans;
    for (int i = MAXK-1; i >= 0; i--) {
        if (lca[i][a] != lca[i][b]) {
            ans = max(maxEdge[i][a], ans);
            ans = max(maxEdge[i][b], ans);
            a = lca[i][a];
            b = lca[i][b];
        }
    }
    ans = max(maxEdge[0][a], ans);
    ans = max(maxEdge[0][b], ans);
    return ans;
}

void solve() {
    cin >> N >> M;
    int u, v, w;
    rep(i, 0, M) {
        cin >> u >> v >> w;
        u--, v--;
        edges[i] = {u, v, w};
        adj[u].push_back({v, w, i});
        adj[v].push_back({u, w, i});
    }
    genMST();
    rep(i, 0, M) {
        if (inMST[i]) {
            int a = edges[i].n, b = edges[i].c, w = edges[i].id;
            treeAdj[a].push_back({b, w, -1});
            treeAdj[b].push_back({a, w, -1});
        }
    }
    genInfo(0, 0, -INF);
    rep(k, 1, MAXK) {
        rep(i, 0, N) {
            lca[k][i] = lca[k-1][lca[k-1][i]];
            maxEdge[k][i] = max(maxEdge[k-1][i], maxEdge[k-1][lca[k-1][i]]);
        }
    }
    rep(i, 0, M) {
        if (inMST[i]) {
            cout << mstCost << '\n';
            continue;
        }
        cout << mstCost + edges[i].id - findLCAMax(edges[i].n, edges[i].c) << '\n';
    }
    // rep(i, 0, M) cout << inMST[i];
    // cout << endl;
    // cout << mstCost << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}