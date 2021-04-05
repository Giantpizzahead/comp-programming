#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const ll MOD = 1e9+7;

int N;

ll powmod(ll b, ll e, ll m) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = r * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return r;
}

void solve() {
    cin >> N;
    ll a, b, c;
    rep(i, 0, N) {
        cin >> a >> b >> c;
        cout << powmod(a, powmod(b, c, MOD-1), MOD) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}