#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N, M;
bool valid = true;
int color[MAXN];
vi adj[MAXN];

void dfs(int n, int c) {
    color[n] = c;
    for (int e : adj[n]) {
        if (color[e] == 0) dfs(e, 3-c);
        else if (color[e] != 3-c) valid = false;
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    rep(i, 1, N+1) if (color[i] == 0) dfs(i, 1);
    if (valid) rep(i, 1, N+1) cout << color[i] << (i == N ? '\n' : ' ');
    else cout << "IMPOSSIBLE\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}