#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N, M;
vi adj[MAXN];

bool vis[MAXN];
stack<int> nodes;
vector<int> cycle;

void dfs(int n, int p) {
    nodes.push(n);
    vis[n] = true;
    for (int e : adj[n]) {
        if (e == p) continue;
        if (vis[e]) {
            // Cycle
            cycle.push_back(e);
            while (nodes.top() != e) {
                cycle.push_back(nodes.top());
                nodes.pop();
            }
            cycle.push_back(e);
            cout << sz(cycle) << '\n';
            rep(i, 0, sz(cycle)) {
                if (i != 0) cout << ' ';
                cout << cycle[i];
            }
            cout << '\n';
            exit(0);
        }
        dfs(e, n);
    }
    nodes.pop();
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    rep(i, 1, N+1) {
        if (!vis[i]) dfs(i, i);
    }
    cout << "IMPOSSIBLE\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}