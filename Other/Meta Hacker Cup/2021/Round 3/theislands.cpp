/*
Solution:
dp[i][j] = Min path distance, path 1 is on island i, path 2 is on island j
BC: dp[0][0] = 0
Trans (forward DP):
dp[i][j], let k = max(i, j)+1, so it's the next unused island
dp[i][j] + dist(i, k) -> dp[k][j]
dp[i][j] + dist(j, k) -> dp[i][k]
(If special island rules forbid the above, don't do it)

plz do not do backward DP for this problem PLEASE

Runtime: O(N^2)
Memory: O(N^2)
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const double INF = 1e9;

int N, B1, B2;
vector<vector<double>> dp;
vector<int> X, Y;

inline double dist(int a, int b) {
    return hypot(X[a] - X[b], Y[a] - Y[b]);
}

void solve() {
    cin >> N >> B1 >> B2;
    X.resize(N);
    Y.resize(N);
    rep(i, 0, N) {
        cin >> X[i] >> Y[i];
    }

    // Do DP
    dp.resize(N, vector<double>(N, INF));
    dp[0][0] = 0;
    rep(i, 0, N-1) {
        rep(j, 0, N-1) {
            int k = max(i, j)+1;
            if (k == N-1) {
                // Final island, both must come here
                dp[k][k] = min(dp[i][j] + dist(i, k) + dist(j, k), dp[k][k]);
            } else {
                // Normal trans
                if (k != B1) dp[k][j] = min(dp[i][j] + dist(i, k), dp[k][j]);
                if (k != B2) dp[i][k] = min(dp[i][j] + dist(j, k), dp[i][k]);
            }
        }
    }
    cout << fixed << setprecision(2) << dp[N-1][N-1] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}