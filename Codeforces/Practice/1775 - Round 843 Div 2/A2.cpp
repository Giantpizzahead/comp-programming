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
    if (S[1] == 'a' || S[0] == 'b') cout << S[0] << " " << S[1] << " " << S.substr(2) << "\n";
    else cout << S[0] << " " << S.substr(1, sz(S)-2) << " " << S[sz(S)-1] << "\n";
}

int main() {
    bool multipleTests = true;
    return runTests(multipleTests);
}
