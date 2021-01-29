#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

const int MAXN = 61, MAXM = 181;
const ll MOD = 1e9+7;

int N, K, Q, M;
int adj[MAXN][MAXN], Bs[MAXN], Bt[MAXN], S[MAXN], T[MAXN];
ll dp[MAXN][MAXM][MAXM];

void solve() {
    cin >> N >> K >> Q;
    M = N+2*Q;
    rep(i, 0, N) {
        string S; cin >> S;
        rep(j, 0, N) {
            adj[i][j] = S[j] - '0';
        }
    }
    rep(i, 0, Q) {
        cin >> Bs[i] >> S[i] >> Bt[i] >> T[i];
        S[i]--, T[i]--;
    }
    rep(i, 0, M) {
        dp[0][i][i] = 1;
    }
    rep(i, 1, K+1) {
        // Handle all queries starting at button i
        rep(j, 0, Q) {
            if (Bs[j] != i) continue;
            int s = N+j;
            rep(t, 0, M) {
                // Normal nodes
                rep(a, 0, N) {
                    if (!adj[S[j]][a]) continue;
                    dp[i][s][t] += dp[i-1][a][t];
                    dp[i][s][t] %= MOD;
                }
            }
        }
        // Handle general transition
        rep(t, 0, M) {
            rep(k, 0, N) {
                ll sumK = 0;
                rep(l, 0, N) {
                    if (!adj[k][l]) continue;
                    sumK += dp[i-1][l][t];
                    sumK %= MOD;
                }
                rep(s, 0, M-Q) {
                    dp[i][s][t] += dp[i-1][s][k] * sumK;
                    dp[i][s][t] %= MOD;
                }
            }
            rep(s, 0, M-Q) {
                dp[i][s][t] += dp[i-1][s][t];
                dp[i][s][t] %= MOD;
            }
            if (t == N-1) t += Q;
        }
        // Handle all queries ending at button i
        rep(j, 0, Q) {
            if (Bt[j] != i) continue;
            int t = N+Q+j;
            rep(s, 0, M) {
                dp[i][s][t] += dp[i-1][s][T[j]];
                dp[i][s][t] %= MOD;
            }
        }
    }
    // rep(i, 0, K+1) {
    //     rep(j, 0, M) {
    //         rep(k, 0, M) {
    //             if (dp[i][j][k]) cout << "dp[" << i << "][" << j << "][" << k << "] = " << dp[i][j][k] << endl;
    //         }
    //     }
    // }
    rep(i, 0, Q) {
        int answer = dp[K][N+i][N+Q+i];
        if (Bs[i] == Bt[i] && S[i] == T[i]) answer = (answer + 1) % MOD;
        cout << answer << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}