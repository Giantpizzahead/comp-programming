#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;

int N, Q;
ll A;
ll V[MAXN], ansT[MAXN], preT[MAXN];

void solve() {
    cin >> N;
    A = 0;
    rep(i, 0, N) {
        cin >> V[i];
        A += V[i];
    }
    // Open pipes from left to right
    ll preSum = 0;
    rep(i, 0, N) {
        preSum += V[i];
        preT[i] = (preSum+i) / (i+1);
        if (i != 0) preT[i] = max(preT[i-1], preT[i]);
        ansT[i] = -(max((A+i) / (i+1), preT[i]));
    }
    cin >> Q;
    rep(i, 0, Q) {
        ll t; cin >> t;
        auto ans = lower_bound(ansT, ansT+N, -t);
        if (ans == ansT+N) cout << -1 << '\n';
        else cout << ans-ansT+1 << '\n';
    }
    // rep(i, 0, N) cout << ansT[i] << " \n"[i==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}