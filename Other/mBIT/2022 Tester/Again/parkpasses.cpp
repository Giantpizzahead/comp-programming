/*
https://codeforces.com/gym/383128/problem/G

Solution:
dp[j] = Min amount spent to have j tickets for the last j days
Process packages in descending order of E
For each package:
if (j >= M-T_i) dp[j+T_i] = min(dp[j] + C_i, dp[j+T_i])
Runtime: O(NM)
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

const int MAXM = 1005;
const ll INF = 1e18+7;

int N, M;
struct Package {
    int t, e, c;
    bool operator<(const Package& o) const {
        return e > o.e;
    }
};
vector<Package> P;

ll dp[MAXM];

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        int t, e, c;
        cin >> t >> e >> c;
        P.push_back({t, e, c});
    }
    sort(all(P));
    rep(i, 1, M+1) dp[i] = INF;
    dp[0] = 0;
    for (Package& p : P) {
        for (int i = M; i >= M-p.e; i--) {
            int ni = min(i+p.t, M);
            dp[ni] = min(dp[i] + p.c, dp[ni]);
        }
    }
    cout << (dp[M] == INF ? -1 : dp[M]) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}