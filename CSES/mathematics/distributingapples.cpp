#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const ll MOD = 1e9+7;

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e % 2) r = r*b%MOD;
        e /= 2;
        b = b*b%MOD;
    }
    return r;
}

ll moddiv(ll a, ll b) {
    return a * powmod(b, MOD-2) % MOD;
}

ll fact(ll a) {
    ll r = 1;
    rep(i, 1, a+1) r = r * i % MOD;
    return r;
}

ll nCk(ll n, ll k) {
    return moddiv(moddiv(fact(n), fact(n-k)), fact(k));
}

int N, M;

void solve() {
    cin >> N >> M;
    cout << nCk(N+M-1, N-1) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}