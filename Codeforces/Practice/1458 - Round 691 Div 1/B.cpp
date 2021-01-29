#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define per(i, a, b) for (int i = (b-1); i >= (a); i--)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 101;

int N, bSum;
double answers[MAXN];
int A[MAXN], B[MAXN];
int dp[MAXN][MAXN*MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i] >> B[i];
    rep(i, 0, N) bSum += B[i];

    rep(i, 0, N+1) {
        rep(j, 0, 100*N+1) dp[i][j] = -1;
    }
    dp[0][0] = 0;

    rep(g, 0, N) {
        per(i, 0, g+2) {
            rep(j, 0, 100*i+1) {
                // Use this glass
                int nj = j-(A[g]-B[g]);
                if (i != 0 && nj >= 0 && dp[i-1][nj] != -1) {
                    // cout << "trans " << nj << " " << j << endl;
                    dp[i][j] = max(dp[i-1][nj] + B[g], dp[i][j]);
                }
                // Update answer
                if (dp[i][j] != -1) answers[i] = max(dp[i][j] / 2.0 + min(j + dp[i][j] / 2.0, bSum / 2.0), answers[i]);
            }
        }
    }

    cout << setprecision(12) << fixed;
    rep(i, 1, N+1) {
        if (i != 1) cout << ' ';
        cout << answers[i];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}                                                                                                                   