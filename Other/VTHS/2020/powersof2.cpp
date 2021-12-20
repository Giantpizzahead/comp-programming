#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 65;

ll N, answer;
ll pow2;
string P, S;
// dp[digits][lps match][is max number];
int E;
ll dp[MAXN][MAXN][2];
int lps[MAXN];

void doDP() {
    dp[0][0][1] = 1;
    for (int i = 0; i < S.size(); i++) {
        for (int j = 0; j <= P.size(); j++) {
            for (int m = 0; m < 2; m++) {
                // Transition to next KMP
                for (int k = 0; k <= 9; k++) {
                    char c = '0' + k;
                    if (m == 1 && S[i] < c) continue;  // Too big
                    int isMax = m;
                    if (isMax == 1 && c < S[i]) isMax = 0;
                    // Use this digit
                    if (j != P.size()) {
                        int kmp = j-1;
                        while (kmp != -1 && c != P[kmp+1]) kmp = lps[kmp];
                        if (c == P[kmp+1]) kmp++;
                        if (kmp == P.size()-1) {
                            // Done
                            dp[i+1][P.size()][isMax] += dp[i][j][m];
                        } else {
                            // Continuing to match
                            dp[i+1][kmp+1][isMax] += dp[i][j][m];
                        }
                    } else {
                        // Already has substring
                        dp[i+1][P.size()][isMax] += dp[i][j][m];
                    }
                }
            }
        }
    }
    // for (int i = 0; i <= S.size(); i++) {
    //     for (int j = 0; j <= P.size(); j++) {
    //         cout << dp[i][j][0] << ' ';
    //     }
    //     cout << endl;
    // }
    answer += dp[S.size()][P.size()][1] + dp[S.size()][P.size()][0];
}

void solve() {
    cin >> N >> E;
    pow2 = (ll) pow(2, E);
    P = to_string(pow2);
    S = to_string(N);
    // LPS array
    lps[0] = -1;
    int currLPS = -1;
    for (int i = 1; i < P.size(); i++) {
        while (currLPS != -1 && P[i] != P[currLPS+1]) currLPS = lps[currLPS];
        if (P[i] == P[currLPS+1]) currLPS++;
        lps[i] = currLPS;
        // cout << lps[i] << ' ';
    }
    // cout << endl;
    // cout << P << endl;
    doDP();
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}