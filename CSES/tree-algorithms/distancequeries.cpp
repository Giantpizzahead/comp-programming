#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5, MAXL = 20;

int N, Q;
int D[MAXN], P[MAXL][MAXN];
vi adj[MAXN];

void dfs(int n, int p) {
    D[n] = D[p] + 1;
    P[0][n] = p;
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs(e, n);
    }
}

int lca(int a, int b) {
    if (D[a] < D[b]) swap(a, b);
    for (int j = MAXL-1; j >= 0; j--) {
        if (D[a] - D[b] >= (1 << j)) {
            a = P[j][a];
        }
    }
    if (a == b) return a;
    for (int j = MAXL-1; j >= 0; j--) {
        if (P[j][a] != P[j][b]) {
            a = P[j][a];
            b = P[j][b];
        }
    }
    return P[0][a];
}

void solve() {
    cin >> N >> Q;
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    D[0] = -1;
    dfs(0, 0);
    rep(i, 1, MAXL) {
        rep(n, 0, N) {
            P[i][n] = P[i-1][P[i-1][n]];
        }
    }
    rep(i, 0, Q) {
        cin >> a >> b;
        a--, b--;
        int c = lca(a, b);
        cout << D[a] + D[b] - 2 * D[c] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}