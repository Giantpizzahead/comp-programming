#include <iostream>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;

ll x1, y1, x2, y2, x3, y3;

void solve() {
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    ll ccw = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);
    if (ccw == 0) cout << "TOUCH\n";
    else if (ccw > 0) cout << "LEFT\n";
    else cout << "RIGHT\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}