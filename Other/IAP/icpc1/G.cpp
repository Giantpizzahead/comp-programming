// ============================== BEGIN TEMPLATE ==============================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#ifdef LOCAL
    #include "pprint.hpp"
#else
    #define debug(...) 42
    #define dumpVars(...) 42
#endif

void solve();

int runTests(bool multiple_tests) {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    if (multiple_tests) {
        int T; cin >> T;
        rep(i, 0, T) solve();
    } else solve();
    return 0;
}
// =============================== END TEMPLATE ===============================

// 2*3*5*7*11*13*17*19*23*29
// Number has at most 10 distinct prime factors
const int MAXP = 1000;
const int MAXQ = 22;

vector<int> primes;
vector<bool> isComp(MAXP);

void setup() {
    // Gen primes
    rep(i, 2, MAXP) {
        if (isComp[i]) continue;
        primes.push_back(i);
        for (int j = i; j < MAXP; j += i) isComp[j] = true;
    }
}

void solve() {
    vector<int> foundPrimes, foundCounts;
    int currP = 0, currCnt = 0;
    rep(i, 0, MAXQ) {
        __uint128_t currQ = 1;
        if (sz(foundPrimes) == sz(foundCounts)) {
            // Find more primes
            int nextP = currP;
            while (currQ * primes[nextP] <= 1e18) currQ *= primes[nextP++];
            debug("querying for primes [" << currP << ", " << nextP << ")");
            cout << "? " << (ll) currQ << "\n";
            ll res; cin >> res;
            rep(j, currP, nextP) if (res % primes[j] == 0) foundPrimes.push_back(primes[j]);
            currP = nextP;
        } else {
            // Find count of a prime
            while (currQ * foundPrimes[currCnt] <= 1e18) currQ *= foundPrimes[currCnt];
            debug("querying count of " << foundPrimes[currCnt]);
            cout << "? " << (ll) currQ << "\n";
            ll res; cin >> res;
            int cnt = 0;
            while (res % foundPrimes[currCnt] == 0) {
                res /= foundPrimes[currCnt];
                cnt++;
            }
            currCnt++;
            foundCounts.push_back(cnt);
        }
    }
    dumpVars(foundPrimes, foundCounts);

    // Output answer
    ll ans = 1;
    for (int cnt : foundCounts) ans *= (cnt+1);
    // Account for error
    ans *= 2;
    cout << "! " << ans << "\n";

    // dumpVars(queryLists);
    // rep(i, 0, MAXQ) debug("prime " << i << " = " << (ll) queryVals[i] << "\n");
    // rep(i, 0, 5) dumpVars(primes[MAXNUM+i]);
}

int main() {
    setup();
    bool multipleTests = true;
    return runTests(multipleTests);
}
