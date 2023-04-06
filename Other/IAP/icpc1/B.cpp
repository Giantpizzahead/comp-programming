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
    string S; cin >> S;
    int latest1 = -1, earliest0 = sz(S);
    rep(i, 0, sz(S)) {
        if (S[i] == '0') earliest0 = min(i, earliest0);
        else if (S[i] == '1') latest1 = max(i, latest1);
    }
    if (latest1 == -1 && earliest0 == sz(S)) cout << sz(S) << '\n';
    else if (latest1 == -1) cout << earliest0 + 1 << '\n';
    else if (earliest0 == sz(S)) cout << sz(S) - latest1 << '\n';
    else cout << earliest0 - latest1 + 1 << '\n';
}

int main() {
    bool multipleTests = true;
    return runTests(multipleTests);
}
