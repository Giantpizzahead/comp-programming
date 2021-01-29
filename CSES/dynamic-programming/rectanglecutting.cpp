#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 501;

int A, B;
int dp[MAXN][MAXN];

void solve() {
    cin >> A >> B;
    for (int i = 1; i <= A; i++) {
        for (int j = 1; j <= B; j++) {
            if (i == j) {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = INT32_MAX;
            // Horizontal cut
            for (int k = 1; k < i; k++) {
                dp[i][j] = min(dp[k][j] + dp[i-k][j] + 1, dp[i][j]);
            }
            // Vertical cut
            for (int k = 1; k < j; k++) {
                dp[i][j] = min(dp[i][k] + dp[i][j-k] + 1, dp[i][j]);
            }
        }
    }
    cout << dp[A][B] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}