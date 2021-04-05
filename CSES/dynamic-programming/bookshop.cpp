#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1000, MAXC = 1e5+1;

int N, X;
int H[MAXN], S[MAXN];
int dp[MAXC];

void solve() {
    cin >> N >> X;
    rep(i, 0, N) cin >> H[i];
    rep(i, 0, N) cin >> S[i];
    rep(i, 0, N) {
        for (int j = X; j >= H[i]; j--) dp[j] = max(dp[j-H[i]] + S[i], dp[j]);
    }
    cout << dp[X] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}