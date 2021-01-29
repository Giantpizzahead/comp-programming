#include <bits/stdc++.h>
#define ll long long
#define vi vector<int>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

const int MAXN = 1e6+1;
const ll MOD = 1e9+7;

int N;
ll fact[MAXN], invFact[MAXN];

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % MOD;
        b = b * b % MOD;
        e /= 2;
    }
    return r;
}

ll nCk(int n, int k) {
    return fact[n] * invFact[n-k] % MOD * invFact[k] % MOD;
}

void solve() {
    fact[0] = 1;
    invFact[0] = 1;
    rep(i, 1, MAXN) {
        fact[i] = fact[i-1] * i % MOD;
        invFact[i] = powmod(fact[i], MOD-2);
    }
    cin >> N;
    rep(i, 0, N) {
        int a, b;
        cin >> a >> b;
        cout << nCk(a, b) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}