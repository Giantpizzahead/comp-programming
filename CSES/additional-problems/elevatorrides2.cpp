#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 20;

int N, X;
int W[MAXN];
pair<int, int> dp[1 << MAXN];

void solve() {
    cin >> N >> X;
    rep(i, 0, N) cin >> W[i];
    rep(mask, 1, 1 << N) {
        dp[mask].first = 1e9;
        rep(j, 0, N) {
            if ((mask & (1 << j)) == 0) continue;
            int oldMask = mask ^ (1 << j);
            int nc, nw;
            if (dp[oldMask].second + W[j] > X) {
                nc = dp[oldMask].first + 1;
                nw = W[j];
            } else {
                nc = dp[oldMask].first;
                nw = dp[oldMask].second + W[j];
            }
            if (make_pair(nc, nw) < dp[mask]) {
                dp[mask].first = nc;
                dp[mask].second = nw;
            }
        }
    }
    cout << dp[(1 << N)-1].first + 1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}