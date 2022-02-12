/**
 * Solution:
 * Runtime: O((N+M) * log(N))
 */

#include "swap.h"

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;
const int INF = 1e9+7;

int N, M, R;
struct Edge {
    int a, b, c;
};
vector<Edge> E;
struct Pair {
    int n, c;
};
vector<Pair> kids[MAXN];
Pair parent[MAXN];
int activeTime[MAXN], depth[MAXN];

struct DisjointSet {
    int V[MAXN];
    bool isPath[MAXN];
    int pathA[MAXN], pathB[MAXN];

    void init() {
        rep(i, 0, N) {
            V[i] = -1;
            isPath[i] = true;
            pathA[i] = i;
            pathB[i] = i;
            parent[i] = {-1, -1};
            activeTime[i] = INF;
        }
    }

    int find(int n) {
        if (V[n] < 0) return n;
        int r = find(V[n]);
        V[n] = r;
        return r;
    }

    void activate(int n, int c) {
        assert(activeTime[n] == INF);
        activeTime[n] = c;
        isPath[n] = false;
        pathA[n] = -1, pathB[n] = -1;
    }

    void merge(int u, int v, int c) {
        int a = find(u), b = find(v);
        if (a == b) {
            if (isPath[a]) activate(a, c);  // No longer a path (unique edges)
            return;
        }
        if (V[b] < V[a]) {
            swap(a, b);
            swap(u, v);
        }

        // Merge into a
        kids[a].push_back({b, c});
        parent[b] = {a, c};
        V[a] += V[b];
        V[b] = a;
        if (isPath[a] && isPath[b]) {
            // Does this component still form a path?
            if ((pathA[a] == u || pathB[a] == u) && (pathA[b] == v || pathB[b] == v)) {
                // Yes
                if (pathA[a] == u) pathA[a] = pathB[a];
                else pathA[a] = pathA[a];
                if (pathA[b] == v) pathB[a] = pathB[b];
                else pathB[a] = pathA[b];
                // cout << pathA[a] << " " << pathB[a] << endl;
            } else {
                // No
                pathA[a] = -1;
                pathB[a] = -1;
                activate(a, c);
            }
        }
        isPath[a] &= isPath[b];
    }
} ds;

int dfsInit(int n, int d) {
    depth[n] = d;
    int currActive = activeTime[n];
    for (Pair& e : kids[n]) {
        currActive = min(max(dfsInit(e.n, d+1), e.c), currActive);
    }
    activeTime[n] = currActive;
    return currActive;
}

void printTree(int n, int indent = 0) {
    rep(i, 0, indent) cout << ' ';
    cout << "" << n << " (" << activeTime[n] << ")\n";
    for (Pair& e : kids[n]) {
        rep(i, 0, indent) cout << ' ';
        cout << "\\ " << e.c << '\n';
        printTree(e.n, indent+1);
    }
}

void init(int n, int m, vector<int> u, vector<int> v, vector<int> w) {
    N = n; M = m;
    // Gen DSU tree
    ds.init();
    rep(i, 0, M) E.push_back({u[i], v[i], w[i]});
    sort(all(E), [](const Edge& a, const Edge& b) {
        return a.c < b.c;
    });
    rep(i, 0, M) ds.merge(E[i].a, E[i].b, E[i].c);
    // Init tree
    rep(i, 0, N) if (parent[i].n == -1) R = i;
    dfsInit(R, 0);
    // Print tree
    // printTree(R);
}

int getMinimumFuelCapacity(int a, int b) {
    // Find LCA and get max along the way
    int ans = -1;
    while (a != b) {
        int da = depth[a], db = depth[b];
        if (da >= db) {
            ans = max(parent[a].c, ans);
            a = parent[a].n;
        }
        if (db >= da) {
            ans = max(parent[b].c, ans);
            b = parent[b].n;
        }
    }
    while (true) {
        if (activeTime[a] != INF) {
            ans = max(activeTime[a], ans);
            return ans;
        }
        if (depth[a] == 0) break;
        ans = max(parent[a].c, ans);
        a = parent[a].n;
    }
    return -1;
}
