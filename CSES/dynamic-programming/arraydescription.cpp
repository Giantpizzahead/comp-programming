#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5, MAXM = 102, MOD = 1e9+7;

int N, M;
int A[MAXN];
int dp[MAXM], oldDP[MAXM];

void solve() {
    cin >> N >> M;
    rep(i, 0, N) cin >> A[i];

    if (A[0] == 0) rep(i, 1, M+1) dp[i] = 1;
    else dp[A[0]] = 1;

    rep(i, 1, N) {
        swap(dp, oldDP);
        rep(j, 1, M+1) dp[j] = 0;
        if (A[i] == 0) {
            rep(j, 1, M+1) {
                dp[j] = ((oldDP[j-1] + oldDP[j]) % MOD + oldDP[j+1]) % MOD;
            }
        } else {
            dp[A[i]] = ((oldDP[A[i]-1] + oldDP[A[i]]) % MOD + oldDP[A[i]+1]) % MOD;
        }
    }

    int ans = 0;
    rep(j, 1, M+1) ans = (ans + dp[j]) % MOD;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}