// Runtime: O(2^K * K^2)

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

const int MAXP = 20;
const int INF = 1e9;
vector<int> pow2(MAXP);
vector<bool> A;

vector<int> bestXOR(int K, int L, bool targetMin) {
    debug("bestXOR: ");
    dumpVars(K, L, targetMin);
    // Base case
    if (K == 0) {
        debug("bestXOR base\n");
        if (A[L]) return {0};
        else if (targetMin) return {INF};
        else return {-INF};
    }
    vector<int> ans(pow2[K], targetMin ? INF : -INF);

    // Split by MSB of A
    // Combine across different MSBs
    vector<int> resZero = bestXOR(K-1, L, targetMin);
    vector<int> resOne = bestXOR(K-1, L+pow2[K-1], targetMin);

    rep(i, 0, pow2[K-1]) {
        int a = resZero[i], b = resOne[i] + pow2[K-1];
        if (targetMin) ans[i] = min(a, b);
        else ans[i] = max(a, b);
    }
    rep(i, 0, pow2[K-1]) {
        int a = resOne[i], b = resZero[i] + pow2[K-1];
        if (targetMin) ans[i+pow2[K-1]] = min(a, b);
        else ans[i+pow2[K-1]] = max(a, b);
    }
    debug("bestXOR: ");
    dumpVars(ans);
    return ans;
}

vector<int> subtract(vector<int> a, vector<int> b) {
    vector<int> c(sz(a));
    rep(i, 0, sz(a)) c[i] = a[i] - b[i];
    return c;
}

vector<int> solve(int K, int L) {
    debug("solve: ");
    dumpVars(K, L);
    // Base case
    if (K == 0) {
        debug("solve base\n");
        vector<int> ans = {INF};
        return ans;
    }
    vector<int> ans(pow2[K], INF);

    // Split by MSB of A
    vector<int> recZero = solve(K-1, L);
    vector<int> recOne = solve(K-1, L+pow2[K-1]);

    // Propagate results
    rep(i, 0, pow2[K-1]) {
        int curr = min(recZero[i], recOne[i]);
        ans[i] = min(curr, ans[i]);
        ans[i+pow2[K-1]] = min(curr, ans[i+pow2[K-1]]);
    }
    // Combine across different MSBs
    vector<int> xorZero = subtract(bestXOR(K-1, L+pow2[K-1], true), bestXOR(K-1, L, false));
    vector<int> xorOne = subtract(bestXOR(K-1, L, true), bestXOR(K-1, L+pow2[K-1], false));
    rep(i, 0, pow2[K-1]) {
        ans[i] = min(xorZero[i] + pow2[K-1], ans[i]);
        ans[i+pow2[K-1]] = min(xorOne[i] + pow2[K-1], ans[i+pow2[K-1]]);
    }
    debug("solve: ");
    dumpVars(ans);
    return ans;
}

void solve() {
    int N, K; cin >> N >> K;
    A = vector<bool>(pow2[K]);
    rep(i, 0, N) {
        int x; cin >> x;
        A[x] = true;
    }
    vector<int> ans = solve(K, 0);
    rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i==sz(ans)-1];
}

int main() {
    bool multipleTests = false;
    pow2[0] = 1;
    rep(i, 1, MAXP) pow2[i] = pow2[i-1] * 2;
    return runTests(multipleTests);
}
