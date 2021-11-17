#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 248;

int N;
int A[MAXN];
int dp[MAXN][MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    int ans = 0;
    rep(s, 0, N) {
        rep(i, 0, N) {
            int j = i+s;
            if (j >= N) continue;
            else if (i == j) dp[i][j] = A[i];
            else {
                // Merge numbers
                dp[i][j] = -1;
                rep(k, i, j) {
                    if (dp[i][k] != -1 && dp[i][k] == dp[k+1][j]) dp[i][j] = max(dp[i][k] + 1, dp[i][j]);
                }
            }
            ans = max(dp[i][j], ans);
            debug << dp[i][j] << " \n"[j==N-1];
        }
    }
    cout << ans << '\n';
}

int main() {
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}