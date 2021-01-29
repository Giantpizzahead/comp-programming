#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N;

void solve() {
    cin >> N;
    cout << 9;
    if (N > 1) cout << 8;
    int d = 9;
    rep(i, 2, N) {
        cout << d;
        d = (d+1)%10;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}