#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 401;

int N;
ll M;
ll dp[MAXN][MAXN][MAXN];

void solve() {
    cin >> N >> M;
    dp[2][0][1] = 1;
    dp[2][1][0] = 1;
    rep(x, 3, N+1) {
        rep(j, 0, x) {
            rep(k, 0, x) {
                if (j == k) continue;
                rep(i, 0, x) {
                    if (i == j || i == k) continue;
                    if (j > i+1 && j > k+1) continue;
                    int oldJ = i;
                    if (i > k) oldJ--;
                    int oldK = j;
                    if (j > k) oldK--;
                    dp[x][j][k] = (dp[x][j][k] + dp[x-1][oldJ][oldK]) % M;
                }
                cout << "dp " << x << " " << j << " " << k << " = " << dp[x][j][k] << "\n";
            }
        }
    }
    ll ans = 0;
    rep(j, 0, N) rep(k, 0, N) ans = (ans + dp[N][j][k]) % M;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}