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
    vector<int> digits(N);
    rep(i, 0, N) cin >> digits[i];
    rep(i, 0, N) {
        int moves; cin >> moves;
        rep(j, 0, moves) {
            char c; cin >> c;
            if (c == 'U') digits[i]--;
            else digits[i]++;
        }
        digits[i] %= 10;
        if (digits[i] < 0) digits[i] += 10;
    }
    rep(i, 0, N) cout << digits[i] << " \n"[i==N-1];
}

int main() {
    bool multipleTests = true;
    return runTests(multipleTests);
}
