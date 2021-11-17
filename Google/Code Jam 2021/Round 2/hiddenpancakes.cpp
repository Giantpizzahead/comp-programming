#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;
const ll MOD = 1e9+7;

int N;
int V[MAXN];
vector<int> L[MAXN];

ll fact[MAXN], invFact[MAXN];

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = r*b % MOD;
        b = b*b % MOD;
        e /= 2;
    }
    return r;
}

ll nCk(int n, int k) {
    assert(n >= 0 && k <= n);
    return fact[n] * invFact[k] % MOD * invFact[n-k] % MOD;
}

ll answer = 1;

void solve(int l, int r, int d) {
    // debug << "solve(" << l << ", " << r << ", " << d << ")" << endl;
    if (l > r) return;

    // Split by lowest
    auto ptr = upper_bound(all(L[d]), r);
    if (ptr == L[d].begin()) {
        // Invalid
        answer = 0;
        return;
    }
    int m = *prev(ptr);
    if (m < l) {
        // Also invalid (outside of range)
        answer = 0;
        return;
    }

    // Choose which pancakes to use on each side
    answer = answer * nCk(r-l, r-m) % MOD;

    solve(l, m-1, d);
    solve(m+1, r, d+1);
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> V[i];
        V[i]--;
        L[V[i]].push_back(i);
    }
    answer = 1;
    solve(0, N-1, 0);
    cout << answer << '\n';
    rep(i, 0, N) L[i].clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fact[0] = 1, invFact[0] = 1;
    rep(i, 1, MAXN) {
        fact[i] = fact[i-1] * i % MOD;
        invFact[i] = powmod(fact[i], MOD-2);
    }
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}