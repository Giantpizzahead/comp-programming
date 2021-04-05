#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 18, MOD = 1e9+7;

int N, M;
int dp[1 << MAXN][MAXN];
vi adj[MAXN], startE, endE;

void solve() {
    cin >> N >> M;
    if (N == 2) {
        // Special case
        int ans = 0, a, b;
        rep(i, 0, M) {
            cin >> a >> b;
            if (a == 1 && b == 2) ans++;
        }
        cout << ans << '\n';
        return;
    }
    int a, b;
    rep(i, 0, M) {
        cin >> a >> b;
        a--, b--;
        if (a == b) continue;
        if (a == 0 && b != N-1) startE.push_back(b-1);
        if (b == N-1 && a != 0) endE.push_back(a-1);
        if (a != 0 && b != 0 && a != N-1 && b != N-1) adj[a-1].push_back(b-1);
    }

    N -= 2;
    for (int n : startE) dp[1 << n][n]++;
    rep(i, 1, 1 << N) {
        rep(n, 0, N) {
            if (!(i & (1 << n))) continue;
            for (int e : adj[n]) {
                if (i & (1 << e)) continue;
                int j = i | (1 << e);
                dp[j][e] += dp[i][n];
                if (dp[j][e] >= MOD) dp[j][e] -= MOD;
            }
        }
    }

    int ans = 0;
    for (int n : endE) {
        ans += dp[(1<<N)-1][n];
        if (ans >= MOD) ans %= MOD;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}