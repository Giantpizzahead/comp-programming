/**
 * For each connected component, get a tree of edges. Set all non-tree edges to arbitrary directions. Then,
 * use a greedy approach starting from tree leafs to "push" the odd outdegree nodes to the root. If it's possible
 * to make all of the nodes even, then this will succeed in O(N+M) time.
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2e5+5;

int N, M;
int A[MAXN], B[MAXN];
bool T[MAXN], S[MAXN], V[MAXN];
vector<int> adj[MAXN], tree;

void dfsTree(int n, int p) {
    V[n] = true;
    for (int e : adj[n]) {
        int o = (A[e] != n ? A[e] : B[e]);
        if (e == p || V[o]) continue;
        // Make edge directed away from leaf
        A[e] = o, B[e] = n;
        dfsTree(o, e);
        // Add tree edges in reverse order
        T[e] = true;
        tree.push_back(e);
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) S[i] = true;
    rep(i, 0, M) {
        cin >> A[i] >> B[i];
        A[i]--, B[i]--;
        adj[A[i]].push_back(i);
        adj[B[i]].push_back(i);
    }

    // Find tree edges
    rep(i, 0, N) if (!V[i]) dfsTree(i, -1);
    // Apply all other edges
    rep(i, 0, M) if (!T[i]) S[A[i]] = !S[A[i]];

    // Greedily set tree edge directions
    for (int e : tree) {
        if (S[A[e]]) swap(A[e], B[e]);
        S[A[e]] = !S[A[e]];
    }

    // Check if valid
    rep(i, 0, N) if (!S[i]) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    // Print edges
    rep(i, 0, M) cout << A[i]+1 << ' ' << B[i]+1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}