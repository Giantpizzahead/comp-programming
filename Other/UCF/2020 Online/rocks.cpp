#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 15;
const ll INF = 1e18;

int T, A, B, N, M;
ll adj[MAXN+2][MAXN+2];
// dp[mask][n][i] = Min time to get here visitng all stops in mask, with n walls + concerts, at node i
ll dp[1 << MAXN][MAXN+1][MAXN];
bool hasA[MAXN], hasB[MAXN];

void solve() {
    cin >> T >> A >> B >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> hasA[i] >> hasB[i];
    }
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            adj[i][j] = INF;
        }
    }
    for (int i = 0; i < N+2; i++) adj[i][i] = 0;
    int a, b;
    ll c;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        a--;
        b--;
        if (a > b) swap(a, b);
        if (a == -1) a = N;
        else if (a == N) a = N+1;
        if (b == -1) b = N;
        else if (b == N) b = N+1;
        adj[a][b] = min(c, adj[a][b]);
        adj[b][a] = min(c, adj[b][a]);
    }
    // for (int k = 0; k < N+2; k++) {
    //     for (int i = 0; i < N+2; i++) {
    //         for (int j = 0; j < N+2; j++) {
    //             adj[i][j] = min(adj[i][k] + adj[k][j], adj[i][j]);
    //         }
    //     }
    // }
    // cout << "adj:\n";
    // for (int i = 0; i < N+2; i++) {
    //     for (int j = 0; j < N+2; j++) {
    //         cout << adj[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    for (int i = 0; i < (1 << N); i++) {
        for (int n = 0; n <= N; n++) {
            for (int j = 0; j < N; j++) {
                dp[i][n][j] = INF;
            }
        }
    }
    // First transitions
    for (int i = 0; i < N; i++) {
        if (adj[N][i] != INF) {
            dp[1 << i][0][i] = adj[N][i];
            if (hasA[i]) dp[1 << i][1][i] = min(adj[N][i] + A, dp[1 << i][1][i]);
            if (hasB[i]) dp[1 << i][1][i] = min(adj[N][i] + B, dp[1 << i][1][i]);
        }
    }
    // Forward DP
    int answer = -1;
    if (adj[N][N+1] <= T) answer = 0;
    for (int mask = 0; mask < (1 << N); mask++) {
        for (int n = 0; n <= N; n++) {
            for (int i = 0; i < N; i++) {
                if ((mask & (1 << i)) == 0) continue;  // Invalid state
                // Transition from any previous cities
                int oldMask = mask ^ (1 << i);
                for (int j = 0; j < N; j++) {
                    if ((oldMask & (1 << j)) == 0) continue;  // Invalid
                    // Transition from this city
                    dp[mask][n][i] = min(dp[oldMask][n][j] + adj[j][i], dp[mask][n][i]);
                    if (hasA[i] && n != 0) {
                        // Go to wall
                        dp[mask][n][i] = min(dp[oldMask][n-1][j] + adj[j][i] + A, dp[mask][n][i]);
                    }
                    if (hasB[i] && n != 0) {
                        // Go to concert
                        dp[mask][n][i] = min(dp[oldMask][n-1][j] + adj[j][i] + B, dp[mask][n][i]);
                    }
                }
                // Update answer
                if (dp[mask][n][i] + adj[i][N+1] <= T) {
                    answer = max(n, answer);
                }
            }
        }
    }
    if (answer == -1) cout << "Book a flight!\n";
    else cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}