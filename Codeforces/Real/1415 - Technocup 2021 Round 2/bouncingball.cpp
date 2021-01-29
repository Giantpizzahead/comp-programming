#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;
int N, P, K, X, Y;
ll dp[MAXN];
bool on[MAXN];

void solve() {
    cin >> N >> P >> K;
    string str;
    cin >> str;
    for (int i = 1; i <= N; i++) {
        on[i] = (str[i-1] == '1');
    }
    cin >> X >> Y;

    // Try starting on every shift
    for (int i = 0; i < P; i++) dp[i] = 2e9+7;
    for (int i = P; i <= N; i++) {
        dp[i] = Y * (i-P);
        dp[i] += on[i] ? 0 : X;
    }
    // Go right
    for (int i = K+1; i <= N; i++) {
        dp[i] = min(dp[i-K] + (on[i] ? 0 : X), dp[i]);
    }
    // Answer
    ll answer = 2e9+7;
    for (int i = N; i > N-K; i--) {
        answer = min(dp[i], answer);
    }

    // for (int i = 1; i <= N; i++) cout << dp[i] << ' ';
    // cout << endl;
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
    return 0;
}