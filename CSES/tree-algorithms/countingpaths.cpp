#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5, MAXL = 18;

int N, M;
int depth[MAXN], parent[MAXL][MAXN], addPre[MAXN], addPost[MAXN], ans[MAXN];
vi adj[MAXN];

void dfs(int n, int p) {
    depth[n] = depth[p] + 1;
    parent[0][n] = p;
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs(e, n);
    }
}

int dfs2(int n, int p) {
    int cnt = addPre[n];
    for (int e : adj[n]) {
        if (e == p) continue;
        cnt += dfs2(e, n);
    }
    ans[n] = cnt;
    cnt += addPost[n];
    return cnt;
}

void addPath(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int origA = a, origB = b;
    for (int i = MAXL-1; i >= 0; i--) {
        if (depth[a]-depth[b] >= 1 << i) {
            a = parent[i][a];
        }
    }
    if (a == b) {
        // Line path
        addPre[origA]++;
        addPost[origB]--;
        return;
    }
    for (int i = MAXL-1; i >= 0; i--) {
        if (parent[i][a] != parent[i][b]) {
            a = parent[i][a];
            b = parent[i][b];
        }
    }
    int lca = parent[0][a];
    // V path
    addPre[origA]++;
    addPre[origB]++;
    addPre[lca]--;
    addPost[lca]--;
}

void solve() {
    cin >> N >> M;
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    depth[0] = -1;
    dfs(0, 0);
    rep(i, 1, MAXL) {
        rep(n, 0, N) {
            parent[i][n] = parent[i-1][parent[i-1][n]];
        }
    }
    rep(i, 0, M) {
        cin >> a >> b;
        a--, b--;
        addPath(a, b);
    }
    dfs2(0, 0);
    rep(i, 0, N) cout << ans[i] << (i == N-1 ? '\n' : ' ');
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}