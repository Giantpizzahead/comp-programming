#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1001;
const int MOD = 1e9+7;

int N;
ll dp[MAXN][MAXN][2];

inline void plusMod(ll& a, ll b) {
    a = (a+b) % MOD;
}

void solve() {
    cin >> N;
    if (N == 1) {
        cout << "1\n";
        return;
    }

    dp[2][1][1] = 2;
    for (int i = 2; i < N; i++) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < 2; k++) {
                if (k == 0) {
                    // Place next to previous number
                    plusMod(dp[i+1][j+1][1], dp[i][j][k] * 2);
                    // Place in between an adjacent pair
                    if (j != 0) plusMod(dp[i+1][j-1][0], dp[i][j][k] * j);
                    // Place in any other place
                    plusMod(dp[i+1][j][0], dp[i][j][k] * (i-1-j));
                } else {
                    // Place next to previous number, between previous pair
                    plusMod(dp[i+1][j][1], dp[i][j][k]);
                    // Place next to previous number, creating new pair
                    plusMod(dp[i+1][j+1][1], dp[i][j][k]);
                    // Place in between an adjacent pair
                    if (j != 0) plusMod(dp[i+1][j-1][0], dp[i][j][k] * (j-1));
                    // Place in any other place
                    plusMod(dp[i+1][j][0], dp[i][j][k] * (i-j));
                }
                // cout << "dp " << i << " " << j << " " << k << " = " << dp[i][j][k] << endl;
            }
        }
    }

    cout << (dp[N][0][0] + dp[N][0][1]) % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}