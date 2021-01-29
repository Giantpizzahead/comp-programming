#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 205;
using ll = long long;

int R, G, B;
int r[MAXN], g[MAXN], b[MAXN];
ll dp[MAXN][MAXN][MAXN];

void solve() {
    cin >> R >> G >> B;
    for (int i = 0; i < R; i++) cin >> r[i];
    for (int i = 0; i < G; i++) cin >> g[i];
    for (int i = 0; i < B; i++) cin >> b[i];
    sort(r, r+R);
    sort(g, g+G);
    sort(b, b+B);

    ll answer = 0;
    for (int i = R; i >= 0; i--) {
        for (int j = G; j >= 0; j--) {
            for (int k = B; k >= 0; k--) {
                ll best = 0;
                if (i != R && j != G) {
                    best = max(dp[i+1][j+1][k] + r[i] * g[j], best);
                }
                if (i != R && k != B) {
                    best = max(dp[i+1][j][k+1] + r[i] * b[k], best);
                }
                if (j != G && k != B) {
                    best = max(dp[i][j+1][k+1] + g[j] * b[k], best);
                }
                dp[i][j][k] = best;
                answer = max(best, answer);
            }
        }
    }

    cout << answer << endl;
}

int main() {
    solve();
    return 0;
}