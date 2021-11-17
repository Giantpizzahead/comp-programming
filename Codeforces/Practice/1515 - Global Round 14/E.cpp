#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 405;

int N;
ll M;
ll fact[MAXN], invFact[MAXN], pow2[MAXN];
ll dp[MAXN][MAXN];

ll powmod(ll b, int e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r*b % M;
        b = b*b % M;
        e >>= 1;
    }
    return r;
}

ll nCk(int n, int k) {
    assert(n >= 0 && k >= 0 && k <= n);
    return fact[n] * invFact[k] % M * invFact[n-k] % M;
}

void solve() {
    cin >> N >> M;
    // Precalc
    pow2[0] = 1, fact[0] = 1, invFact[0] = 1;
    rep(i, 1, MAXN) {
        pow2[i] = pow2[i-1] * 2 % M;
        fact[i] = fact[i-1] * i % M;
        invFact[i] = powmod(fact[i], M-2);
    }
    // DP
    dp[0][0] = 1;
    rep(i, 1, N+2) {
        rep(j, 1, i+1) {
            rep(k, 0, i-1) {
                if (dp[k][j-1] == 0) continue;
                int ns = i-k-1;
                dp[i][j] += dp[k][j-1] * pow2[ns-1] % M * nCk(i-j, ns) % M;
            }
            dp[i][j] %= M;
            // cout << dp[i][j] << " \n"[j==i];
        }
    }
    ll ans = 0;
    rep(j, 0, N+2) ans = (ans + dp[N+1][j]) % M;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}