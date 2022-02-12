/*
Solution: 
Runtime: 
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2e5+5;

int N;
// 0 = Beginning, 1 = Middle, 2 = End
int A[MAXN], dp[MAXN][3];
map<int, vector<int>> locs;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    // Longest contiguous sorted subsequence
    rep(i, 0, N) locs[A[i]].push_back(i);
    for (auto& p : locs) sort(all(p.second));
    int ans = 0;
    rep(i, 0, N) {
        rep(j, 0, 3) {
            if (j == 0) dp[i][j] = max(dp[i][j], 1);
            ans = max(dp[i][j], ans);
            // Forward trans
            auto ptr = upper_bound(all(locs[A[i]]), i);
            if (ptr != locs[A[i]].end()) {
                int ni = *ptr;
                dp[ni][j] = max(dp[i][j]+1, dp[ni][j]);
            }
            // Transition to next value
            auto ptr2 = locs.upper_bound(A[i]);
            if (ptr2 != locs.end()) {
                auto ptr3 = upper_bound(all(ptr2->second), i);
                if (ptr3 != ptr2->second.end()) {
                    int ni = *ptr3;
                    if (j == 0) {
                        // Transition to last value
                        dp[ni][2] = max(dp[i][j]+1, dp[ni][2]);
                        // Can only transition to the beginning
                        if (ptr2->second.begin() == ptr3) dp[ni][1] = max(dp[i][j]+1, dp[ni][1]);
                    } else if (j == 1) {
                        // Must transition from the end
                        if (i != *prev(locs[A[i]].end())) continue;
                        // Transition to last value
                        dp[ni][2] = max(dp[i][j]+1, dp[ni][2]);
                        // Can only transition to the beginning
                        if (ptr2->second.begin() == ptr3) dp[ni][1] = max(dp[i][j]+1, dp[ni][1]);
                    }
                }
            }
        }
    }
    cout << N-ans << '\n';

    // rep(j, 0, 3) rep(i, 0, N) debug << dp[i][j] << " \n"[i==N-1];
    
    locs.clear();
    rep(i, 0, N) rep(j, 0, 3) dp[i][j] = 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}