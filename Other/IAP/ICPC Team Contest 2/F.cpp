#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

int X, Y;

map<int, int> seen;

void solve() {
    cin >> X >> Y;
    X = X % Y;
    for (int i = 0;; i++) {
        if (X == 0) {
            cout << i << " " << 0 << endl;
            break;
        }
        if (seen.count(X)) {
            cout << seen[X] << " " << i - seen[X] << endl;
            break;
        }
        seen[X] = i;
        X = (X * 10) % Y;
    }
    seen.clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
