#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
typedef unsigned long long ll;

const ll MOD = 998244353;
const int MAXN = 2001;

struct FastMod {
	ll b, m;
	FastMod(ll b) : b(b), m(-1ULL / b) {}
	ll reduce(ll a) { // a % b + (0 or b)
		return a - (ll)((__uint128_t(m) * a) >> 64) * b;
	}
};
FastMod F(MOD);

// ll fact[MAXN], invFact[MAXN];
ll nCk[MAXN][MAXN];

// ll powmod(ll b, ll e) {
//     ll r = 1;
//     for (; e > 0; e >>= 1) {
//         if (e & 1) r = r*b % MOD;
//         b = b*b % MOD;
//     }
//     return r;
// }

// inline ll modinv(int x) {
//     return powmod(x, MOD-2);
// }

int N;
int preO[MAXN], preC[MAXN], preQ[MAXN];
ll answer = 0;
string S;

inline int numO(int l, int r) {
    if (l > r) return 0;
    else return preO[r] - (l == 0 ? 0 : preO[l-1]);
}

inline int numC(int l, int r) {
    if (l > r) return 0;
    else return preC[r] - (l == 0 ? 0 : preC[l-1]);
}

inline int numQ(int l, int r) {
    if (l > r) return 0;
    else return preQ[r] - (l == 0 ? 0 : preQ[l-1]);
}

void solve() {
    cin >> S;
    N = sz(S);
    // Gen factorials
    // fact[0] = 1;
    // rep(i, 1, N+1) fact[i] = fact[i-1] * i % MOD;
    // invFact[N] = modinv(fact[N]);
    // for (int i = N-1; i >= 0; i--) invFact[i] = invFact[i+1] * (i+1) % MOD;
    // Gen combinations
    rep(i, 0, N+1) nCk[i][0] = 1;
    rep(i, 1, N+1) {
        rep(j, 1, i+1) {
            nCk[i][j] = nCk[i-1][j] + nCk[i-1][j-1];
            if (nCk[i][j] >= MOD) nCk[i][j] -= MOD;
        }
    }
    // Prefix sums
    rep(i, 0, N) {
        if (i != 0) {
            preO[i] += preO[i-1];
            preC[i] += preC[i-1];
            preQ[i] += preQ[i-1];
        }
        if (S[i] == '(') preO[i]++;
        if (S[i] == ')') preC[i]++;
        if (S[i] == '?') preQ[i]++;
    }
    // Go through all substrings
    int firstOpen, lastClose;
    int leftO, leftQ, rightC, rightQ, stopK;
    ll numWays;
    rep(i, 0, N) {
        firstOpen = N, lastClose = -1;
        rep(j, i+1, N) {
            //      i                                   j
            // ... [(] some closing, then some opening [)] ...
            if (S[i] != ')' && S[j] != '(') {
                numWays = 0;
                leftO = numO(0, i-1), leftQ = numQ(0, i-1), rightC = numC(j+1, N-1), rightQ = numQ(j+1, N-1);
                // k = # of extra pairs of parentheses
                stopK = min(leftO + leftQ, rightC + rightQ) + 1;
                rep(k, max(leftO, rightC), stopK) {
                    numWays += F.reduce(nCk[leftQ][k-leftO] * nCk[rightQ][k-rightC]) * (k+1);
                }
                answer += F.reduce(numWays * (min(j, firstOpen)-max(i, lastClose)));
            }
            // Post update
            if (S[j] == ')') {
                lastClose = j;
                if (firstOpen != N) break;  // No () in middle
            } else if (S[j] == '(' && firstOpen == N) firstOpen = j;
        }
    }
    cout << answer % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}