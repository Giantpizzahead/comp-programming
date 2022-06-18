#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

void solve() {
    int Q; cin >> Q;
    rep(i, 0, Q) {
        int N; cin >> N; N /= 2;
        ll ans = 0;
        ll x = N, v = 2;
        while (x > 0) {
            // Place LSB 1 bit here
            ll cnt = (x+1) / 2;
            ans += v*v*v * cnt;
            x /= 2;
            v++;
        }
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}