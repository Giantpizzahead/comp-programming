#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

int L, R, A;

int f(int x) {
    return x / A + x % A;
}

void solve() {
    cin >> L >> R >> A;
    int mod0 = R / A * A;
    int ans = f(R);
    if (mod0-1 >= L) ans = max(f(mod0-1), f(R));
    if (mod0+A-1 <= R) ans = max(f(mod0+A-1), f(R));
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}