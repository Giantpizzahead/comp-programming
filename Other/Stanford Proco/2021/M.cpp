#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 5005;

int N, K;
ll W, S;
ll T[MAXN];
ll preCost[MAXN];

ll dp[MAXN][MAXN];

ll sumFrom1(ll x) {
    return x * (x+1) / 2;
}

ll sumFrom(ll a, ll b) {
    return sumFrom1(b) - sumFrom1(a-1);
}

ll overcost(int x) {
    ll leftN = x/2, rightN = (x-1)/2;
    ll over = leftN * (leftN+1) / 2;
    over += rightN * (rightN+1) / 2;
    return over;
}

void solve() {
    cin >> N >> K >> W >> S;
    ll leftN = K/2, rightN = (K-1)/2;
    ll over = sumFrom1(leftN);
    over += sumFrom1(rightN);
    W -= over * S;
    rep(i, 0, N) cin >> T[i];

    preCost[0] = 0;
    rep(j, 1, K) {
        preCost[j] = preCost[j-1] + min(j, K-j) * S;
    }

    rep(i, 0, N+1) {
        rep(j, 0, K) {
            dp[i][j] = 1e18;
        }
    }

    dp[0][0] = 0;
    rep(i, 0, N) {
        rep(j, 0, K) {
            ll swapCost = min(j, K-j) * S;
            // Don't sprinkle next plant
            dp[i+1][j] = min(dp[i][j] + swapCost + T[i], dp[i+1][j]);
            // Sprinkle next plant
            if (j == K-1) {
                rep(k, 0, K) {
                    ll overCost = (k == 0 ? 0 : preCost[k-1]);
                    dp[i+1][k] = min(dp[i][j] + swapCost + W + overCost, dp[i+1][k]);
                }
            } else {
                dp[i+1][j+1] = min(dp[i][j] + swapCost, dp[i+1][j+1]);
            }
        }
    }

    // rep(i, 0, N+1) {
    //     rep(j, 0, K) {
    //         cout << dp[i][j] << " \n"[j==K-1];
    //     }
    // }
    cout << dp[N][0] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}