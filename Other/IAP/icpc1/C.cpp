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
    vector<int> A(N), B(N), dMin(N), dMax(N);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) cin >> B[i];
    int bi = 0;
    rep(ai, 0, N) {
        while (B[bi] < A[ai]) bi++;
        dMin[ai] = B[bi] - A[ai];
    }
    bi = N-1;
    for (int ai = N-1; ai >= 0; ai--) {
        dMax[ai] = B[bi] - A[ai];
        if (ai != 0 && B[ai-1] < A[ai]) bi = ai-1;
    }
    rep(i, 0, N) cout << dMin[i] << " \n"[i==N-1];
    rep(i, 0, N) cout << dMax[i] << " \n"[i==N-1];
}

int main() {
    bool multipleTests = true;
    return runTests(multipleTests);
}
