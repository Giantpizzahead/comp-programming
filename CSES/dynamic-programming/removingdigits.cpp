#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e6+5;

int N;
int dp[MAXN];
bool appears[10];

void solve() {
    cin >> N;
    rep(i, 1, 10) dp[i] = 1;
    rep(x, 10, N+1) {
        int n = x;
        while (n != 0) {
            appears[n%10] = true;
            n /= 10;
        }
        dp[x] = 9999999;
        rep(k, 0, 10) {
            if (appears[k]) dp[x] = min(dp[x-k] + 1, dp[x]);
            appears[k] = false;
        }
        // cout << x << " = " << dp[x] << endl;
    }
    cout << dp[N] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}