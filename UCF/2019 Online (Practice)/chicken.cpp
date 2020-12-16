#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N, D;
double P;
double dp[MAXN];

void solve() {
    cin >> N >> D >> P;
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        // Don't get pickles
        dp[i] = dp[i-1] * (1-P);
        // Get pickles
        dp[i] += (dp[max(0, i-D)] + 2) * P;
    }
    cout << dp[N] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    cout << fixed << setprecision(18);
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}