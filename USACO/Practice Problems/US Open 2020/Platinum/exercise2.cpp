/**
 * Exercise: Subtask 2
 */

#include <iostream>
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

int gcf(int a, int b) {
    if (b == 0) return a;
    return gcf(b, a % b);
}

int lcm(int a, int b) {
    return a / gcf(a, b) * b;
}

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = F.reduce(r * b);
        b = F.reduce(b * b);
        e /= 2;
    }
    return r;
}

const int MAXN = 7501;

int N, M;
ll fact[MAXN], nCk[MAXN][MAXN];
unordered_map<int, ll> dp[MAXN];

void precalc() {
    fact[0] = 1;
    rep(i, 1, N+1) fact[i] = F.reduce(fact[i-1] * i);
    rep(i, 0, N+1) {
        nCk[i][0] = 1;
        nCk[i][i] = 1;
    }
    rep(i, 2, N+1) {
        rep(j, 1, i) {
            nCk[i][j] = F.reduce(nCk[i-1][j] + nCk[i-1][j-1]);
        }
    }
}

void doDP() {
    // Forward DP
    dp[0][1] = 1;
    // # of cows used so far = i
    rep(i, 0, N+1) {
        for (auto p : dp[i]) {
            // Current LCM = j
            // # of ways = v;
            int j = p.first, v = p.second;

            // This cycle contains smallest unassigned cow
            // Cycle length = k
            rep(k, 1, N+1-i) {
                int nj = lcm(j, k);
                // Current ways
                ll trans = v;
                // Choose k-1 more cows to be part of cycle
                trans = F.reduce(trans * nCk[N-i-1][k-1]);
                // Form edges in cycle
                trans = F.reduce(trans * fact[k-1]);
                // Update DP
                dp[i+k][nj] = F.reduce(dp[i+k][nj] + trans);
            }
        }
    }
}

void getAnswer() {
    // Now modding by M
    F = FastMod(M);
    ll answer = 1;
    for (auto p : dp[N]) {
        // cerr << p.first << " " << p.second << endl;
        answer = F.reduce(answer * powmod(p.first, p.second));
    }
    cout << answer << endl;
}

void solve() {
    precalc();
    doDP();
    getAnswer();
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