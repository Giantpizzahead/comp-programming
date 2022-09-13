/*
https://codeforces.com/problemset/gymProblem/328369/F

Solution: Use a DFS, adding nodes in decreasing donation value, and finding the longest route at each iteration.
Runtime: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct DisjointSet {
    vi V, minO, maxO;

    DisjointSet(int n = 0) : V(n, -1), minO(n, n+1), maxO(n, -1) {}

    int find(int n) {
        if (V[n] < 0) return n;
        int r = find(V[n]);
        return r;
    }

    int size(int n) {
        return -V[find(n)];
    }

    int merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return a;
        if (V[a] < V[b]) swap(a, b);
        minO[a] = min(minO[b], minO[a]);
        maxO[a] = max(maxO[b], maxO[a]);
        V[a] += V[b];
        V[b] = a;
        return a;
    }
};

int N, M, tempN, R;
vi D, pathNum, nodeOrder, orderToID;
vector<vi> adj;

vector<bool> active;
vector<pii> toProcess;
vi pathSize;
DisjointSet ds;
multiset<int> lengths;

void dfsPath(int n, int p) {
    pathNum[n] = M;
    nodeOrder[n] = tempN++;
    pathSize[M]++;
    for (int e : adj[n]) if (e != p) dfsPath(e, n);
}

ll bestD = 0;
int bestX = -1, bestY = -1;

void tryAnswer(ll d, int x, int y) {
    if (make_tuple(d, -x, -y) > make_tuple(bestD, bestX, bestY)) {
        bestD = d;
        bestX = x;
        bestY = y;
    }
}

void solve() {
    // Parse input
    cin >> N;
    D.resize(N), pathNum.resize(N), nodeOrder.resize(N), orderToID.resize(N);
    adj.resize(N);
    rep(i, 0, N) cin >> D[i];
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b; a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    // Find paths
    rep(i, 0, N) if (sz(adj[i]) > 2) R = i;
    M = 0, tempN = 0;
    pathNum[R] = -1;
    nodeOrder[R] = tempN++;
    for (int e : adj[R]) {
        pathSize.push_back(0);
        dfsPath(e, R);
        M++;
    }

    // Process all nodes
    active.resize(N);
    ds = DisjointSet(N);
    rep(i, 0, N) {
        ds.minO[i] = nodeOrder[i], ds.maxO[i] = nodeOrder[i];
        orderToID[nodeOrder[i]] = i;
        toProcess.push_back({D[i], i});
    }
    sort(all(toProcess));
    reverse(all(toProcess));
    for (pii& p : toProcess) {
        ll d = p.first;
        int n = p.second;
        active[n] = true;
        for (int e : adj[n]) if (n != R && e != R && active[e]) ds.merge(e, n);
        // Update answer in this component (route completely inside path)
        n = ds.find(n);
        ll currD = d * ds.size(n);
        int currX = orderToID[ds.minO[n]];
        int currY = orderToID[ds.maxO[n]];
        if (currX > currY) swap(currX, currY);
        if (currD <= bestD) currD = bestD;
        tryAnswer(currD, currX, currY);
        // Update answer if going through the root
        // TODO: maybe process each path individually to avoid going through bs updates
    }

    cout << "root: " << R+1 << "\n";
    rep(i, 0, N) cout << pathNum[i] << " \n"[i==N-1];

    cout << bestD << "\n";
    cout << bestX+1 << " " << bestY+1 << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}