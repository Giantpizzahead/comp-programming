/**
 * Solution:
 * Dynamic programming.
 * dp[i][j] = # ways to fill first i characters with cows
 * 
 * Runtime: O(N^2)
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1005;
const int MOD = 2012;

int N;
string S;
int dp[MAXN][MAXN];

void solve() {
    cin >> S;
    N = sz(S);
    S = " " + S;
    dp[0][0] = 1;
    int currParen = 0;
    rep(i, 1, N+1) {
        if (S[i] == '(') {
            currParen++;
            rep(j, 0, N+1) {
                // Set to G
                int currH = currParen - j;
                if (currH >= 0 && j != 0) dp[i][j] += dp[i-1][j-1];
                // Set to H
                if (currH >= 1) dp[i][j] += dp[i-1][j];
                dp[i][j] %= MOD;
            }
        } else {
            currParen--;
            rep(j, 0, N+1) {
                // Set to G
                int currH = currParen - j;
                if (currH >= 0 && j != N) dp[i][j] += dp[i-1][j+1];
                // Set to H
                if (currH >= 0) dp[i][j] += dp[i-1][j];
                dp[i][j] %= MOD;
            }
        }
    }
    if (currParen == 0) cout << dp[N][0] << "\n";
    else cout << "0\n";
}

int main() {
    ios::sync_with_stdio(0);
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);
    solve();
    return 0;
}