#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;
using namespace std;

const int MAXN = 1e5+5;

int N;
int A[MAXN];

unordered_map<int, int> dp[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    sort(A, A+N);
    rep(i, 1, 4) dp[0][i] = 0;
    rep(i, 0, N) {
        for (auto& p : dp[i]) {
            int nextI = A[i] + p.first;
            auto ptr = lower_bound(A, A+N, nextI);
            if (ptr == A+N || *ptr != nextI) continue;
            rep(j, -2, 3) {
                if (j == 0) continue;
                int ni = ptr-A;
                int nk = p.first + j;
                if (nk <= 0) continue;
                if (dp[ni].count(nk)) dp[ni][nk] = min(dp[ni][nk], p.second+1);
                else dp[ni][nk] = p.second+1;
            }
        }
    }
    if (dp[N-1].empty()) cout << -1 << '\n';
    else {
        int ans = 999999999;
        for (auto& p : dp[N-1]) ans = min(p.second, ans);
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}