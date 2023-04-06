/*
JOI 2022 Problem 3

Solution: DP.

Sort the states by increasing B[i].
Let dp[i][k][p] =
Minimum time required to get k votes and p people together (1 + # of collabs),
using only states 1 to i (one indexed).

Base case: dp[0][0][1] = 0

Assuming A and B are stored using zero indexing.
Transitions:
dp[i][k][p] = C
Get a collaborator: dp[i+1][k+1][p+1] = C + B[i] / p
Get a vote only: dp[i+1][k+1][p] = C + A[i] / p
Skip: dp[i+1][k][p] = C
To save memory, compress the first dimension.

Runtime: O(N^3 / 4)
Memory: O(N^2)

Notes:
Collaborators should be gotten first in the order (greedy to maximize total hours).
AKA given a solution with a fixed set (0, 1, 2) where 0=None, 1=Vote, 2=Collab:
The states with smallest B_i should be talked to first to get collabs.
In fact, all people should talk in the same place, since the total time wouldn't change
and this could only be beneficial.

Total time = Sum of the below
B_1 + B_2 / 2 + B_3 / 3 + ... for type 2
(A_1 + A_2 + ...) / (# of people)
Where the total number of states = K.

Say the # of people we want at the end is fixed. Then go for the states with smallest B_i
to satisfy that requirement, then smallest A_i for the vote requirement.
I think this is a valid greedy solution.

Say we have (1, 100), (90, 105)
105.5 would be the non-greedy...
So no, it's not a valid greedy. Perhaps DP is more applicable here...
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct State {
    int a, b;
};

void tryTrans(double& a, double b) {
    a = min(a, b);
}

void solve() {
    int N; cin >> N;
    int K; cin >> K;
    vector<State> S(N);
    rep(i, 0, N) {
        cin >> S[i].a >> S[i].b;
    }
    sort(all(S), [](const State& s1, const State& s2) {
        int b1 = (s1.b == -1 ? 10000 : s1.b);
        int b2 = (s2.b == -1 ? 10000 : s2.b);
        return b1 < b2;
    });
    // rep(i, 0, N) cout << S[i].a << ' ' << S[i].b << '\n';

    // DP
    double INF = 1e17;
    vector<vector<vector<double>>> dp(2, vector<vector<double>>(N+1, vector<double>(N+2, INF)));
    int cr = 0, nr = 1;
    dp[cr][0][1] = 0;
    rep(i, 0, N) {
        // Fill next row with infinity first
        // rep(k, 0, i+2) rep(p, 1, i+3) dp[nr][k][p] = INF;
        // Main transitions
        rep(k, 0, i+1) {
            rep(p, 1, i+2) {
                double C = dp[cr][k][p];
                if (C >= INF) continue;
                // cout << "dp[" << i << "][" << k << "][" << p << "] = " << C << endl;
                // Get a collaborator
                if (S[i].b != -1) tryTrans(dp[nr][k+1][p+1], C + (double) S[i].b / p);
                // Get a vote only
                tryTrans(dp[nr][k+1][p], C + (double) S[i].a / p);
                // Skip
                tryTrans(dp[nr][k][p], C);
            }
        }
        // Swap rows
        cr = 1-cr, nr = 1-nr;
    }

    // Calculate answer
    double answer = INF;
    rep(p, 1, N+2) answer = min(dp[cr][K][p], answer);
    cout << fixed << setprecision(6) << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}