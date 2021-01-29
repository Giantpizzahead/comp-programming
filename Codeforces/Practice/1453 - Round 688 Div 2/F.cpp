#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 3001, INF = 1e9;

int N;
int A[MAXN];
int dp[MAXN][MAXN];
multiset<int> currRemove;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N+1) {
        rep(j, 0, N+1) {
            dp[i][j] = INF;
        }
    }
    dp[N-1][N] = 0;
    for (int i = N-2; i >= 0; i--) {
        // Propagate mins
        for (int j = N-1; j >= 0; j--) {
            dp[i+1][j] = min(dp[i+1][j+1], dp[i+1][j]);
        }
        currRemove.clear();
        for (int j = i+1; j < N; j++) {
            if (j > i+A[i]) continue;  // Cannot reach
            dp[i][j] = dp[j][i+A[i]+1] + currRemove.size();
            // Update currRemove
            currRemove.erase(j);
            // Add current to minRemove
            if (A[j] != 0) currRemove.insert(j+A[j]);
        }
    }
    int answer = INF;
    rep(j, 1, N+1) answer = min(dp[0][j], answer);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}