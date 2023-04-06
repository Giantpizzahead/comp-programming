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
    ll N, X; cin >> N >> X;
    if (X > N) {
        cout << "-1\n";
        return;
    }
    // Process each bit individually
    ll currN = N, currX = X, pow2 = 1;
    ll minM = N, maxM = 5 * 1e18;
    while (currN > 0 || currX > 0) {
        bool onN = (currN % 2 == 1), onX = (currX % 2 == 1);
        dumpVars(pow2, onN, onX, minM, maxM);
        if (onX && !onN) {
            // Not possible to add new bit
            cout << "-1\n";
            return;
        } else if (onN) {
            // Get min M needed to turn this bit off
            ll turnOff = N + (pow2 - N % pow2);
            if (onX) {
                // This bit must stay on
                maxM = min(turnOff-1, maxM);
            } else {
                // This bit must be removed
                minM = max(turnOff, minM);
            }
        } else {
            // Already off; nothing to do
        }
        currN /= 2;
        currX /= 2;
        pow2 *= 2;
    }
    if (minM > maxM) cout << "-1\n";
    else cout << minM << "\n";
}

int main() {
    bool multipleTests = true;
    return runTests(multipleTests);
}
