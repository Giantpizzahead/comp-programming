#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1005;
const int MOD = 1e9+7;

int N;
bool grid[MAXN][MAXN];
int dp[MAXN][MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        string S; cin >> S;
        rep(j, 0, N) grid[i][j] = (S[j] == '.');
    }

    dp[0][0] = grid[0][0];
    rep(i, 0, N) {
        rep(j, 0, N) {
            if (!grid[i][j]) continue;
            if (i != 0) dp[i][j] += dp[i-1][j];
            if (j != 0) dp[i][j] += dp[i][j-1];
            dp[i][j] %= MOD;
        }
    }
    cout << dp[N-1][N-1] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}