#include <iostream>

using namespace std;
using ll = long long;

const int MAXN = 100005;
const ll MOD = 1e9+7;

int N, M;
// dp[i][j] = # of ways to create one line of i cells with last 2 cells = j
ll dp[MAXN][4];
ll answer;

int main() {
    dp[0][0b11] = 1;
    dp[0][0b00] = 1;
    for (int i = 1; i < MAXN; i++) {
        dp[i][0b00] = (dp[i-1][0b10]) % MOD;
        dp[i][0b01] = (dp[i-1][0b10] + dp[i-1][0b00]) % MOD;
        dp[i][0b10] = (dp[i-1][0b01] + dp[i-1][0b11]) % MOD;
        dp[i][0b11] = (dp[i-1][0b01]) % MOD;
    }
    cin >> N >> M;
    // Repeating columns
    answer = dp[N][0b00] + dp[N][0b01] + dp[N][0b10] + dp[N][0b11];
    // Repeating rows
    answer += dp[M][0b00] + dp[M][0b01] + dp[M][0b10] + dp[M][0b11];
    // Symmetrical in both ways
    answer -= 2;
    if (answer < 0) answer += MOD;
    answer %= MOD;
    cout << answer << '\n';
    return 0;
}