#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const ll MOD = 1e9+7;
const int MAXN = 1e5+5;

ll powmod(ll b, ll e, ll m) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = r*b%m;
        b = b*b%m;
        e >>= 1;
    }
    return r;
}

ll modinv(ll x, ll m) {
    return powmod(x, m-2, m);
}

ll geoSum(ll r, ll k) {
    ll result = powmod(r, k+1, MOD) - 1;
    result = result * modinv(r-1, MOD) % MOD;
    if (result < 0) result += MOD;
    return result;
}

int N;
int X[MAXN], K[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> X[i] >> K[i];
    }
    // Number of divisors
    ll numDivisors = 1;
    rep(i, 0, N) numDivisors = numDivisors * (K[i]+1) % MOD;
    // Sum of divisors
    ll sumDivisors = 1;
    rep(i, 0, N) {
        sumDivisors = sumDivisors * geoSum(X[i], K[i]) % MOD;
    }
    // Product of divisors
    bool perfectSquare = true;
    ll num = 1, halfNumDivs = 1;
    rep(i, 0, N) {
        num = num * powmod(X[i], K[i], MOD) % MOD;
        int currK = K[i];
        if (currK % 2 == 1 && perfectSquare) {
            perfectSquare = false;
            currK /= 2;
        }
        halfNumDivs = halfNumDivs * (currK+1) % (MOD-1);
    }
    if (perfectSquare) {
        // Recalc num as sqrt(num)
        num = 1;
        rep(i, 0, N) {
            num = num * powmod(X[i], K[i]/2, MOD) % MOD;
        }
    }
    ll prodDivisors = powmod(num, halfNumDivs, MOD);

    cout << numDivisors << " " << sumDivisors << " " << prodDivisors << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}