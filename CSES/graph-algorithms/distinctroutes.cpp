#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 505, MAXM = 2005;

int N, M;
struct Edge {
    int n, i;
};
vector<Edge> adj[MAXN];
int C[MAXM];

int currIter, vis[MAXN];
int fordFulkerson(int n, int f) {
    vis[n] = currIter;
    if (n == N-1) return f;
    for (Edge& e : adj[n]) {
        if (vis[e.n] == currIter) continue;
        if (C[e.i] <= 0) continue;
        int res = fordFulkerson(e.n, min(f, C[e.i]));
        if (res != 0) {
            // Push flow
            C[e.i^1] += res;
            C[e.i] -= res;
            return res;
        }
    }
    // No path found
    return 0;
}

void findPath(int n, vi& path) {
    path.push_back(n+1);
    if (n == N-1) return;
    for (Edge& e : adj[n]) {
        if (e.i % 2 == 1 || C[e.i] == 1) continue;
        C[e.i]++;
        findPath(e.n, path);
        return;
    }
}

void solve() {
    cin >> N >> M;
    int a, b;
    rep(i, 0, M) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back({b, i*2});
        adj[b].push_back({a, i*2+1});
        C[i*2] = 1, C[i*2+1] = 0;
    }
    // Find max flow
    while (true) {
        currIter++;
        int res = fordFulkerson(0, INT32_MAX);
        if (res == 0) break;
    }
    // rep(i, 0, M) cout << C[i*2] << endl;
    // Build paths
    vector<vi> paths;
    while (true) {
        vi path;
        findPath(0, path);
        if (path.back() != N) break;
        paths.push_back(path);
    }
    cout << sz(paths) << '\n';
    for (vi& path : paths) {
        cout << sz(path) << '\n';
        rep(i, 0, sz(path)) cout << path[i] << " \n"[i == sz(path)-1];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}