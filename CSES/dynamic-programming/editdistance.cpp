#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 5001, INF = 1e9;

int N, M;
string S, T;
int dp[MAXN][MAXN];

void solve() {
    cin >> S >> T;
    N = sz(S), M = sz(T);
    rep(i, 0, N+1) dp[i][0] = i;
    rep(j, 0, M+1) dp[0][j] = j;
    rep(i, 1, N+1) {
        rep(j, 1, M+1) {
            dp[i][j] = INF;
            // Replace or already match
            if (S[i-1] == T[j-1]) dp[i][j] = min(dp[i-1][j-1], dp[i][j]);
            else dp[i][j] = min(dp[i-1][j-1]+1, dp[i][j]);
            // Remove from S or T, or add to S or T
            dp[i][j] = min(dp[i-1][j]+1, dp[i][j]);
            dp[i][j] = min(dp[i][j-1]+1, dp[i][j]);
        }
    }
    cout << dp[N][M] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}