#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 501, MOD = 1e9+7;

int N, K, M[MAXN];
vector<ll> dp[MAXN], pre[MAXN];

void solve() {
    cin >> N >> K;
    rep(i, 1, N+1) {
        M[i] = i*(i-1)/2+1;
        dp[i] = vector<ll>(M[i]);
        pre[i] = vector<ll>(M[i]);
    }
    dp[1][0] = 1;
    pre[1][0] = 1;
    rep(i, 2, N+1) {
        rep(j, 0, M[i]) {
            dp[i][j] = (pre[i-1][min(j, M[i-1]-1)] - (j-i < 0 ? 0 : pre[i-1][j-i])) % MOD;
            pre[i][j] = (j == 0 ? 0 : pre[i][j-1]) + dp[i][j];
            debug << dp[i][j] << ' ';
        }
        debug << endl;
    }
    cout << dp[N][K] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}