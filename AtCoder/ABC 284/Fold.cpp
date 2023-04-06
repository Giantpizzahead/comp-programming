/*
bandana

input:    banANADNABdana (T)
reversed: anadBANDANAnab (U)

Search for string U in T, recording longest matching prefix at each index.
Search for string T in U, recording longest matching prefix at each index.
Then, combine this recorded arrays (reversing the one for U).
Iterate through each index to find one where the sum of the longest matches equals N.
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

vector<int> getLCP(string& S) {
    vector<int> lcp(sz(S));
    int currLoc = 0;
    lcp[0] = 0;
    rep(i, 1, sz(S)) {
        while (currLoc != 0 && S[i] != S[currLoc]) {
            currLoc = lcp[currLoc];
        }
        if (S[i] == S[currLoc]) currLoc++;
        lcp[i] = currLoc;
    }
    return lcp;
}

vector<int> getKMP(string& S, string& T) {
    // T is the pattern to search for
    vector<int> lcp = getLCP(T);
    dumpVars(lcp, S, T);
    vector<int> kmp(sz(S));
    int currLoc = 0;
    rep(i, 0, sz(S)) {
        while (currLoc != 0 && (currLoc == sz(T) || S[i] != T[currLoc])) {
            currLoc = lcp[currLoc-1];
        }
        if (S[i] == T[currLoc]) currLoc++;
        kmp[i] = currLoc;
    }
    return kmp;
}

void solve() {
    int N; cin >> N;
    string T; cin >> T;
    string revT = T;
    reverse(all(revT));
    vector<int> kmp1 = getKMP(T, revT);
    vector<int> kmp2 = getKMP(revT, T);
    reverse(all(kmp2));
    dumpVars(T, revT);
    dumpVars(kmp1);
    dumpVars(kmp2);
    rep(i, 0, 2*N) {
        if (kmp1[2*N-1] + kmp2[i] >= N) {
            int ans = kmp2[i];
            cout << T.substr(0, ans) << T.substr(2*N-(N-ans)) << "\n";
            cout << ans << "\n";
            return;
        }
    }
    cout << -1 << "\n";
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
