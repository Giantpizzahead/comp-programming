#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int R, N;
int X[MAXN], Y[MAXN], T[MAXN];
int dp[MAXN];

void solve() {
    cin >> R >> N;
    X[0] = 1, Y[0] = 1, T[0] = 0;
    rep(i, 1, N+1) {
        cin >> T[i] >> X[i] >> Y[i];
    }
    dp[0] = 0;
    int bestNum = -1e9;
    rep(i, 1, N+1) {
        dp[i] = -1e9;
        rep(j, max(i-1000, 0), i) {
            int dist = abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
            // cout << dist << " " << T[i] - T[j] << endl;
            if (dist <= T[i] - T[j]) dp[i] = max(dp[j]+1, dp[i]);
        }
        dp[i] = max(bestNum+1, dp[i]);
        if (i-1000 >= 0) bestNum = max(dp[i-1000], bestNum);
    }
    int ans = 0;
    rep(i, 0, N+1) ans = max(dp[i], ans);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}