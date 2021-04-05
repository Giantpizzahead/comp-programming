#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int N = 20, D = 10;

string numA, numB;
// dp[i][j][k] = Numbers with first i digits filled, last digit = j, definitely lower (1) or not (0) = k
ll dp[N+1][D][2];

ll solve(string S) {
    dp[0][0][0] = 1, dp[0][0][1] = 0;
    rep(i, 1, sz(S)) {
        rep(j, 0, D) {
            dp[i][j][0] = 0, dp[i][j][1] = 0;
            if (S[i] - '0' > j) {
                // Definitely safe
                rep(k, 0, D) {
                    if (k == j) continue;
                    dp[i][j][1] += dp[i-1][k][0] + dp[i-1][k][1];
                }
            } else if (S[i] - '0' == j) {
                // Maybe
                rep(k, 0, D) {
                    if (k == j) continue;
                    dp[i][j][0] += dp[i-1][k][0];
                    dp[i][j][1] += dp[i-1][k][1];
                }
            } else {
                // Only if already def
                rep(k, 0, D) {
                    if (k == j) continue;
                    dp[i][j][1] += dp[i-1][k][1];
                }
            }
        }
    }
    ll ans = 0;
    if (sz(S) == 2) ans++;  // Count 0
    rep(j, 0, D) {
        ans += dp[sz(S)-1][j][0];
        ans += dp[sz(S)-1][j][1];
    }
    // cout << "solve" << S << " = " << ans << endl;
    return ans;
}

void solve() {
    ll temp;
    cin >> temp >> numB;
    temp--;
    numA = to_string(temp);
    ll ans = solve(' ' + numB);
    string str9 = "";
    rep(i, 1, sz(numB)) {
        str9 += '9';
        ans += solve(' ' + str9);
    }
    if (temp != -1) {
        ans -= solve(' ' + numA);
        str9 = "";
        rep(i, 1, sz(numA)) {
            str9 += '9';
            ans -= solve(' ' + str9);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}