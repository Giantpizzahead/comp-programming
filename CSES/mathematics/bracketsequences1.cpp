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
    for (; e > 0; e >>= 1) {
        if (e & 1) r = r*b%MOD;
        b = b*b%MOD;
    }
    return r;
}

ll moddiv(ll a, ll b) {
    return a * powmod(b, MOD-2) % MOD;
}

ll fact(int a) {
    ll r = 1;
    rep(i, 1, a+1) r = r*i%MOD;
    return r;
}

ll nCk(int n, int k) {
    return moddiv(fact(n), fact(n-k) * fact(k) % MOD);
}

int N;

void solve() {
    cin >> N;
    if (N % 2 == 1) cout << "0\n";
    else cout << moddiv(nCk(N, N/2), N/2+1) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}