#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N, K;

void solve() {
    cin >> N >> K;
    int ans = 0;
    rep(i, 0, N) {
        int x; cin >> x;
        ans ^= x;
    }
    cout << (ans == 0 ? "Second" : "First") << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}