#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 2e5+5;
const ll MOD = 998244353;

// b^e under modulo.
ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = (r * b) % MOD;
        e >>= 1;
        b = (b * b) % MOD;
    }
    return r;
}

// a / b under modulo.
ll moddiv(ll a, ll b) {
    return a * powmod(b, MOD-2) % MOD;
}

int N, L0, L1, K;
int A[MAXN];
ll dp[MAXN];

void solve() {
    cin >> N;
    L0 = 0, L1 = 0;
    rep(i, 0, N) {
        cin >> A[i];
        if (A[i] == 0) L0++;
        else L1++;
    }
    // Number out of place
    K = 0;
    rep(i, 0, L0) if (A[i] != 0) K++;

    // Expected values
    dp[0] = 0;
    ll denom = (ll) N * (N-1) / 2 % MOD;
    // cout << "denom = " << denom << endl;
    // cout << "K = " << K << endl;
    rep(i, 1, K+1) {
        ll numer = (ll) i * i % MOD;
        dp[i] = (dp[i-1] + moddiv(denom, numer)) % MOD;
    }
    cout << dp[K] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    // int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
