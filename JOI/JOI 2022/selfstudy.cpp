/*
JOI 2022 Problem 2

Solution:
First, set A_i = max(A_i, B_i) to avoid edge cases.
Then, binary search on the answer (makes the problem easier).

Start with Bitaro attending every class.
Then, for each course in which he overprepares, calculate the # of classes that can be skipped.
See if those missed courses (in total) can make up the ones he underprepares for.
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

bool check(int N, ll M, vi& A, vi& B, ll K) {
    vector<ll> prepLeft(N, K);
    // Initially, go to all the classes
    rep(i, 0, N) prepLeft[i] -= M * A[i];
    // Count number of free classes (to be reassigned)
    // Also count number of needed self study periods
    ll numFree = 0;
    ll numSelf = 0;
    rep(i, 0, N) {
        if (prepLeft[i] <= -A[i]) {
            // Overprepared
            numFree += min(-prepLeft[i] / A[i], M);
        } else if (prepLeft[i] > 0) {
            // Underprepared
            numSelf += (prepLeft[i]+B[i]-1) / B[i];
            if (numSelf >= 1e18) return false;
        }
    }
    // Possible if enough free periods exist
    return numFree >= numSelf;
}

void solve() {
    int N; cin >> N;
    ll M; cin >> M;
    vi A(N), B(N);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) {
        cin >> B[i];
        A[i] = max(A[i], B[i]);
    }

    // Binary search on the answer
    ll ansLow = 0, ansHigh = 2e18;
    while (ansLow < ansHigh) {
        ll mid = (ansLow+ansHigh+1) / 2;
        if (check(N, M, A, B, mid)) ansLow = mid;
        else ansHigh = mid - 1;
    }
    ll ans = ansLow;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}