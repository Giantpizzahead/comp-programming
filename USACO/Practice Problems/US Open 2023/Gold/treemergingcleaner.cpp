#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr

struct Pair {
    int a, b;
};

vector<Pair> merges;

struct DisjointSet {
    int N;
    vector<int> V, M;

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
        a = find(a), b = find(b);
        if (a == b) return a;
        else if (abs(V[a]) > abs(V[b])) {
            M[a] = max(M[a], M[b]), M[b] = -1;
            V[a] += V[b], V[b] = a;
            return a;
        } else {
            M[b] = max(M[b], M[a]), M[a] = -1;
            V[b] += V[a], V[a] = b;
            return b;
        }
    }
} ds(1);

struct Tree {
    int N, R;
    vector<int> parent, depth;
    vector<vector<int>> kids;
    vector<bool> active;

    Tree(int n) : N(n) {
        depth = vector<int>(n, 0);
        active = vector<bool>(n);
        parent = vector<int>(n, -1);
        kids = vector<vector<int>>(n);
    }

    void init() {
        rep(i, 0, N) if (parent[i] == -1 && sz(kids[i]) != 0) {
            R = i;
            break;
        }
        dfs(R, 0);
    }

    void merge(int a, int b) {
        if (a < b) swap(a, b);
        // debug << "merging " << a+1 << " and " << b+1 << endl;
        assert(a > b && active[a] && active[b] && parent[a] == parent[b]);
        for (int e : kids[b]) {
            kids[a].push_back(e);
            parent[e] = a;
        }
        kids[b].clear();
        // Erase b from its parent
        rep(i, 0, sz(kids[parent[b]])) if (kids[parent[b]][i] == b) {
            kids[parent[b]].erase(kids[parent[b]].begin() + i);
            break;
        }
        parent[b] = -1;
        active[b] = false;
        debug << "merged " << a+1 << " and " << b+1 << endl;
        merges.push_back({a, b});
    }

    void dfs(int n, int d) {
        active[n] = true;
        depth[n] = d;
        for (int e : kids[n]) dfs(e, d+1);
    }

    vector<int> getPath(int n) {
        vector<int> path;
        while (n != R) {
            path.push_back(n);
            n = parent[n];
        }
        path.push_back(R);
        reverse(all(path));
        return path;
    }
};

Tree A(1), B(1);

void attemptMerge(int a, int b) {
    // First, merge parent nodes
    if (A.parent[a] != A.parent[b]) attemptMerge(A.parent[a], A.parent[b]);
    // Now, merge this node
    ds.merge(a, b), A.merge(a, b);
}

void solve() {
    int N; cin >> N;
    ds = DisjointSet(N);
    A = Tree(N), B = Tree(N);
    merges = vector<Pair>();

    int e = N;
    rep(i, 0, e-1) {
        int a, b; cin >> a >> b;
        a--, b--;
        A.kids[b].push_back(a);
        A.parent[a] = b;
    }
    A.init();

    cin >> e;
    rep(i, 0, e-1) {
        int a, b; cin >> a >> b;
        a--, b--;
        B.kids[b].push_back(a);
        B.parent[a] = b;
    }
    B.init();

    // Merge all remaining nodes
    bool didSomething = true;
    while (didSomething) {
        didSomething = false;

        // Merge nodes that exist in both trees
        for (int n = N-1; n >= 0; n--) {
            if (!A.active[n] || !B.active[n]) continue;
            // Find paths to both nodes and merge the paths
            vector<int> pathA = A.getPath(n);
            vector<int> pathB = B.getPath(n);
            // cout << "paths: ";
            // for (int e : pathA) cout << e+1 << " ";
            // cout << "vs. ";
            // for (int e : pathB) cout << e+1 << " ";
            // cout << endl;
            rep(i, 0, sz(pathA)) {
                int a = pathA[i], b = pathB[i];
                if (a != b) {
                    attemptMerge(a, b);
                    didSomething = true;
                    break;
                }
            }
        }

        // Attempt to merge two nodes
        rep(n, 0, N) {
            if (B.active[n] || !A.active[n] || sz(A.kids[n]) != 0) continue;
            // Find another node in the same subtree as this one
            rep(m, 0, N) {
                if (!A.active[m]) continue;
                if (A.parent[n] == A.parent[m]) {
                    debug << "checked " << n+1 << " " << m+1 << endl;
                    // This node works
                    attemptMerge(n, m);
                    didSomething = true;
                    break;
                }
            }
        }
    }

    // Sort merges by depth
    sort(all(merges), [&](const Pair& a, const Pair& b){
        return A.depth[a.a] < A.depth[b.a];
    });
    assert(sz(merges) == N-e);
    debug << sz(merges) << "\n";
    for (Pair p : merges) cout << p.a+1 << " " << p.b+1 << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) {
        debug << "Test " << i+1 << ":" << endl;
        solve();
        debug << "\n";
    }
    return 0;
}
