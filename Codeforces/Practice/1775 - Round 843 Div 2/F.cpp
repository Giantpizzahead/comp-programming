/*
Consider an optimal plan for a fixed N. First, figure out the optimal perimeter.
(Smallest A * A or A * (A+1) grid that fits the N)
*/

// ============================== BEGIN TEMPLATE ==============================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#ifdef LOCAL
    #include "pprint.hpp"
#else
    #define debug(...) 42
    #define dumpVars(...) 42
#endif

void genData();
void solve();

int U;
ll M;

int runTests(bool multiple_tests) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (multiple_tests) {
        int T; cin >> T >> U;
        if (U == 2) {
            cin >> M;
            genData();
        }
        rep(i, 0, T) solve();
    } else solve();
    return 0;
}
// =============================== END TEMPLATE ===============================

int squaresToRemove(int N, pair<int, int>& S) {
    int ans = S.first * S.second - N;
    return ans;
}

pair<int, int> findOptimalSize(int N) {
    // A * A grid
    int squareLen = min((int) sqrt(N) - 1, 1);
    while (squareLen * squareLen < N) squareLen++;
    // A * (A+1) grid maybe?
    if (squareLen * (squareLen-1) >= N) return {squareLen, squareLen-1};
    else return {squareLen, squareLen};
}

const int MAXS = 800;
const int K = 4;
/*
dp[s][h] = # of ways to make a corner with current height h with s squares removed
BC:
dp[0][MAXS-1] = 1
Trans:
dp[s][h] -> For each newH in [1, h], add new column
dp[s+newH][newH] += dp[s][h]
*/
array<array<ll, MAXS>, MAXS> cornerWays;
/*
dp[s][n] = # of ways to remove s squares from n corners
BC:
dp[0][0] = 1
Trans:
dp[n][s] -> For each k in [0, MAXS-1], try removing k squares from the nth corner
dp[n+1][s+k] = dp[n][s] * cornerWays[k][0]
*/
array<array<ll, MAXS>, K+1> totalWays;

void genData() {
    // cornerWays
    rep(s, 0, MAXS) cornerWays[s].fill(0);
    cornerWays[0][MAXS-1] = 1;
    rep(s, 0, MAXS) {
        rep(h, 0, MAXS) {
            if (cornerWays[s][h] == 0) continue;
            rep(k, 0, h+1) {
                if (s+k >= MAXS) break;
                cornerWays[s+k][k] += cornerWays[s][h];
                cornerWays[s+k][k] %= M;
            }
        }
    }

    // totalWays
    rep(n, 0, K+1) totalWays[n].fill(0);
    totalWays[0][0] = 1;
    rep(n, 0, K) {
        rep(s, 0, MAXS) {
            if (totalWays[n][s] == 0) continue;
            rep(k, 0, MAXS) {
                if (s+k >= MAXS) break;
                totalWays[n+1][s+k] += totalWays[n][s] * cornerWays[k][0] % M;
                totalWays[n+1][s+k] %= M;
            }
        }
    }

    // dumpVars(cornerWays);
    // dumpVars(totalWays);
}

void solve() {
    int N; cin >> N;
    pair<int, int> S = findOptimalSize(N);
    if (U == 1) {
        // Generate something valid
        int toRemove = squaresToRemove(N, S);
        cout << S.first << " " << S.second << "\n";
        rep(i, 0, S.first) {
            rep(j, 0, S.second) {
                if (i == 0 && j < toRemove) cout << ".";
                else cout << "#";
            }
            cout << "\n";
        }
        return;
    } else {
        if (N == 2) {
            cout << "6 2\n";
            return;
        }
        // Count number of ways
        ll ans = totalWays[4][squaresToRemove(N, S)];
        if (S.first != S.second) ans = ans * 2 % M;
        while (true) {
            S.first++, S.second--;
            int toRemove = squaresToRemove(N, S);
            if (toRemove < 0) break;
            ans += totalWays[4][toRemove] * 2 % M;
            ans %= M;
        }
        cout << S.first * 2 + S.second * 2 << " " << ans << "\n";
    }
}

int main() {
    bool multipleTests = true;
    return runTests(multipleTests);
}
