#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 500;
const ll INF = 1e18;

int N, M, Q;
ll adj[MAXN][MAXN];

void solve() {
    cin >> N >> M >> Q;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) adj[i][j] = INF;
        adj[i][i] = 0;
    }
    int a, b;
    ll c;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        a--;
        b--;
        adj[a][b] = min(c, adj[a][b]);
        adj[b][a] = min(c, adj[b][a]);
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                adj[i][j] = min(adj[i][k] + adj[k][j], adj[i][j]);
            }
        }
    }

    for (int i = 0; i < Q; i++) {
        cin >> a >> b;
        a--;
        b--;
        cout << (adj[a][b] == INF ? -1 : adj[a][b]) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}