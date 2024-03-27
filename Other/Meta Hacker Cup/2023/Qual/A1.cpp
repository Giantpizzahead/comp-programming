/*
Solution: Greedy.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

void solve() {
    int S, D, K;
    cin >> S >> D >> K;
    int b = 2 * (S + D);
    int p = S + 2 * D;
    if (b >= K+1 && p >= K) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
