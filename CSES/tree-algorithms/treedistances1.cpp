#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
vi adj[MAXN];
int d1[MAXN], d2[MAXN], d1f[MAXN], ans[MAXN];

void dfs(int n, int p, int d=0) {
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs(e, n, d+1);
        d1[n] = max(d1[n], d1[e]+1);
        if (d1[n] == d1[e]+1) d1f[n] = e;
    }
    for (int e : adj[n]) {
        if (e == p || e == d1f[n]) continue;
        d2[n] = max(d2[n], d1[e]+1);
    }
}

void dfs2(int n, int p, int pd=0) {
    ans[n] = max(d1[n], pd);
    for (int e : adj[n]) {
        if (e == p) continue;
        if (e == d1f[n]) dfs2(e, n, max(d2[n]+1, pd+1));
        else dfs2(e, n, max(d1[n]+1, pd+1));
    }
}

void solve() {
    cin >> N;
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, 0);
    dfs2(0, 0);
    // rep(i, 0, N) cout << d1[i] << (i==N-1 ? '\n' : ' ');
    // rep(i, 0, N) cout << d2[i] << (i==N-1 ? '\n' : ' ');
    // rep(i, 0, N) cout << d1f[i] << (i==N-1 ? '\n' : ' ');
    rep(i, 0, N) cout << ans[i] << (i==N-1 ? '\n' : ' ');
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}