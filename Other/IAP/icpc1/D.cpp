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
    const ll MOD = 998244353;
    ll N, M, K; int Q;
    cin >> N >> M >> K >> Q;
    struct Query {
        int x, y;
    };
    vector<Query> queries(Q);
    rep(i, 0, Q) {
        cin >> queries[i].x >> queries[i].y;
        queries[i].x--, queries[i].y--;
    }
    reverse(all(queries));

    int numUnique = 0, numXFilled = 0, numYFilled = 0;
    vector<bool> xFilled(N), yFilled(M);
    for (auto& q : queries) {
        if (xFilled[q.x] && yFilled[q.y]) continue;
        if (!xFilled[q.x]) numXFilled++;
        if (!yFilled[q.y]) numYFilled++;
        xFilled[q.x] = true;
        yFilled[q.y] = true;
        numUnique++;
        if (numXFilled == N || numYFilled == M) break;
    }

    ll ans = 1;
    rep(i, 0, numUnique) ans = (ans * K) % MOD;
    cout << ans << '\n';
}

int main() {
    bool multipleTests = true;
    return runTests(multipleTests);
}
