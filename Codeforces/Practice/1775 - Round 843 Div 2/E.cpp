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
    int N; cin >> N;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];
    // Try a simple greedy
    ll numPos = 0, numNeg = 0;
    rep(i, 0, N) {
        if (A[i] > 0) {
            if (A[i] > numNeg) {
                // Must add more subseqs
                numNeg = A[i];
            }
            numNeg -= A[i], numPos += A[i];
        } else if (A[i] < 0) {
            if (-A[i] > numPos) {
                // Must add more subseqs
                numPos = -A[i];
            }
            numPos -= (-A[i]), numNeg += (-A[i]);
        }
    }
    cout << numPos + numNeg << "\n";
}

int main() {
    bool multipleTests = true;
    return runTests(multipleTests);
}
