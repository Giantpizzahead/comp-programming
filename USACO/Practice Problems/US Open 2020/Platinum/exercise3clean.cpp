/**
 * Exercise: Subtask 4
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

typedef unsigned long long ll;
typedef __uint128_t L;
struct FastMod {
    ll b, m;
    FastMod(ll b) : b(b), m(ll((L(1) << 64) / b)) {}
    ll reduce(ll a) {
        ll q = (ll)((L(m) * a) >> 64);
        ll r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod F(2);

int add(int a, int b) {
    return F.reduce(a+b);
}

int sub(int a, int b) {
    return F.reduce(a-b);
}

ll mul(ll a, ll b) {
    return F.reduce(a*b);
}

ll powmod(ll b, ll e, ll m) {
    ll r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % m;
        b = b * b % m;
        e /= 2;
    }
    return r;
}

const int MAXN = 7503;

int N, M;
int fact[MAXN], nPk[MAXN][MAXN];

// dp[i] = # of ways to get at least 1 cycle that divides p
int dp[MAXN];
ll solvePrime(int p) {
    rep(i, 0, N+1) dp[i] = 0;
    rep(i, p, N+1) {
        rep(j, 1, i+1) {
            if (j % p == 0) {
                // This cycle length works
                dp[i] = add(mul(fact[i-j], nPk[i-1][j-1]), dp[i]);
            } else {
                // Can extend if already has cycle length
                dp[i] = add(mul(dp[i-j], nPk[i-1][j-1]), dp[i]);
            }
        }
    }
    return dp[N];
}

void solve() {
    fact[0] = 1;
    rep(i, 1, N+1) fact[i] = mul(fact[i-1], i);
    rep(i, 0, N+1) {
        nPk[i][0] = 1;
        rep(j, 1, i+1) {
            nPk[i][j] = mul(nPk[i][j-1], i-j+1);
        }
    }
    bool prime[MAXN];
    rep(i, 2, N+1) prime[i] = true;
    ll answer = 1;
    rep(i, 2, N+1) {
        if (prime[i]) {
            for (int j = i+i; j <= N; j += i) prime[j] = false;
            // Evaluate for each prime power
            for (int j = i; j <= N; j *= i) {
                int res = solvePrime(j);
                // cerr << j << ": " << res << endl;
                answer = answer * powmod(i, res, M) % M;
            }
        }
    }
    cout << answer << '\n';
}

int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    cin >> N >> M;
    F = FastMod(M-1);
    solve();
    fclose(stdin);
    fclose(stdout);
    return 0;
}