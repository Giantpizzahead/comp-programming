/*
Solution: wtf
Runtime: idfk go solve it yourself
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2005;

int N;
vector<int> adj[MAXN], revAdj[MAXN];

bool vis[MAXN];
stack<int> dfsOrder;

void dfs1(int n) {
    vis[n] = true;
    for (int e : adj[n]) {
        if (vis[e]) continue;
        dfs1(e);
    }
    dfsOrder.push(n);
}

int C = 0;
int compID[MAXN], compIndex[MAXN];
vector<int> compNodes[MAXN];

void dfs2(int n) {
    compID[n] = C;
    compIndex[n] = sz(compNodes[C]);
    compNodes[C].push_back(n);
    for (int e : revAdj[n]) {
        if (compID[e] == -1) dfs2(e);
    }
}

int compN;
vector<int> compAdj[MAXN];
bool mat[MAXN][MAXN];

vector<vector<int>> genPaths() {
    rep(i, 0, compN) rep(j, 0, compN) mat[i][j] = false;
    rep(n, 0, compN) for (int e : compAdj[n]) mat[n][e] = true;
    vector<vector<int>> paths(compN, vector<int>());
    // Generate initial path
    vector<int> path;
    rep(n, 0, compN) {
        // Move node back as far as possible
        int furthestIn = -1;
        rep(i, 0, sz(path)) if (mat[path[i]][n]) furthestIn = i;
        // Insert after this node
        path.insert(path.begin() + (1 + furthestIn), n);
    }

    // Cycle the initial path
    int pathsFound = 0;
    while (pathsFound != compN) {
        // Update path if it's new
        if (paths[path.front()].empty()) {
            pathsFound++;
            paths[path.front()].insert(paths[path.front()].end(), all(path));
        }

        // Move first node back as far as possible
        int furthestIn = 0;
        rep(i, 1, compN) if (mat[path[i]][path[0]]) furthestIn = i;
        // Insert after this node
        path.insert(path.begin() + furthestIn + 1, path.front());
        path.erase(path.begin());
    }
    /*
    rep(i, 0, compN) {
        debug << "p " << i << ": ";
        for (int n : paths[i]) debug << n << " ";
        debug << endl;
    }
    */
    return paths;
}

vector<int> paths[MAXN];

void solve() {
    cin >> N;
    rep(i, 1, N) {
        rep(j, 0, i) {
            int b; cin >> b;
            if (b) {
                adj[j].push_back(i);
                revAdj[i].push_back(j);
            } else {
                adj[i].push_back(j);
                revAdj[j].push_back(i);
            }
        }
    }

    // Find SCCs
    rep(n, 0, N) if (!vis[n]) dfs1(n);
    rep(n, 0, N) compID[n] = -1;
    while (!dfsOrder.empty()) {
        int n = dfsOrder.top(); dfsOrder.pop();
        if (compID[n] == -1) {
            dfs2(n);
            C++;
        }
    }

    // Process each SCC separately
    rep(i, 0, C) {
        compN = sz(compNodes[i]);
        // debug << "scc " << i << " " << X << endl;
        rep(j, 0, compN) compAdj[j].clear();
        for (int n : compNodes[i]) {
            for (int e : adj[n]) {
                if (compID[e] != compID[n]) continue;
                compAdj[compIndex[n]].push_back(compIndex[e]);
            }
        }
        int numEdges = 0;
        rep(j, 0, compN) numEdges += sz(compAdj[j]);
        vector<vector<int>> currPaths = genPaths();
        rep(j, 0, compN) {
            for (int k : currPaths[j]) {
                paths[compNodes[i][j]].push_back(compNodes[i][k]);
            }
        }
    }

    // Combine results and print them
    rep(n, 0, N) {
        vector<int> ans;
        ans.insert(ans.end(), all(paths[n]));
        // Visit all future comps
        rep(c, compID[n]+1, C) {
            ans.insert(ans.end(), all(paths[compNodes[c][0]]));
        }
        cout << sz(ans);
        for (int x : ans) cout << ' ' << x+1;
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}