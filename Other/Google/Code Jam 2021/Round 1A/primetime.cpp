#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXM = 100;

int M;
ll total;
ll P[MAXM], N[MAXM];

bool check(ll score) {
    ll currTot = total;
    ll currS = score;
    rep(i, 0, M) {
        ll currN = N[i];
        while (currS % P[i] == 0 && currN > 0) {
            currS /= P[i];
            currTot -= P[i];
            currN--;
        }
        if (currS % P[i] == 0) return false;
    }
    if (currS != 1) return false;
    if (currTot != score) return false;
    return true;
}

void solve() {
    cin >> M;
    total = 0;
    rep(i, 0, M) {
        cin >> P[i] >> N[i];
        total += P[i] * N[i];
    }
    ll minCheck = max(2ll, total - 5000);
    ll ans = 0;
    for (ll s = minCheck; s < total; s++) {
        if (check(s)) ans = max(s, ans);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 1, T+1) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}