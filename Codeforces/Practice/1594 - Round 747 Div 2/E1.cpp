/*
Solution: 
Runtime: 
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const ll MOD = 1e9+7;
const int MAXK = 61;

int K;
ll defaultWays[MAXK];

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = r*b % MOD;
        b = b*b % MOD;
        e >>= 1;
    }
    return r;
}

void solve() {
    cin >> K;
    defaultWays[1] = 1;
    rep(i, 2, K+1) {
        defaultWays[i] = (defaultWays[i-1]*2) * (defaultWays[i-1]*2) % MOD;
    }
    ll ans = defaultWays[K] * 3 % MOD;
    ans = ans * powmod(2, (1LL << K) - 1) % MOD;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}