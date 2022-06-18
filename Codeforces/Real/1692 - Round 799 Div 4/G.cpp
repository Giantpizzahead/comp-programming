#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;

int N, K;
int A[MAXN];
bool S[MAXN];

void solve() {
    cin >> N >> K;
    rep(i, 0, N) cin >> A[i];
    // Locations that cannot be part of the subarray
    rep(i, 0, N-1) {
        S[i] = (A[i] >= 2 * A[i+1]);
    }
    int ans = 0;
    int lastS = -1;
    rep(i, 0, N) {
        if (i - lastS >= K+1) ans++;
        if (S[i]) lastS = i;
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