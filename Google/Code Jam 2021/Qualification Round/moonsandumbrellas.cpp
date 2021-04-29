#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005, INF = 1e9;

int N, X, Y;
string S;
// C, J
int dp[MAXN][2];

void setmin(int& a, int b) {
    a = min(a, b);
}

void solve() {
    cin >> X >> Y >> S;
    N = S.size();
    if (N == 1) {
        cout << 0 << '\n';
        return;
    }
    for (int i = 0; i < N; i++) {
        dp[i][0] = INF;
        dp[i][1] = INF;
    }
    if (S[0] != 'J' && S[1] != 'J') setmin(dp[1][0], 0);
    if (S[0] != 'J' && S[1] != 'C') setmin(dp[1][1], X);
    if (S[0] != 'C' && S[1] != 'J') setmin(dp[1][0], Y);
    if (S[0] != 'C' && S[1] != 'C') setmin(dp[1][1], 0);
    for (int i = 2; i < N; i++) {
        if (S[i] != 'J') {
            // Last letter C
            setmin(dp[i][0], dp[i-1][0]);
            setmin(dp[i][0], dp[i-1][1]+Y);
        }
        if (S[i] != 'C') {
            // Last letter J
            setmin(dp[i][1], dp[i-1][1]);
            setmin(dp[i][1], dp[i-1][0]+X);
        }
    }
    int ans = min(dp[N-1][0], dp[N-1][1]);
    cout << ans << '\n';
}

int main() {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
}