#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;
 
const int MAXN = 2e6+5;
const ll MOD = 1e9+7;
 
ll fact[MAXN], invFact[MAXN];
 
ll powmod(ll b, ll e) {
    ll r = 1;
    for (; e > 0; e >>= 1) {
        if (e & 1) r = r * b % MOD;
        b = b * b % MOD;
    }
    return r;
}
 
ll nCk(int n, int k) {
    return fact[n] * invFact[n-k] % MOD * invFact[k] % MOD;
}
 
int N, M;
struct Trap {
    int x, y;
    ll v;
};
vector<Trap> traps;
 
void solve() {
    cin >> N >> M;
    fact[0] = 1;
    rep(i, 1, 2*N+1) fact[i] = fact[i-1] * i % MOD;
    invFact[2*N] = powmod(fact[2*N], MOD-2);
    for (int i = 2*N-1; i >= 0; i--) invFact[i] = invFact[i+1] * (i+1) % MOD;
 
    traps.push_back({1, 1, MOD-1});
    traps.push_back({N, N, 0});
    int x, y;
    rep(i, 0, M) {
        cin >> x >> y;
        traps.push_back({x, y, 0});
    }
    sort(all(traps), [](const Trap& a, const Trap& b) {
        int c1 = a.x + a.y, c2 = b.x + b.y;
        return c1 < c2;
    });
 
    // Counting # of paths with inclusion-exclusion
    rep(i, 0, sz(traps)) {
        // Transition from all previous traps
        rep(j, 0, i) {
            int cx = traps[i].x - traps[j].x, cy = traps[i].y - traps[j].y;
            if (cx < 0 || cy < 0) continue;
            // # of ways to move from trap j to trap i
            ll ways = nCk(cx+cy, cx);
            traps[i].v = (traps[i].v + traps[j].v * -ways) % MOD;
        }
    }
 
    cout << (traps.back().v + MOD) % MOD << '\n';
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}