/*
4 1 6 3 10 7

Binary search on answer?

There is a DP for this, sort of, once we binary search:
dp[i] = Min sum of elements with all segment sums <= K, blocking i.
dp[i] = for j in 0...i-1: min(dp[j] + A[i] if sum(A[j+1...i-1]) <= K).

That can be done with a sliding window approach.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

int N;
vector<ll> A;

bool check(ll K) {
    // cerr << "check(" << K << "): ";
    vector<ll> dp(N);
    dp[0] = 0;
    multiset<ll> currTrans;
    currTrans.insert(dp[0]);
    int windowI = 0;  // Leftmost index that can be transitioned from (one before segment sum)
    ll windowSum = 0;
    rep(i, 1, N) {
        dp[i] = *currTrans.begin() + A[i];
        currTrans.insert(dp[i]);
        // cerr << dp[i] << " ";

        windowSum += A[i];
        while (windowSum > K) {
            currTrans.erase(currTrans.find(dp[windowI]));
            windowSum -= A[windowI+1];
            windowI++;
        }
    }
    // cerr << endl;

    return dp[N-1] <= K;
}

void solve() {
    cin >> N;
    A.resize(N+2);
    rep(i, 1, N+1) cin >> A[i];
    // Makes the code easier
    A[0] = 0, A[N+1] = 0;
    N += 2;

    ll low = 0, high = 1e18;
    while (low < high) {
        ll mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    cout << low << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    // int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
