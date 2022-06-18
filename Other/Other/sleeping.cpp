#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 1e5+5;

int N, M;
ll A[MAXN], Q[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    cin >> M;
    rep(i, 0, M) cin >> Q[i];

    rep(i, 0, M) {
        ll q = Q[i];
        ll ans = 0;
        ll curr = 0;
        rep(j, 0, N) {
            // Merge numbers
            if (curr != 0) ans++;
            curr += A[j];
            // Create correct numbers
            ll toCreate = curr / q;
            curr -= toCreate * q;
            ans += toCreate;
            if (curr == 0) ans--;
        }
        if (curr == 0) cout << ans << '\n';
        else cout << -1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}