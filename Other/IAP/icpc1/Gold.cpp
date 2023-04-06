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
const int MAXQ = 12, MAXNUM = 97;

vector<int> primes;
vector<vector<int>> queryLists(MAXQ);
vector<__uint128_t> queryVals(MAXQ, 1);
vector<bool> isComp(MAXP);

void setup() {
    // Gen primes
    rep(i, 2, MAXP) {
        if (isComp[i]) continue;
        primes.push_back(i);
        for (int j = i; j < MAXP; j += i) isComp[j] = true;
    }

    // Gen queries
    for (int i = MAXNUM-1; i >= 0; i--) {
        // Find the query to fit this in with the smallest amount left over
        int bestJ = -1;
        __uint128_t bestV = 0;
        rep(j, 0, MAXQ) {
            if (queryVals[j] * primes[i] <= 1e18) {
                if (queryVals[j] > bestV) {
                    bestJ = j;
                    bestV = queryVals[j];
                }
            }
        }
        queryVals[bestJ] *= primes[i];
        queryLists[bestJ].push_back(primes[i]);
    }

    dumpVars(queryLists);
}

void solve() {
    // Spend the first 12 queries figuring out all the prime factors
    vector<int> foundPrimes;
    rep(i, 0, MAXQ) {
        debug("querying primes " << queryLists[i]);
        cout << "? " << (ll) queryVals[i] << "\n";
        ll res; cin >> res;
        for (int p : queryLists[i]) if (res % p == 0) foundPrimes.push_back(p);
    }
    // Spend the final (up to 10) queries figuring out the count of each factor
    vector<int> foundCounts(sz(foundPrimes));
    rep(i, 0, sz(foundPrimes)) {
        __uint128_t currQ = 1;
        while (currQ * foundPrimes[i] <= 1e18) currQ *= foundPrimes[i];
        debug("querying count of " << foundPrimes[i]);
        cout << "? " << (ll) currQ << "\n";
        ll res; cin >> res;
        while (res % foundPrimes[i] == 0) {
            res /= foundPrimes[i];
            foundCounts[i]++;
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
