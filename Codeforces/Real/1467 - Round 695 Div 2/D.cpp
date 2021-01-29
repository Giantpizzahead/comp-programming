#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 5002, MOD = 1e9+7;

int N, K, Q;
ll A[MAXN];
int dp[MAXN][MAXN];
int contrib[MAXN];

void solve() {
    cin >> N >> K >> Q;
    rep(i, 0, N) dp[i][0] = 1;
    rep(j, 1, K+1) {
        rep(i, 0, N) {
            if (i != 0) dp[i][j] += dp[i-1][j-1];
            if (i != N-1) dp[i][j] += dp[i+1][j-1];
            dp[i][j] %= MOD;
            // cout << dp[i][j] << ' ';
        }
        // cout << endl;
    }
    rep(i, 0, N) {
        rep(j, 0, K+1) {
            contrib[i] += (ll) dp[i][j] * dp[i][K-j] % MOD;
            contrib[i] %= MOD;
        }
        // cout << contrib[i] << ' ';
    }
    // cout << endl;

    ll answer = 0;
    rep(i, 0, N) {
        cin >> A[i];
        answer = (answer + A[i] * contrib[i]) % MOD;
    }
    rep(i, 0, Q) {
        int j;
        ll x;
        cin >> j >> x; j--;
        answer -= A[j] * contrib[j] % MOD;
        answer += x * contrib[j] % MOD;
        A[j] = x;
        answer = (answer % MOD + MOD) % MOD;
        cout << answer << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}