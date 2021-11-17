#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 262144, MAXV = 60;

int N;
int A[MAXN];
int dp[MAXV][MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i];
        A[i]--;
    }
    int ans = 0;
    rep(i, 0, MAXV) {
        rep(j, 0, N) {
            // Is it possible to form value i starting from index j?
            if (A[j] == i) {
                // Already the right value
                dp[i][j] = j;
                ans = max(i, ans);
            } else if (i != 0 && dp[i-1][j] != -1 && dp[i-1][j] != N-1 && dp[i-1][dp[i-1][j]+1] != -1) {
                // Combine two smaller values
                dp[i][j] = dp[i-1][dp[i-1][j]+1];
                ans = max(i, ans);
            } else {
                // Not possible
                dp[i][j] = -1;
            }
            debug << dp[i][j] << " \n"[j==N-1];
        }
    }
    cout << ans + 1 << '\n';
}

int main() {
    freopen("262144.in", "r", stdin);
    freopen("262144.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}