#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;
using namespace std;

int N, A, B;

void solve() {
    cin >> N >> A >> B;
    int a = A, b = B;
    int ans1 = 0;
    int bit = 1;
    while (a > 0 || b > 0) {
        if (a % 2 != b % 2) ans1 = max(bit, ans1);
        bit *= 2;
        a /= 2;
        b /= 2;
    }
    a = A ^ N, b = B;
    int ans2 = 0;
    bit = 1;
    while (a > 0 || b > 0) {
        if (a % 2 != b % 2) ans2 = max(bit, ans2);
        bit *= 2;
        a /= 2;
        b /= 2;
    }
    cout << min(ans1, ans2) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}