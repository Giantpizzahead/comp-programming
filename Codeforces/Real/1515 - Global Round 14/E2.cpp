#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = unsigned long long;

const int MAXN = 402;

typedef unsigned long long ull;
struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(-1ULL / b) {}
	ull reduce(ull a) { // a % b + (0 or b)
		return a - (ull)((__uint128_t(m) * a) >> 64) * b;
	}
};

FastMod F(2);

int N;
ll M;
ll fact[MAXN], invFact[MAXN];
ll dp[MAXN][3][MAXN], nCk[MAXN][MAXN];

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = F.reduce(r * b);
        b = F.reduce(b * b);
        e /= 2;
    }
    return r;
}

ll calcComb(int a, int b) {
    // debug << "nCk " << a << " " << b << " = " << fact[a] * invFact[b] % M * invFact[a-b] % M << endl;
    return F.reduce(F.reduce(fact[a] * invFact[b]) * invFact[a-b]);
}

void solve() {
    cin >> N >> M;
    // Generate info
    F = FastMod(M);
    fact[0] = 1, invFact[0] = 1;
    rep(i, 1, MAXN) {
        fact[i] = F.reduce(fact[i-1] * i);
        invFact[i] = powmod(fact[i], M-2);
        debug << fact[i] << " " << invFact[i] << '\n';
    }
    rep(i, 0, MAXN) {
        rep(j, 0, i+1) {
            nCk[i][j] = calcComb(i, j);
            debug << "nCk " << i << " " << j << " = " << nCk[i][j] << "\n";
        }
    }

    int states = 0, goodStates = 0, trans = 0, goodTrans = 0;
    rep(j, 0, 3) dp[0][j][0] = 1;
    dp[1][0][1] = 1, dp[1][1][1] = 1, dp[1][2][0] = 1;
    rep(i, 2, N+1) {
        rep(j, 0, 3) {
            if (i != N && j == 0) continue;
            int lowSteps = i/2, highSteps = i;
            rep(k, lowSteps, highSteps+1) {
                states++;
                // For each middle location
                rep(tempL, 0, i) {
                    // For each split steps
                    int l = tempL;
                    int r = i-1-l;
                    // if (l > r) break;
                    // rep(s, l/2, l+1) {
                    rep(s, 0, k) {
                        if (k-1-s < 0) break;
                        trans++;
                        debug << "trans " << l << " " << r << " " << s << " " << k-1-s << endl;
                        ll val;
                        if (j == 0) {
                            val = F.reduce(dp[l][1][s] * dp[r][1][k-1-s]);
                        } else if (j == 1) {
                            val = F.reduce(dp[l][1][s] * dp[r][2][k-1-s]);
                        } else {
                            val = F.reduce(dp[l][2][s] * dp[r][2][k-1-s]);
                        }
                        val = F.reduce(val * nCk[k-1][s]);
                        // if (l < r) {
                        //     // Symmetry
                        //     val *= 2;
                        // }
                        if (val != 0) goodTrans++;
                        dp[i][j][k] += val;
                    }
                }
                F.reduce(dp[i][j][k]);
                debug << "dp[" << i << "][" << j << "][" << k << "] = " << dp[i][j][k] << endl;
                if (dp[i][j][k] != 0) goodStates++;
            }
        }
    }

    ll ans = 0;
    rep(k, 0, N+1) ans = (ans + dp[N][0][k]) % M;
    cout << ans << '\n';
    cout << states << " " << goodStates << " " << trans << " " << goodTrans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}