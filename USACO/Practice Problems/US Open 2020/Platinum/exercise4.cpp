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

// wall[i] = # of ways to get length i where all cycles divide p
// wno[i] = # of ways to get length i where no cycles that divide p
int wall[MAXN], wno[MAXN];
ll solvePrime(int p) {
    wall[0] = 1;
    rep(i, 1, N+1) {
        wall[i] = 0;
        for (int j = p; i-j >= 0; j += p) {
            // Add this length cycle
            wall[i] = add(wall[i], mul(wall[i-j], mul(nCk[i-1][j-1], fact[j-1])));
        }
    }
    rep(i, 0, N+1) {
        wno[i] = fact[i];
        for (int j = p; i-j >= 0; j += p) {
            // Subtract all permutations with this # of cows in a divisible by p cycle
            wno[i] = sub(wno[i], mul(wno[i-j], mul(nCk[i][j], wall[j])));
        }
    }
    // rep(i, 0, N+1) cerr << wall[i] << ' ';
    // cerr << endl;
    // rep(i, 0, N+1) cerr << wno[i] << ' ';
    // cerr << endl;
    return sub(fact[N], wno[N]);
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