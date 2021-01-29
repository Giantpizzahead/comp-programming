#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

const int MAXN = 1e5+1, MOD = 1e9+7;

int N;
// Number ways possible using chars 0...i, first char in prev split = j, first char in curr split = k, last char = l
int dp[MAXN][4][4][4];
bool allowed[MAXN][4];
string str;

inline void plusMod(int& a, int b) {
    a = (a+b) % MOD;
}

void solve() {
    cin >> str;
    N = str.size();
    rep(i, 0, N) {
        if (str[i] == '?') rep(j, 0, 4) allowed[i][j] = true;
        if (str[i] == 'A') allowed[i][0] = true;
        if (str[i] == 'C') allowed[i][1] = true;
        if (str[i] == 'G') allowed[i][2] = true;
        if (str[i] == 'T') allowed[i][3] = true;
    }
    rep(i, 0, 4) {
        rep(j, 0, 4) {
            if (allowed[0][j]) dp[0][i][j][j] = 1;
        }
    }
    rep(i, 1, N) {
        rep(j, 0, 4) {
            rep(k, 0, 4) {
                rep(l, 0, 4) {
                    if (!allowed[i][l]) continue;
                    // Don't split
                    rep(m, 0, 4) {
                        if (l != m) plusMod(dp[i][j][k][l], dp[i-1][j][k][m]);
                    }
                    // Split
                    if (k == l) {
                        rep(m, 0, 4) plusMod(dp[i][j][k][l], dp[i-1][m][j][m]);
                    }
                }
            }
        }
    }
    int answer = 0;
    rep(j, 0, 4) {
        rep(k, 0, 4) {
            plusMod(answer, dp[N-1][j][k][j]);
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}