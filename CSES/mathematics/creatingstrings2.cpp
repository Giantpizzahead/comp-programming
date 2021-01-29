#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e6+5;
const ll MOD = 1e9+7;

int N;
string S;
int cnt[256];
ll fact[MAXN], invFact[MAXN];

ll powmod(ll b, ll e) {
    ll r = 1;
    for (; e > 0; e /= 2) {
        if (e & 1) r = r * b % MOD;
        b = b * b % MOD;
    }
    return r;
}

void solve() {
    cin >> S;
    N = sz(S);
    fact[0] = 1;
    invFact[0] = 1;
    rep(i, 1, N+1) {
        fact[i] = fact[i-1] * i % MOD;
        invFact[i] = powmod(fact[i], MOD-2);
    }
    for (char c : S) cnt[c]++;
    ll answer = fact[N];
    rep(i, 0, 256) {
        answer = answer * invFact[cnt[i]] % MOD;
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}