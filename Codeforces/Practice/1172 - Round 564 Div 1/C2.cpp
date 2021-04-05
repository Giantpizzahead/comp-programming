#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;

const ll MOD = 998244353;

ll powmod(ll b, ll e) {
    ll r = 1;
    for (; e > 0; e >>= 1) {
        if (e & 1) r = r*b % MOD;
        b = b*b % MOD;
    }
    return r;
}

unordered_map<int, ll> invcache;
inline ll modinv(int x) {
    auto ptr = invcache.find(x);
    if (ptr != invcache.end()) return ptr->second;
    ll res = powmod(x, MOD-2);
    invcache.emplace(x, res);
    return res;
}

inline void plusMod(ll& a, ll& b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

const int MAXN = 2e5+1, MAXM = 3e3+1;

int N, M, zeroSum, oneSum;
ll zeroAdd, oneAdd;
bool A[MAXN];
ll W[MAXN], tempW[MAXN], prob[MAXM][MAXM];

void solve() {
    cin >> N >> M;
    invcache.reserve(3*M);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) {
        cin >> W[i];
        if (A[i]) oneSum += W[i];
        else zeroSum += W[i];
    }
    // prob[i][j] = On (i+1)th visit, j times used to decrease 0 prob
    prob[0][0] = 1;
    rep(i, 0, M) {
        rep(j, 0, i+1) {
            // Calc sums
            int zeroW = zeroSum - j;
            int oneW = oneSum + (i-j);
            // Pick each group
            ll zeroC = zeroW * modinv(zeroW + oneW) % MOD * prob[i][j] % MOD;
            ll oneC = oneW * modinv(zeroW + oneW) % MOD * prob[i][j] % MOD;
            plusMod(zeroAdd, zeroC);
            plusMod(oneAdd, oneC);
            plusMod(prob[i+1][j+1], zeroC);
            plusMod(prob[i+1][j], oneC);
        }
    }
    // Distribute additions
    rep(i, 0, N) {
        if (A[i]) {
            // Take from oneAdd
            ll part = W[i] * modinv(oneSum) % MOD;
            ll contrib = oneAdd * part % MOD;
            plusMod(W[i], contrib);
        } else {
            // Take from zeroAdd
            ll part = W[i] * modinv(zeroSum) % MOD;
            ll contrib = -zeroAdd * part % MOD;
            if (contrib < 0) contrib += MOD;
            plusMod(W[i], contrib);
        }
        cout << W[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}