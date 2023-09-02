/*
dp[i][j] = # ways to make array of length i, last j elements are distinct from each other.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 4001;
const int MOD = 998244353;

int N, K;
int dp[MAXN][MAXN], suf[MAXN][MAXN];
int powK[MAXN];

void solve() {
    cin >> N >> K;
    powK[0] = 1;
    rep(i, 1, N+1) powK[i] = ((ll) powK[i-1] * K) % MOD;

    dp[1][1] = K;
    int ans = 0;
    rep(i, 2, N+1) {
        // Suffix sums
        for (int j = K; j >= 0; j--) {
            suf[i-1][j] = (suf[i-1][j+1] + dp[i-1][j]) % MOD;
        }
        // Main DP
        rep(j, 0, K) {
            if (j == 0) {
                // Use final element to reset
                dp[i][j] = dp[i-1][K-1];
                ans = (ans + (ll) dp[i][j] * powK[N-i]) % MOD;
            } else {
                // Add new distinct element
                dp[i][j] = (dp[i][j] + (ll) dp[i-1][j-1] * (K-j+1)) % MOD;
                // Reuse previously distinct element
                // rep(oj, j, K) {
                //     dp[i][j] = (dp[i][j] + dp[i-1][oj]) % MOD;
                // }
                dp[i][j] = (dp[i][j] + suf[i-1][j]) % MOD;
            }
            // cout << dp[i][j] << "\t";
        }
        // cout << endl;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
