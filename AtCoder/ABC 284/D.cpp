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
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (multiple_tests) {
        int T; cin >> T;
        rep(i, 0, T) solve();
    } else solve();
    return 0;
}
// =============================== END TEMPLATE ===============================

void solve() {
    ll N; cin >> N;
    ll p = 2;
    while (true) {
        if (N % p == 0) break;
        p++;
    }
    ll q;
    if (N / p % p == 0) {
        q = N/p/p;
    } else {
        q = p;
        p = round(sqrt(N/p));
    }
    cout << p << " " << q << "\n";
}

int main() {
    bool multipleTests = true;
    return runTests(multipleTests);
}
