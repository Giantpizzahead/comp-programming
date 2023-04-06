/**
 * Meant to test the template's features.
 */

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
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int fib(int x) {
    if (x < 2) return x;
    else return fib(x-2) + fib(x-1);
}

void solve() {
    debug("basic types\n");

    int a = 5;
    string b = "hello";
    vector<double> c = {2.3, -8.22, 9.3};
    dumpVars(a, b, c);

    vector<vector<int>> adj = {
        {2},
        {1, 3},
        {},
        {0, 1, 2, 3}
    };
    dumpVars(adj);

    array<int, 5> cpp_arr = {-1, 1, 3, 5, 7};
    dumpVars(cpp_arr);

    int c_arr[] = {1, 4, 6, 4, 1};
    debug("c_arr = " << vector<int>(c_arr, c_arr+5) << "\n");
    debug("c_arr compressed = ");
    rep(i, 0, 5) debug(c_arr[i] << " \n"[i==4]);

    unordered_map<int, string> m = {
        {1, "up"}, {2, "right"}, {3, "down"}, {4, "left"}
    };
    dumpVars(m);

    set<ll> s = {2, 8, 15, 39, 39};
    dumpVars(s);

    debug("custom types\n");

    Pair p = {-8, 16};
    dumpVars(p);

    debug("function calls\n");

    rep(i, 1, 6) {
        debug("fib(" << i << ") = " << fib(i) << endl);
    }

    cout << "This is my answer!" << endl;
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
