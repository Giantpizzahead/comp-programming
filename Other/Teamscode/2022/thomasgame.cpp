#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;
int N, M, Q;

int deg[MAXN];
unordered_set<int> adj[MAXN];

void solve() {
    cin >> N >> M >> Q;
    rep(i, 0, N) deg[i] = N-1;
    rep(i, 0, M) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].insert(b);
        adj[b].insert(a);
        deg[a]--, deg[b]--;
    }
    // rep(i, 0, N) cout << deg[i] << " \n"[i==N-1];
    vector<int> toCheck;
    rep(i, 0, N) if (deg[i] <= 3) toCheck.push_back(i);
    rep(i, 0, Q) {
        int a, b; cin >> a >> b;
        a--, b--;
        int ans = 0;
        for (int n : toCheck) {
            if (n == a || n == b) continue;
            int edges = deg[n];
            if (!adj[a].count(n)) edges--;
            if (!adj[b].count(n)) edges--;
            // cout << n << ": " << edges << "\n";
            if (edges <= 1) ans++;
        }
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}