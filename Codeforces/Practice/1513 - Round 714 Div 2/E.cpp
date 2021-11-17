#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;
const ll MOD = 1e9+7;

ll fact[MAXN], invFact[MAXN];

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r*b % MOD;
        b = b*b % MOD;
        e >>= 1;
    }
    return r;
}

ll nCk(int n, int k) {
    assert(n >= 0 && k >= 0 && n >= k);
    return fact[n] * invFact[k] % MOD * invFact[n-k] % MOD;
}

int N;
ll S;
int A[MAXN];
int numSources, numSinks;
map<int, int> sources, sinks, nums;

void solve() {
    cin >> N;
    // Gen factorials
    fact[0] = 1, invFact[0] = 1;
    rep(i, 1, N+1) {
        fact[i] = fact[i-1] * i % MOD;
        invFact[i] = powmod(fact[i], MOD-2);
    }

    S = 0;
    rep(i, 0, N) {
        cin >> A[i];
        S += A[i];
        nums[A[i]]++;
    }
    if (S % N != 0) {
        cout << "0\n";
        return;
    }
    S /= N;
    rep(i, 0, N) {
        if (A[i] > S) {
            numSources++;
            sources[A[i]]++;
        } else if (A[i] < S) {
            numSinks++;
            sinks[A[i]]++;
        }
    }

    ll ans;
    if (numSources <= 1 || numSinks <= 1) {
        // All permutations work
        ans = fact[N];
        for (auto& p : nums) ans = ans * invFact[p.second] % MOD;
    } else {
        // Split into 2 groups
        ans = 0;
        rep(i, numSources-1, N) {
            if (N-1-i < numSinks) continue;
            ll ways = nCk(i, numSources-1) * nCk(N-1-i, numSinks) % MOD;
            // Symmetry
            ways = ways * 2 % MOD;
            ans = (ans + ways) % MOD;
        }
        // Create permutations
        ans = ans * fact[numSources] % MOD;
        for (auto& p : sources) ans = ans * invFact[p.second] % MOD;
        ans = ans * fact[numSinks] % MOD;
        for (auto& p : sinks) ans = ans * invFact[p.second] % MOD;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}