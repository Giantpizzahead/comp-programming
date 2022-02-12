/*
Solution:


(Begin notes)
1 2 4 8 16 21 42 51 102
2:	1
4:	3 2 (G)
8:	7 6 4 (U)
16:	15 14 12 8 (G)
21:	20 19 17 13 5 (U)
42:	41 40 38 34 26 21 (G)

All differences will be unique, since either it’s greater than all previous differences, or the addition is unique
Simulate the sequence up to a certain point, then use math to determine the rest
After elements are > 10^9:
    *2 means all differences will be > 10^9, so can be ignored
    + unique creates a new unique difference
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N, X;
vector<ll> A;
vector<int> diffs;
unordered_map<int, pair<int, int>> usedDiffs;

void solve() {
    A.push_back(1);
    A.push_back(2);
    usedDiffs[1] = {1, 0};
    while (A.back() <= 1e9) {
        // Even n
        int y = A.back() * 2;
        rep(i, 0, sz(A)) usedDiffs[y-A[i]] = {sz(A), i};
        A.push_back(y);
        // Odd n
        y = 1;
        while (usedDiffs.count(y)) y++;
        y += A.back();
        rep(i, 0, sz(A)) usedDiffs[y-A[i]] = {sz(A), i};
        A.push_back(y);
    }
    for (auto& p : usedDiffs) diffs.push_back(p.first);
    sort(all(diffs));

    // for (int x : A) cout << x << " ";
    // cout << endl;

    cin >> N;
    rep(i, 0, N) {
        cin >> X;
        // Check if difference is in first few elements
        auto ptr = usedDiffs.find(X);
        if (ptr != usedDiffs.end()) cout << ptr->second.first+1 << ' ' << ptr->second.second+1 << '\n';
        else {
            // Manually calculate location of difference
            int numBefore = lower_bound(all(diffs), X) - diffs.begin();
            int a = sz(A) + (X - numBefore) * 2;
            cout << a << ' ' << a-1 << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}