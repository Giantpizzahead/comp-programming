/**
 * Optimal centroid picking (node with the minimum largest ST size)
 * Runtime: 0.337 avg, 0.49s worst
 * Reasoning: There are either one or two centroids in a tree. This method takes more time to run (second DFS), and it
 * will end up finding that one centroid if there's only one. If there is two, then picking either centroid would be
 * nearly identical, so the runtime isn't improved at all.
 */

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+1;

int N, K;
ll answer = 0;
int stSize[MAXN];
vi adj[MAXN];
bool blocked[MAXN];

int dfsSize(int n, int p) {
    stSize[n] = 1;
    for (int e : adj[n]) {
        if (e == p || blocked[e]) continue;
        stSize[n] += dfsSize(e, n);
    }
    return stSize[n];
}

int currN, bestCentroid, bestSTSize;
int pathCnt[MAXN];
stack<int> toAdd;

void dfsCentroid(int n, int p) {
    int maxSTSize = currN - stSize[n];
    for (int e : adj[n]) {
        if (e == p || blocked[e]) continue;
        maxSTSize = max(stSize[e], maxSTSize);
        dfsCentroid(e, n);
    }
    if (maxSTSize < bestSTSize) {
        bestSTSize = maxSTSize;
        bestCentroid = n;
    }
}

int findCentroid(int n) {
    dfsSize(n, n);
    currN = stSize[n];
    bestCentroid = -1;
    bestSTSize = INT32_MAX;
    dfsCentroid(n, n);
    return bestCentroid;
}

void dfsCount(int n, int p, int d) {
    if (K-d < currN) answer += pathCnt[K-d];
    if (d >= K) return;
    toAdd.push(d);
    for (int e : adj[n]) {
        if (e == p || blocked[e]) continue;
        dfsCount(e, n, d+1);
    }
}

void solveRec(int n) {
    n = findCentroid(n);
    // Find all paths with exactly k edges that include (or go through) the centroid
    rep(i, 0, currN) pathCnt[i] = 0;
    pathCnt[0] = 1;
    for (int e : adj[n]) {
        if (blocked[e]) continue;
        dfsCount(e, n, 1);
        while (!toAdd.empty()) {
            pathCnt[toAdd.top()]++;
            toAdd.pop();
        }
    }
    // cout << "center " << n << " = " << answer << endl;
    blocked[n] = true;
    for (int e : adj[n]) {
        if (!blocked[e]) solveRec(e);
    }
}

void solve() {
    cin >> N >> K;
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    solveRec(1);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}