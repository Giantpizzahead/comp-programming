#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 402-395;

int N;
ll M;
ll fact[MAXN], invFact[MAXN];
ll dp[MAXN][3][MAXN];

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = r * b % M;
        b = b * b % M;
        e /= 2;
    }
    return r;
}

ll nCk(int a, int b) {
    // debug << "nCk " << a << " " << b << " = " << fact[a] * invFact[b] % M * invFact[a-b] % M << endl;
    return fact[a] * invFact[b] % M * invFact[a-b] % M;
}

void solve() {
    cin >> N >> M;
    fact[0] = 1, invFact[0] = 1;
    rep(i, 1, MAXN) {
        fact[i] = fact[i-1] * i % M;
        invFact[i] = powmod(fact[i], M-2);
        cout << fact[i] << " " << invFact[i] << '\n';
    }

    rep(j, 0, 3) dp[0][j][0] = 1;
    dp[1][0][1] = 1, dp[1][1][1] = 1, dp[1][2][0] = 1;
    rep(i, 2, N+1) {
        rep(j, 0, 3) {
            int lowSteps = i/2, highSteps = i;
            rep(k, lowSteps, highSteps+1) {
                // For each middle location
                rep(l, 0, i) {
                    // For each split steps
                    int r = i-1-l;
                    rep(s, 0, k) {
                        debug << "trans " << l << " " << r << " " << s << " " << k-1-s << endl;
                        ll val;
                        if (j == 0) {
                            val = dp[l][1][s] * dp[r][1][k-1-s] % M;
                            val = val * nCk(k-1, s) % M;
                        } else if (j == 1) {
                            val = dp[l][1][s] * dp[r][2][k-1-s] % M;
                            val = val * nCk(k-1, s) % M;
                        } else {
                            val = dp[l][2][s] * dp[r][2][k-1-s] % M;
                            val = val * nCk(k-1, s) % M;
                        }
                        dp[i][j][k] = (dp[i][j][k] + val) % M;
                    }
                }
                debug << "dp[" << i << "][" << j << "][" << k << "] = " << dp[i][j][k] << endl;
            }
        }
    }

    ll ans = 0;
    rep(k, 0, N+1) ans = (ans + dp[N][0][k]) % M;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}