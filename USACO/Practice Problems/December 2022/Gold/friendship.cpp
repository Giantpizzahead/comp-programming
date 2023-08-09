/*
http://usaco.org/index.php?page=viewproblem2&cpid=1259

Solution:
Try every min # of friends. For each, do an efficient algorithm to find the max number of cows in a group. The runtime
is O(Nsqrt(N)).

Alternate:
Process nodes from min to max degree. Then connected components are friendship groups with known degree.
Remove nodes from graph after processing. Do this in reverse using a DSU. Runtime is O(NlogN).
*/

// ============================== BEGIN TEMPLATE ==============================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
// =============================== END TEMPLATE ===============================

const int MAXN = 1e5+5;

int N, M;
vector<int> adj[MAXN];

int degree[MAXN];
bool isActive[MAXN];
queue<int> q;

int dfsComp(int n) {
    isActive[n] = false;
    int ans = 1;
    for (int e : adj[n]) if (isActive[e]) {
        ans += dfsComp(e);        
    }
    return ans;
}

int solve(int K) {
    rep(n, 0, N) degree[n] = sz(adj[n]);
    
    // Mark nodes that are active
    while (!q.empty()) q.pop();
    rep(n, 0, N) {
        if (degree[n] >= K) isActive[n] = true;
        else {
            isActive[n] = false;
            q.push(n);
        }
    }

    // Process non-marked nodes
    while (!q.empty()) {
        int n = q.front(); q.pop();
        for (int e : adj[n]) {
            degree[e]--;
            if (isActive[e] && degree[e] < K) {
                // Newly non-marked node
                isActive[e] = false;
                q.push(e);
            }
        }
    }

    // Find largest component
    int largest = 0;
    rep(i, 0, N) {
        if (isActive[i]) {
            int compSize = dfsComp(i);
            largest = max(largest, compSize);
        }
    }
    return largest;
}

int main() {
    cin >> N >> M;
    rep(i, 0, M) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans = 0;
    rep(k, 1, N) {
        int maxNum = solve(k);
        // cout << k << " -> " << maxNum << "\n";
        if (maxNum == 0) break;
        else ans = max(ans, k * maxNum);
    }
    cout << ans << "\n";
}
