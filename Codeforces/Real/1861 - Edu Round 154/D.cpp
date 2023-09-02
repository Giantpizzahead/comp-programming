/*
Optimal always looks like all negative nums, followed by positive nums.
Answer = (# not decreasing in section 1) + (# not increasing in section 2).
Try all split locations with prefix sums.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 2e5+5;

int N;
int A[MAXN], pre[MAXN], suf[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    rep(i, 1, N) pre[i] = pre[i-1] + (A[i-1] <= A[i]);
    suf[N-1] = 0, suf[N] = 0;
    for (int i = N-2; i >= 0; i--) suf[i] = suf[i+1] + (A[i] >= A[i+1]);

    // Only +
    int bestAns = suf[0];
    // - followed by +, or only -
    rep(i, 0, N) {
        int ans = 1+pre[i] + suf[i+1];
        bestAns = min(ans, bestAns);
    }
    cout << bestAns << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T; rep(i, 0, T) solve();
    return 0;
}
