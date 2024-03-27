/*
https://www.facebook.com/codingcompetitions/hacker-cup/2014/qualification-round/problems/C

I think this is just math.

P(Tennison wins set i) = P(Sunny in set i) * p_s + (1 - P(Sunny in set i)) * p_r

Given that Tennison has won A sets and lost B sets before:
P(Sunny in set i) = p_i + p_w * p_u - 

Since probabilities are clipped, we need to track them as we go.
There are only 1,000 possible probability values, since all numbers only have 3 decimal points.
Store them as ints instead!

dp[w][l][s] = The chance of Tennison winning the entire match. Current sunny probability is s. Tennison has won w sets and lost l sets.

BC:
dp[K][...K-1][...] = 1
dp[...K-1][K][...] = 0

Trans:
dp[w][l][s] =
Convert s into probability with s/1000.
Sunny with prob s: Win with prob p_s, lose with prob 1-p_s
Rainy with prob 1-s: Win with prob p_r, lose with prob 1-p_r
Win:
    Prob p_w:   dp[w+1][l][s + p_u clipped to be within 0,1]
    Prob 1-p_w: dp[w+1][l][s]
Lose:
    Prob p_l:   dp[w][l+1][s - p_d clipped to be within 0,1]
    Prob 1-p_l: dp[w][l+1][s]

Answer: dp[0][0][p_i]

Runtime: O(100^2 * 1000) states = O(10^7), which should work.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int QUANTIZE = 1000;

void solve() {
    // K, followed by the probabilities ps, pr, pi, pu, pw, pd, pl 
    int K; cin >> K;
    double ps, pr, pi, pu, pw, pd, pl;
    cin >> ps >> pr >> pi >> pu >> pw >> pd >> pl;
    int quantI = round(pi * QUANTIZE);
    int quantU = round(pu * QUANTIZE);
    int quantD = round(pd * QUANTIZE);

    // Base cases (we never reach dp[K][K][...])
    vector<vector<vector<double>>> dp(K+1, vector<vector<double>>(K+1, vector<double>(QUANTIZE+1)));
    for (int i = 0; i <= K; i++) {
        for (int s = 0; s <= QUANTIZE; s++) {
            dp[K][i][s] = 1;
            dp[i][K][s] = 0;
        }
    }

    // Trans
    for (int w = K-1; w >= 0; w--) {
        for (int l = K-1; l >= 0; l--) {
            for (int quantS = 0; quantS <= QUANTIZE; quantS++) {
                // GPT 4 didn't work :/
                double s = quantS / (double) QUANTIZE; // Convert s into probability
                double winProb = s * ps + (1-s) * pr;
                double loseProb = 1 - winProb;

                // Update sun probability with a win
                dp[w][l][quantS] = 0;
                dp[w][l][quantS] += winProb * pw * dp[w+1][l][min(quantS+quantU, QUANTIZE)];
                dp[w][l][quantS] += winProb * (1-pw) * dp[w+1][l][quantS];

                // Update sun probability with a loss
                dp[w][l][quantS] += loseProb * pl * dp[w][l+1][max(quantS-quantD, 0)];
                dp[w][l][quantS] += loseProb * (1-pl) * dp[w][l+1][quantS];

                // cerr << "dp[" << w << "][" << l << "][" << s << "] = " << dp[w][l][quantS] << endl;
            }
        }
    }

    cout << fixed << setprecision(6) << dp[0][0][quantI] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("tennison_input.txt", "r", stdin);
    freopen("test.out", "w", stdout);
    int T; cin >> T;
    rep(i, 1, T+1) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
