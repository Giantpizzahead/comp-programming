/**
 * Exercise: Full solution
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

int M;

int add(int a, int b) {
    int c = a+b;
    if (c >= M-1) c -= (M-1);
    return c;
}

int sub(int a, int b) {
    int c = a-b;
    if (c < 0) c += (M-1);
    return c;
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

int N;
int fact[MAXN], nCk[MAXN][MAXN];

// wall[i] = # of ways to get length i*p where all cycles divide p
// wno[i] = # of ways to get length N-i*p where no cycles that divide p
int wall[MAXN], wno[MAXN];
ll solvePrime(int p) {
    wall[0] = 1;
    for (int i = 1; i*p <= N; i++) {
        wall[i] = 0;
        for (int j = 1; j <= i; j++) {
            // Add cycle of length j*p
            wall[i] = add(wall[i], mul(wall[i-j], mul(nCk[i*p-1][j*p-1], fact[j*p-1])));
        }
    }
    for (int i = N/p; i >= 0; i--) {
        // # of cows is actually N-i*p
        wno[i] = fact[N-i*p];
        for (int j = 1; j <= N/p-i; j++) {
            // Subtract all permutations with j*p cows in a divisible by p cycle
            wno[i] = sub(wno[i], mul(wno[i+j], mul(nCk[N-i*p][j*p], wall[j])));
        }
    }
    // rep(i, 0, N/p+1) cerr << wall[i] << ' ';
    // cerr << endl;
    // rep(i, 0, N/p+1) cerr << wno[i] << ' ';
    // cerr << endl;
    ll result = 0;
    for (int i = 1; i*p <= N; i++) {
        result = add(result, mul(nCk[N][i*p], mul(wall[i], wno[i])));
    }
    return result;
}

void solve() {
    fact[0] = 1;
    rep(i, 1, N+1) fact[i] = mul(fact[i-1], i);
    rep(i, 0, N+1) {
        nCk[i][0] = 1;
        rep(j, 1, i+1) {
            nCk[i][j] = add(nCk[i-1][j], nCk[i-1][j-1]);
            // cerr << nCk[i][j] << ' ';
        }
        // cerr << endl;
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