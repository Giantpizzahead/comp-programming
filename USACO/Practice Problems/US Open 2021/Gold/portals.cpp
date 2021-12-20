#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;

int N;
int C[MAXN];
int P[MAXN][4];
vector<int> cycleAdj[MAXN], cycleLocs[MAXN];

int numComps;
int compID[MAXN];

struct Edge {
    int n, c;
    bool operator<(const Edge& o) const {
        return c > o.c;
    }
};
vector<Edge> adj[MAXN];

void dfsComp(int n) {
    compID[n] = numComps;
    for (int e : cycleAdj[n]) {
        if (compID[e] != -1) continue;
        dfsComp(e);
    }
}

const int INF = 10000;
int vis[MAXN];
priority_queue<Edge> pq;

int findMST() {
    int ans = 0;
    fill(vis, vis+numComps, INF);
    vis[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        Edge p = pq.top(); pq.pop();
        int n = p.n, c = p.c;
        if (vis[n] == -1) continue;
        vis[n] = -1;
        ans += c;
        for (Edge& e : adj[n]) {
            if (vis[e.n] > e.c) {
                vis[e.n] = e.c;
                pq.push({e.n, e.c});
            }
        }
    }
    return ans;
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> C[i];
        rep(j, 0, 4) {
            cin >> P[i][j];
            P[i][j]--;
        }
        cycleAdj[P[i][0]].push_back(P[i][1]);
        cycleAdj[P[i][1]].push_back(P[i][0]);
        cycleAdj[P[i][2]].push_back(P[i][3]);
        cycleAdj[P[i][3]].push_back(P[i][2]);
    }

    // DFS components
    numComps = 0;
    fill(compID, compID+2*N, -1);
    rep(i, 0, 2*N) {
        if (compID[i] == -1) {
            dfsComp(i);
            numComps++;
        }
    }

    // Generate graph and find MST
    rep(i, 0, N) {
        int a = compID[P[i][0]];
        int b = compID[P[i][2]];
        if (a == b) continue;
        adj[a].push_back({b, C[i]});
        adj[b].push_back({a, C[i]});
    }
    int ans = findMST();
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}