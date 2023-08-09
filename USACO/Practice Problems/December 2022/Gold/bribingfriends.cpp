/*
http://usaco.org/index.php?page=viewproblem2&cpid=1257

Solution:
Sort cows in order of increasing X. Then when doing knapsack, we should always use up ice cream cones before moonies.
So, the DP becomes a standard-ish knapsack problem. The runtime is O(N*(A+B)).
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int getMaxPopularity(int N, int A, int B, vector<int>& P, vector<int>& C, vector<int>& X) {
    int INF = 1e9;
    vector<vector<int>> dp(N+1, vector<int>(A+B+1, -INF));
    dp[0][A+B] = 0;

    int answer = 0;
    for (int i = 0; i <= N; i++) {
        for (int j = A+B; j >= 0; j--) {
            answer = max(dp[i][j], answer);
            if (i == N || dp[i][j] == -INF) continue;
            // cerr << i << " " << j << " = " << dp[i][j] << endl;

            // Skip cow i
            dp[i+1][j] = max(dp[i][j], dp[i+1][j]);

            // Use cow i
            int aLeft = (j <= A ? j : A);
            int bLeft = (j <= A ? 0 : j-A);
            int nj;
            if (bLeft > 0) {
                // Try bribing
                int maxBribe = bLeft / X[i];
                if (maxBribe < C[i]) {
                    // Cannot fully bribe, must also pay from A
                    nj = A - (C[i]-maxBribe);
                } else {
                    // Fully bribed
                    nj = j - C[i] * X[i];
                }
            } else nj = aLeft - C[i];
            // If this works, try it
            if (nj >= 0) dp[i+1][nj] = max(dp[i][j] + P[i], dp[i+1][nj]);
        }
    }

    return answer;
}

void solve() {
    int N, A, B;
    cin >> N >> A >> B;
    struct Cow {
        int p, c, x;
        bool operator<(const Cow& o) const {
            return x < o.x;
        }
    };
    vector<Cow> cows(N);
    for (int i = 0; i < N; i++) {
        cin >> cows[i].p >> cows[i].c >> cows[i].x;
    }
    // Sort cows in order of increasing X
    sort(cows.begin(), cows.end());

    // Generate vectors for function
    vector<int> P(N), C(N), X(N);
    for (int i = 0; i < N; i++) P[i] = cows[i].p, C[i] = cows[i].c, X[i] = cows[i].x;
    cout << getMaxPopularity(N, A, B, P, C, X) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
