/*
B^k % (B-1) = 1 for all k.
So, the number is divisible by (B-1) iff the sum of digits is divisible by (B-1).
It's guaranteed that a_i >= 1 for all i, so the optimal result is to remove the 1 digit that gets the required sum,
then arrange the smallest numbers first, largest last.
Answer queries using prefix sums and binary search.
Runtime: O(B + Q * log(B))
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXB = 1e6+5;
const int MAXQ = 1e5+5;

int B, Q;
ll A[MAXB], K[MAXQ];

void solve() {
    cin >> B >> Q;
    rep(i, 0, B) cin >> A[i];
    rep(i, 0, Q) cin >> K[i];
    ll currSum = 0;
    rep(i, 0, B) currSum = (currSum + i * A[i]) % (B-1);
    if (currSum != 0) A[currSum]--;
    rep(i, 1, B) A[i] += A[i-1];
    rep(i, 0, Q) {
        int v = upper_bound(A, A+B, K[i]) - A;
        cout << (v == B ? -1 : v) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}