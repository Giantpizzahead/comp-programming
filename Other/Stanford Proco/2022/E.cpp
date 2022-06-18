#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;
using namespace std;

const int MAXN = 54;

int N, M, P;
__int128_t dp[MAXN][MAXN];
bool hole[MAXN][MAXN];

void solve() {
    cin >> N >> M >> P;
    N++, M++;
    rep(n, 0, P) {
        int i, j;
        cin >> i >> j;
        hole[i][j] = true;
    }
    dp[0][0] = 1;
    rep(i, 0, N) {
        rep(j, 0, M) {
            if (hole[i][j]) continue;
            dp[i+1][j] += dp[i][j];
            dp[i][j+1] += dp[i][j];
        }
    }
    __int128_t x = dp[N-1][M-1];
    vector<int> vals;
    if (x == 0) vals.push_back(0);
    while (x > 0) {
        vals.push_back(x % 10);
        x /= 10;
    }
    reverse(all(vals));
    for (int n : vals) cout << n;
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}