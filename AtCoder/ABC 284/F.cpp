/**
 * Problem link:
 * https://atcoder.jp/contests/abc284/tasks/abc284_f
 * 
 * Solution:
 * Reverse the given string T. Call this reversed string R.
 * Then, the reversed string will have the target string S somewhere inside it.
 * 
 * Ex:
 * S = banana, i = 4, N = 6
 * T = banaananabna
 * R = anbananaanab
 * 
 * Calculate for each ending index of R, the longest matching prefix of T.
 * a n b a n a n a a n a b
 * 0 0 1 2 3 4 0 0 0 0 0 1 (longest matching prefix going rightward, ending at i)
 * 1 0 0 1 2 1 2 1 1 2 1 0 (longest matching suffix going leftward, ending at i)
 *            | *cutoff 4+2=6>=N
 * At some "cutoff" in R, the longest matching prefix + suffix will be *at least N*.
 * Take the length of the longest matching prefix, and use that as i.
 * 
 * abababab
 * 
 * b a b a b a b a
 * 0 1 2 3 4 5 6 7
 * 7 6 5 4 3 2 1 0
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

/*
lcp[i] = Last matched prefix char ending at i that's not the whole string
*/
vector<int> getLCPArray(string S) {
    int N = sz(S);
    vector<int> lcp(N);
    lcp[0] = -1;
    rep(i, 1, N) {
        lcp[i] = lcp[i-1];
        while (lcp[i] != -1 && S[i] != S[lcp[i]+1]) lcp[i] = lcp[lcp[i]];
        if (S[i] == S[lcp[i]+1]) lcp[i]++;
    }
    return lcp;
}

/*
If A[i] = j, that means S[i-j:i+1] = T[0:j+1] (exclusive).
That is, prefix of T matches up till character i in string S.
-1 if no match.
*/
vector<int> getMatchingPrefix(string S, string T) {
    int N = sz(S), M = sz(T);
    vector<int> lcp = getLCPArray(T);
    vector<int> pre(N);
    rep(i, 0, N) {
        pre[i] = (i == 0 ? -1 : pre[i-1]);
        if (pre[i] == M-1) pre[i] = lcp[pre[i]];
        while (pre[i] != -1 && S[i] != T[pre[i]+1]) pre[i] = lcp[pre[i]];
        if (S[i] == T[pre[i]+1]) pre[i]++;
    }
    return pre;
}

void solve() {
    int N; cin >> N;
    string T; cin >> T;
    string revT = T;
    reverse(all(revT));
    vector<int> pre = getMatchingPrefix(revT, T.substr(0, N));
    vector<int> suf = getMatchingPrefix(T, revT.substr(0, N));
    reverse(all(pre));
    dumpVars(pre);
    dumpVars(suf);
    // Test cutoff location
    int currPre = pre[N]+1;
    int currSuf = suf[N-1]+1;
    dumpVars(currPre, currSuf);
    if (currPre + currSuf < N) {
        cout << "-1\n";
        return;
    }
    int cutoff = currPre % N;
    cout << T.substr(0, cutoff) << T.substr(sz(T)-(N-cutoff)) << "\n";
    cout << cutoff << "\n";
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
