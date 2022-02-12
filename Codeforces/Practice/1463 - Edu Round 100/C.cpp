/*
Solution: Simulate the robot's actions.
Runtime: O(N)
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;

int N, ans;
ll T[MAXN], X[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> T[i] >> X[i];
    T[N] = 1e18;
    X[N++] = 0;
    ll prevX = 0, prevT = 0;
    ll currX = 0, currT = 0;
    ll targetX = 0;
    ans = 0;
    rep(i, 0, N) {
        prevT = currT;
        prevX = currX;
        currT = T[i];
        // Move the robot and determine if previous was successful
        ll dt = currT - prevT;
        if (prevX <= targetX) currX = min(prevX + dt, targetX);
        else currX = max(prevX - dt, targetX);
        if (i != 0 && X[i-1] >= min(prevX, currX) && X[i-1] <= max(prevX, currX)) ans++;
        // Next instruction
        if (currX == targetX) {
            // Follows this instruction
            targetX = X[i];
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}