#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using namespace std;
using ll = long long;

const int MAXN = 1505;

const ll MOD = 1e9+7;

int N, x;
ll fact[MAXN], nCk[MAXN][MAXN];

ll powmod(ll b, ll e, ll m) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) {
            r = r*b % m;
        }
        e >>= 1;
        b = b*b % m;
    }
    return r;
}

ll modinv(ll n) {
    return powmod(n, MOD-2, MOD);
}

void genComb() {
    fact[0] = 1;
    rep(i, 1, N+1) fact[i] = fact[i-1] * i % MOD;
    rep(i, 0, N+1) {
        rep(j, 0, i+1) {
            nCk[i][j] = fact[i] * modinv(fact[j]) % MOD * modinv(fact[i-j]) % MOD;
        }
    }
}

// dp[i][j] = # of ways to fill j numbers only in r2, k numbers only in r1, i numbers split amongst both (unique)
ll dp[MAXN][MAXN][3];

void genDP() {
    rep(j, 0, N+1) {
        rep(k, 0, 3) {
            dp[0][j][k] = fact[j] * fact[k] % MOD;
        }
    }
    rep(i, 1, N+1) {
        rep(j, 0, N+1) {
            rep(k, 0, 3) {
                dp[i][j][k] = dp[i-1][j][k] * (i+j+k+1) % MOD;
            }
        }
    }
    // Additional numbers at the end
    rep(i, 0, N+1) {
        rep(j, 0, N+1) {
            rep(k, 0, 3) {
                int f = N-i-j-k-2;
                if (f < 0) dp[i][j][k] = 0;
                else dp[i][j][k] = dp[i][j][k] * fact[f] % MOD;
            }
        }
    }
}

// sum[i][j] = # of ways to MAYBE fill j numbers in r2, i numbers in both
// Definitely fill k numbers in r1
ll sum[MAXN][MAXN][3];
ll preSum[MAXN][MAXN][3];

void genSum() {
    // First prefix sum
    rep(i, 0, N+1) {
        rep(j, 0, N+1) {
            if (i+j >= N) continue;
            rep(k, 0, 3) {
                for (int b = j; b >= 0; b--) {
                    ll toAdd = dp[i][b][k] * nCk[j][b] % MOD;
                    sum[i][j][k] += toAdd;
                }
                sum[i][j][k] %= MOD;
            }
        }
    }
    // Second prefix sum
    for (int i = N; i >= 0; i--) {
        rep(j, 0, N+1) {
            if (i+j >= N) continue;
            rep(k, 0, 3) {
                ll newSum = 0;
                for (int a = i; a >= 0; a--) {
                    ll toAdd = sum[a][j][k] * nCk[i][a] % MOD;
                    newSum += toAdd;
                }
                sum[i][j][k] = newSum % MOD;
            }
        }
    }
    // rep(i, 0, N+1) {
    //     rep(j, 0, N+1) {
    //         cout << sum[i][j][0] << " \n"[j==N];
    //     }
    // }

    // Final prefix sum
    rep(i, 0, N+1) {
        rep(j, 0, N+1) {
            rep(k, 0, 3) {
                preSum[i][j][k] = ((j == 0 ? 0 : preSum[i][j-1][k]) + sum[i][j][k]) % MOD;
            }
        }
    }
}

void genAnswer() {
    // Fix c, d, and a
    ll ans = 0;
    rep(c, 0, x) {
        rep(d, x+2, N+2) {
            int k = 2;
            if (c == 0) k--;
            if (d == N+1) k--;
            int botNum = max(c-1, 0);
            int topNum = max(N-d, 0);
            int firstJ = d-(d-1)-1;
            int lastJ = d-(x+1)-1;
            ll toAdd = (x-c) * (preSum[botNum+topNum][lastJ][k] - (firstJ == 0 ? 0 : preSum[botNum+topNum][firstJ-1][k])) % MOD;
            if (toAdd < 0) toAdd += MOD;
            // cout << c << " " << d << " " << a << " = " << "sum[" << botNum+topNum << "][" << d-a-1 << "][" << k << "] = " << toAdd << '\n';
            ans = (ans + toAdd) % MOD;
        }
    }
    cout << ans << '\n';
}

void solve() {
    cin >> N >> x;
    genComb();
    genDP();
    genSum();
    genAnswer();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}