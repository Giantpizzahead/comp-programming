#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e6+5;
const int INF = 1e9;

int solve(int N, bool first = false) {
    if (N == 0) return 0;
    else if (N == 1) return -INF;
    int ans = 1;
    for (int d = 2; d*d <= N; d++) {
        if (N % d != 0) continue;
        if (d != 2 || !first) {
            ans = max(solve(N/d - 1) + 1, ans);
        }
        int e = N/d;
        if (e != 2 || !first) {
            ans = max(solve(N/e - 1) + 1, ans);
        }
    }
    return ans;
}

void solve() {
    int N;
    cin >> N;
    cout << solve(N, true) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}