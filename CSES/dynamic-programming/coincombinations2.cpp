#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100, MAXX = 1e6+1, MOD = 1e9+7;

int N, X;
int C[MAXN];
int dp[MAXX];

void solve() {
    cin >> N >> X;
    for (int i = 0; i < N; i++) cin >> C[i];
    dp[0] = 1;
    for (int i = 0; i < N; i++) {
        for (int j = C[i]; j <= X; j++) {
            dp[j] = (dp[j] + dp[j-C[i]]) % MOD;
        }
    }
    cout << dp[X] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}