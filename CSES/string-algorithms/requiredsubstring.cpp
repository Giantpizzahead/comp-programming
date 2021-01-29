#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1001, MAXM = 101, MOD = 1e9+7;

int N, M;
string str;
int lps[MAXM];
int dp[MAXN][MAXM];

void solve() {
    cin >> N >> str;
    M = str.size();
    lps[0] = -1;
    int currLPS = -1;
    rep(i, 1, M) {
        while (currLPS != -1 && str[i] != str[currLPS+1]) currLPS = lps[currLPS];
        if (str[i] == str[currLPS+1]) currLPS++;
        lps[i] = currLPS;
    }

    dp[0][0] = 1;
    rep(i, 0, N) {
        rep(j, 0, M+1) {
            if (j == M) {
                // Any character works
                dp[i+1][j] = (dp[i+1][j] + (ll) dp[i][j] * 26) % MOD;
            } else {
                // Try all characters
                rep(c, 'A', 'Z'+1) {
                    currLPS = j-1;
                    while (currLPS != -1 && c != str[currLPS+1]) currLPS = lps[currLPS];
                    if (c == str[currLPS+1]) currLPS++;
                    int nj = currLPS+1;
                    dp[i+1][nj] = (dp[i+1][nj] + dp[i][j]) % MOD;
                }
            }
        }
    }

    cout << dp[N][M] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}