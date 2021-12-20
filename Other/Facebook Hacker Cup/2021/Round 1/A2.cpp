#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const ll MOD = 1e9+7;

void solve() {
    int N;
    string S;
    cin >> N >> S;
    ll ans = 0;
    int lastLoc = -1;
    rep(i, 0, N) {
        if (S[i] == 'O' || S[i] == 'X') {
            if (lastLoc != -1 && S[lastLoc] != S[i]) {
                ll ways = (ll) (lastLoc+1) * (N-i);
                ans = (ans + ways) % MOD;
            }
            lastLoc = i;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}