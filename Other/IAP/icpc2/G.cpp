/**
 * Problem link:
 * https://codeforces.com/group/hosRkEuluH/contest/423073/problem/G
 * 
 * Solution:
 * Binary search on the location of 1. Once this is fixed, naively evaluate the
 * depth of both sides. Try putting less elements on the side with greater depth.
 * Keep doing this until the optimal depth is found.
 * Runtime: O(Nlog2(N))
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

vector<int> curr, valToI, depth;

pair<int, int> trySplit(int N, int K, vector<int>& A) {
    rep(i, 0, N) curr[i] = A[K+i];
    rep(i, 0, N) valToI[curr[i]] = i;

    set<int> locs;
    rep(v, 0, N) {
        // Get current range
        int i = valToI[v];
        int maxDepth = 1;
        auto leftLoc = locs.lower_bound(i);
        if (leftLoc != locs.end()) maxDepth = max(depth[*leftLoc]+1, maxDepth);
        if (leftLoc != locs.begin()) {
            auto rightLoc = prev(leftLoc);
            maxDepth = max(depth[*rightLoc]+1, maxDepth);
        }
        depth[i] = maxDepth;
        locs.insert(i);
    }
    
    pair<int, int> ans = {1, 1};
    rep(i, 0, valToI[0]) ans.first = max(depth[i], ans.first);
    rep(i, valToI[0]+1, N) ans.second = max(depth[i], ans.second);
    dumpVars(N, K, curr, depth, ans);
    return ans;
}

void solve() {
    int N; cin >> N;
    vector<int> A(N);
    rep(i, 0, N) {
        cin >> A[i];
        A[i]--;
    }
    // Special case
    if (N == 1) {
        cout << "1 0\n";
        return;
    }
    // Init vars
    curr = vector<int>(N);
    valToI = vector<int>(N);
    depth = vector<int>(N);

    // Shift the array left based on 1 location so the 1 is at the start
    int oneLoc = -1;
    rep(i, 0, N) if (A[i] == 0) oneLoc = i;
    vector<int> newA(2*N);
    rep(i, 0, N) newA[i] = A[(oneLoc+i)%N];
    A = newA;
    // Duplicate array for easier cyclic shifting
    rep(i, 0, N) A[N+i] = A[i];

    // Binary search on split point (starting index of range to consider)
    // rep(i, 1, N+1) trySplit(N, i, A);
    int low = 1, high = N;
    while (low+1 < high) {
        int mid = (low + high) / 2;
        pair<int, int> split = trySplit(N, mid, A);
        if (split.first < split.second) high = mid;
        else if (split.first > split.second) low = mid;
        else {
            low = mid;
            high = mid;
            break;
        }
    }
    pair<int, int> lowSplit = trySplit(N, low, A);
    pair<int, int> highSplit = trySplit(N, high, A);
    int lowDepth = max(lowSplit.first, lowSplit.second);
    int highDepth = max(highSplit.first, highSplit.second);
    int ans;
    if (lowDepth <= highDepth) ans = low;
    else ans = high;
    cout << min(lowDepth, highDepth) << " " << (ans+oneLoc) % N << "\n";
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
