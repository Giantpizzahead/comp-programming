/*
IOI 2005 Day 1 Problem 2
https://contest.yandex.com/ioi/contest/566/problems/B/

2, 5, 9
A_0+A_1=2T
A_1=2T-A_0
X, 4-X, 6+X, 12-X

To check that all are nondecreasing:
A-X <= B+X
A-B <= 2X
(A-B)/2 <= X
Guaranteed B>A, so:
X >= (A-B)/2

C+X <= D-X
2X <= D-C
X <= (D-C)/2
Guaranteed D>C

Therefore, all X satisfying
(A-B)/2 <= X <= (D-C)/2 works,
where (A, B) start at odd indices,
and (C, D) start at even indices.

Only need to track smallest D-C and largest A-B!
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int INF = 2e9+7;

void solve() {
    int N; cin >> N;
    int minDC = INF, maxAB = -INF;
    int prevVal = 0, currVal = 0;
    rep(i, 0, N) {
        int x; cin >> x;
        currVal = 2*x - prevVal;
        if (i % 2 == 0) {
            // CD
            minDC = min(currVal - prevVal, minDC);
        } else {
            // AB
            maxAB = max(prevVal - currVal, maxAB);
        }
        prevVal = currVal;
    }
    minDC /= 2, maxAB /= 2;
    // cout << minDC << " " << maxAB << '\n';
    int ans = max(minDC - maxAB + 1, 0);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}