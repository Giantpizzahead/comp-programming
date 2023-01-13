// 8 5 2 7
// -3 -3 5
// 0 0 0 = 11 steps

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;

int N;
int A[MAXN], diff[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N-1) diff[i] = A[i+1] - A[i];
    ll finalNum = A[0];
    ll ans = 0;
    rep(i, 0, N-1) {
        if (diff[i] < 0) {
            // Decrease on left side
            finalNum -= -diff[i];
            ans += -diff[i];
        } else if (diff[i] > 0) {
            // Decrease on right side
            ans += diff[i];
        }
    }
    ans += abs(finalNum);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}