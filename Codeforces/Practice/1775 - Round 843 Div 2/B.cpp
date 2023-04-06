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
    vector<vector<int>> bits(N);
    vector<bool> cleared(N);
    map<int, int> bitCnt;
    rep(i, 0, N) {
        int k; cin >> k;
        rep(j, 0, k) {
            int p; cin >> p;
            bits[i].push_back(p);
            bitCnt[p]++;
        }
    }
    rep(i, 0, N) {
        bool works = true;
        for (int b : bits[i]) if (bitCnt[b] == 1) works = false;
        if (works) {
            cout << "Yes\n";
            return;
        }
    }
    cout << "No\n";
}

int main() {
    bool multipleTests = true;
    return runTests(multipleTests);
}
