/*
Solution:
Iterate in decreasing order of value to get groups of elements that need to come together. Then, do subset sum to determine if we can make two arrays of length N following these groups.
T(i) = Last group included to create array of size i.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 1005;

int N;
int C[2*MAXN];
bool used[2*MAXN];
vector<pair<int, int>> groups;

int dp[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, 2*N) cin >> C[i];
    // Gen groups
    for (int k = 2*N; k >= 1; k--) {
        rep(i, 0, 2*N) {
            if (C[i] != k || used[i]) continue;
            // Found the element
            int numIn = 0;
            rep(j, i, 2*N) {
                if (used[j]) break;
                used[j] = true, numIn++;
            }
            groups.push_back({i, numIn});
            break;
        }
    }

    // 0-1 subset sum on groups
    rep(i, 0, N+1) dp[i] = -1;
    dp[0] = 2*N;
    rep(j, 0, sz(groups)) {
        for (int i = N; i >= 0; i--) {
            if (dp[i] != -1) continue;
            if (i-groups[j].second >= 0 && dp[i-groups[j].second] != -1) {
                // This group works
                dp[i] = j;
            }
        }
    }
    // cout << "dp: ";
    // rep(i, 0, N+1) cout << dp[i] << " \n"[i==N];

    // Construct array
    if (dp[N] == -1) cout << "-1\n";
    else {
        vector<int> ans;
        for (int i = N; i > 0; i -= groups[dp[i]].second) {
            rep(j, 0, groups[dp[i]].second) {
                ans.push_back(C[groups[dp[i]].first + j]);
            }
        }
        rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i==sz(ans)-1];

        vector<int> ans2;
        rep(i, 0, 2*N) if (find(all(ans), C[i]) == ans.end()) ans2.push_back(C[i]);
        rep(i, 0, sz(ans2)) cout << ans2[i] << " \n"[i==sz(ans2)-1];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
