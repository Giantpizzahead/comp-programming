#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 305;
const ll INF = 1e18;

int N, M;
int locs[MAXN];
ll dp[MAXN][MAXN];
ll bike[MAXN][MAXN], walk[MAXN][MAXN];

void solve() {
    int X;
    cin >> N >> X;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            bike[i][j] = INF;
            walk[i][j] = INF;
        }
        bike[i][i] = 0;
        walk[i][i] = 0;
    }
    int u, v, t;
    for (int i = 0; i < X; i++) {
        cin >> u >> v >> t;
        bike[u][v] = t;
        bike[v][u] = t;
    }
    cin >> X;
    for (int i = 0; i < X; i++) {
        cin >> u >> v >> t;
        walk[u][v] = t;
        walk[v][u] = t;
    }
    cin >> M;
    for (int i = 1; i <= M; i++) {
        cin >> locs[i];
    }
    M++;
    locs[0] = 0;
    locs[M++] = 0;
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                bike[i][j] = min(bike[i][k] + bike[k][j], bike[i][j]);
                walk[i][j] = min(walk[i][k] + walk[k][j], walk[i][j]);
            }
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i < N; i++) dp[0][i] = INF;
    for (int i = 1; i < M; i++) {
        for (int j = 0; j < N; j++) {
            ll bestTrans = INF;
            for (int k = 0; k < N; k++) {
                // Bike previously at node k, move to node j
                ll cost = dp[i-1][k] + walk[locs[i-1]][k] + bike[k][j] + walk[j][locs[i]];
                bestTrans = min(cost, bestTrans);
            }
            // Don't move the bike
            ll cost = dp[i-1][j] + walk[locs[i-1]][locs[i]];
            bestTrans = min(cost, bestTrans);
            dp[i][j] = bestTrans;
        }
    }
    cout << dp[M-1][0] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}