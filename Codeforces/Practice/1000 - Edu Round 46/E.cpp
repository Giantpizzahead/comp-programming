#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 3e5+5;

int N, M;
struct Edge {
    int n, id;
};
vector<Edge> adj[MAXN];
set<int> compAdj[MAXN];
bool isBridge[MAXN];

int currT = 1, disc[MAXN], lowLink[MAXN];
void dfsBridges(int n, int fromID) {
    disc[n] = currT;
    lowLink[n] = currT++;
    for (Edge& e : adj[n]) {
        if (e.id == fromID) continue;
        if (disc[e.n] == 0) {
            // Not visited
            dfsBridges(e.n, e.id);
            lowLink[n] = min(lowLink[e.n], lowLink[n]);
            if (lowLink[e.n] > disc[n]) {
                // Bridge!
                isBridge[e.id] = true;
            }
        } else {
            // Visited
            lowLink[n] = min(disc[e.n], lowLink[n]);
        }
    }
}

int compN = 0, compID[MAXN];
void dfsComp(int n, int fromID) {
    compID[n] = compN;
    for (Edge& e : adj[n]) {
        if (e.id == fromID || isBridge[e.id] || compID[e.n] != -1) continue;
        dfsComp(e.n, e.id);
    }
}

int bestN, bestD;
void dfsTree(int n, int p, int d) {
    if (d > bestD) {
        bestN = n;
        bestD = d;
    }
    for (int e : compAdj[n]) {
        if (e == p) continue;
        dfsTree(e, n, d+1);
    }
}

int treeDiameter() {
    bestN = 0, bestD = 0;
    dfsTree(0, 0, 0);
    int startN = bestN;
    bestN = startN, bestD = 0;
    dfsTree(startN, startN, 0);
    return bestD;
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back({y, i});
        adj[y].push_back({x, i});
    }
    dfsBridges(0, -1);

    // cout << "bridges: ";
    // rep(i, 0, M) cout << isBridge[i] << ' ';
    // cout << endl;

    rep(i, 0, N) compID[i] = -1;
    rep(i, 0, N) {
        if (compID[i] == -1) {
            dfsComp(i, -1);
            compN++;
        }
    }
    rep(i, 0, N) {
        for (Edge& e : adj[i]) {
            if (compID[i] == compID[e.n]) continue;
            compAdj[compID[i]].insert(compID[e.n]);
            compAdj[compID[e.n]].insert(compID[i]);
        }
    }

    // cout << "comps: ";
    // rep(i, 0, N) cout << compID[i] << ' ';
    // cout << endl;

    cout << treeDiameter() << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}