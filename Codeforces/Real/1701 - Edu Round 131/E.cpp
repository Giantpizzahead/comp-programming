#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 5005;
const int INF = 1e9;

int N, M;
// dp[i][j][k] = Min moves required to move cursor to right after index i in S, with a length j prefix of T
// k = State of the cursor
// One indexed
int dp[MAXN][MAXN][3];
string S, T;

void trans(int& a, int b) {
    a = min(b, a);
}

void solve() {
    cin >> N >> M;
    cin >> S >> T;
    S = " " + S;
    T = " " + T;
    rep(i, 0, N+1) rep(j, 0, M+1) rep(k, 0, 3) dp[i][j][k] = INF;
    dp[0][0][0] = 0;
    dp[0][0][1] = 0;
    dp[0][0][2] = 0;
    rep(i, 0, N+1) {
        rep(j, 0, M+1) {
            rep(k, 0, 3) {
                if (dp[i][j][k] == INF) continue;
                if (k == 0) {
                    // Delete the next letter
                    if (i != N) trans(dp[i+1][j][k], dp[i][j][k] + 2);
                    // Use the next letter
                    if (i != N && j != M && S[i+1] == T[j+1]) trans(dp[i+1][j+1][k], dp[i][j][k] + 1);
                    // Use jump
                    trans(dp[i][j][1], dp[i][j][k] + 1);
                } else if (k == 1) {
                    // Use the next letter
                    if (i != N && j != M && S[i+1] == T[j+1]) trans(dp[i+1][j+1][k], dp[i][j][k]);
                    // Use jump
                    trans(dp[i][j][2], dp[i][j][k]);
                } else {
                    // Moves by 1 no matter what
                    if (i != N) trans(dp[i+1][j][k], dp[i][j][k] + 1);
                    if (i != N && j != M && S[i+1] == T[j+1]) trans(dp[i+1][j+1][k], dp[i][j][k] + 1);
                }
                // cout << "dp[" << i << "][" << j << "][" << k << "] = " << dp[i][j][k] << "\n";
            }
        }
    }
    int ans = dp[N][M][2];
    cout << (ans == INF ? -1 : ans) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}