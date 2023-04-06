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
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];
    int ans = 1e9;
    // Try special configs
    // A _ B
    rep(i, 1, N-1) {
        int curr = min(A[i-1], A[i+1]) + (abs(A[i+1] - A[i-1])+1)/2;
        ans = min(curr, ans);
    }
    // A B
    rep(i, 0, N-1) {
        int a = A[i], b = A[i+1];
        if (a > b) swap(a, b);
        // Hit the stronger wall first
        int curr = min((b-a), (b+1)/2);
        dumpVars(curr, a, b);
        a -= curr;
        b -= 2 * curr;
        // Hit both (maybe)
        if (b <= 0) {
            if (a > 0) curr += (a+1)/2;
        } else {
            assert(a == b);
            curr += (b+2)/3 * 2;
            if (b % 3 == 1) curr--;
        }
        ans = min(curr, ans);
    }
    // Normal (disjoint)
    sort(all(A));
    ans = min((A[0]+1)/2 + (A[1]+1)/2, ans);
    cout << ans << '\n';
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
