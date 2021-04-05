#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e6+5, MOD = 1e9+7;

int N;
int dp[MAXN][2];

void solve() {
    dp[1][0] = 1, dp[1][1] = 1;
    rep(i, 2, MAXN) {
        dp[i][0] = ((ll) dp[i-1][0] * 4 + dp[i-1][1]) % MOD;
        dp[i][1] = (dp[i-1][0] + (ll) dp[i-1][1] * 2) % MOD;
    }
    int T; cin >> T;
    rep(i, 0, T) {
        cin >> N;
        cout << (dp[N][0] + dp[N][1]) % MOD << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}