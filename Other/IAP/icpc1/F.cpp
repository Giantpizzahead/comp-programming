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

struct Pair {
    int x, y;
    friend ostream& operator<<(ostream& os, const Pair& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};
vector<Pair> P;

void genPow2(int start, int len) {
    for (int curr = 1; curr < len; curr *= 2) {
        for (int i = start; i < start+len; i += curr*2) {
            rep(j, 0, curr) P.push_back({i+j, i+curr+j});
        }
    }
    // dumpVars(P);
}

void solve() {
    int N; cin >> N;
    int maxPow2 = 1;
    while (maxPow2*2 <= N) maxPow2 *= 2;
    genPow2(0, maxPow2);
    genPow2(N-maxPow2, maxPow2);
    cout << sz(P) << '\n';
    for (auto& p : P) cout << p.x+1 << ' ' << p.y+1 << '\n';
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
