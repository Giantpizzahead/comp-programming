#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 100, MAXX = 100001;

int N;
int X[MAXN];
bool dp[MAXX];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> X[i];
    dp[0] = true;
    rep(i, 0, N) {
        for (int j = MAXX-1; j >= X[i]; j--) {
            dp[j] |= dp[j-X[i]];
        }
    }
    int cnt = 0;
    rep(i, 1, MAXX) if (dp[i]) cnt++;
    cout << cnt << '\n';
    bool first = true;
    rep(i, 1, MAXX) {
        if (dp[i]) {
            if (!first) cout << ' ';
            else first = false;
            cout << i;
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}