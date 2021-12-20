#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

ll X, Y;

void solve() {
    cin >> X >> Y;
    if (X == Y) {
        cout << X << '\n';
        return;
    } else if (X > Y) {
        ll N = Y + X;
        cout << N << '\n';
        return;
    } else {
        ll N = Y;
        ll m1 = N % X;
        ll m2 = 0;
        // As N decreases, m1--, m2++
        // They will meet at some point before m2 loops
        N -= (m1-m2) / 2;
        cout << N << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}