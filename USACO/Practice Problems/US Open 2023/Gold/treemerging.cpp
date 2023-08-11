#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

struct Pair {
    int a, b;
};

struct DisjointSet {
    int N;
    vector<int> V, M;
    vector<Pair> merges;

    DisjointSet(int n) : N(n) {
        V = vector<int>(n, -1);
        M = vector<int>(n);
        rep(i, 0, n) M[i] = i;
    }

    int find(int n) {
        if (V[n] < 0) return n;
        int r = find(V[n]);
        V[n] = r;
        return r;
    }

    int merge(int a, int b) {
        // cout << "merged " << a+1 << " and " << b+1 << endl;
        a = find(a), b = find(b);
        if (a == b) return a;
        merges.push_back({a, b});
        if (abs(V[a]) > abs(V[b])) {
            M[a] = max(M[a], M[b]), M[b] = -1;
            V[a] += V[b], V[b] = a;
            return a;
        } else {
            M[b] = max(M[b], M[a]), M[a] = -1;
            V[b] += V[a], V[a] = b;
            return b;
        }
    }
};

struct Tree {
    int N, R;
    vector<int> val, parent, depth;
    vector<vector<int>> kids;

    Tree(int n) : N(n) {
        val = vector<int>(n, -1);
        parent = vector<int>(n, -1);
        depth = vector<int>(n, 0);
        kids = vector<vector<int>>(n);
    }

    void findRoot() {
        rep(i, 0, N) if (parent[i] == -1 && sz(kids[i]) != 0) {
            R = i;
            break;
        }
        dfs(R, 0);
    }

    void dfs(int n, int d) {
        depth[n] = d;
        for (int e : kids[n]) dfs(e, d+1);
    }

    bool isActive(int n) {
        return parent[n] != -1 || sz(kids[n]) > 0;
    }

    vector<int> getPath(int n, DisjointSet& ds) {
        vector<int> path;
        while (n != R) {
            path.push_back(ds.find(n));
            n = parent[n];
        }
        path.push_back(ds.find(R));
        reverse(all(path));
        return path;
    }
};

void solve() {
    int N; cin >> N;
    // cout << "in " << N << endl;
    DisjointSet ds(N);
    Tree A(N), B(N);
    int e = N;
    rep(i, 0, e-1) {
        int a, b; cin >> a >> b;
        // cout << "in " << a << " " << b << endl;
        a--, b--;
        A.kids[b].push_back(a);
        A.parent[a] = b;
    }
    A.findRoot();
    cin >> e;
    // cout << "in " << e << endl;
    rep(i, 0, e-1) {
        int a, b; cin >> a >> b;
        // cout << "in " << a << " " << b << endl;
        a--, b--;
        B.kids[b].push_back(a);
        B.parent[a] = b;
    }
    B.findRoot();

    // Merge nodes that exist if possible
    for (int n = N-1; n >= 0; n--) {
        // Is this node active in both trees?
        if (A.isActive(n) && B.isActive(n)) {
            // Find paths to both nodes and merge the paths
            vector<int> pathA = A.getPath(n, ds);
            vector<int> pathB = B.getPath(n, ds);
            rep(i, 0, sz(pathA)) if (pathA[i] != pathB[i]) {
                // Merge these nodes
                int a = pathA[i], b = pathB[i];
                while (a != b) {
                    ds.merge(a, b);
                    a = ds.find(A.parent[a]);
                    b = ds.find(B.parent[b]);
                }
            }
            // cout << "paths " << n+1 << ":" << endl;
            // for (int e : pathA) cout << e+1 << " ";
            // cout << endl;
            // for (int e : pathB) cout << e+1 << " ";
            // cout << endl;
        }
    }

    // Merge all remaining nodes
    bool didSomething = true;
    while (didSomething) {
        didSomething = false;
        rep(n, 0, N) {
            // cout << n << " " << B.isActive(n) << " " << ds.M[n] << endl;
            if (B.isActive(n) || ds.M[ds.find(n)] > n) continue;  // Not deleted or already merged
            // cout << "trying to merge " << n+1 << endl;
            // Find a greater node in the same subtree as this one
            rep(m, n+1, N) {
                // cout << m << " " << A.parent[m] << endl;
                if (A.parent[m] != -1 && ds.find(A.parent[n]) == ds.find(A.parent[m])) {
                    // cout << "found " << m+1 << " -> " << ds.find(A.parent[m])+1 << endl;
                    // This node works
                    ds.merge(n, m);
                    didSomething = true;
                    break;
                }
            }
        }
    }

    // Sort merges by depth
    sort(all(ds.merges), [&](const Pair& a, const Pair& b){
        return A.depth[a.a] < A.depth[b.a];
    });
    assert(sz(ds.merges) == N-e);
    cout << sz(ds.merges) << "\n";
    for (Pair p : ds.merges) cout << p.a+1 << " " << p.b+1 << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) {
        // cout << "Test " << i+1 << ":" << endl;
        solve();
        // cout << "\n";
    }
    return 0;
}
