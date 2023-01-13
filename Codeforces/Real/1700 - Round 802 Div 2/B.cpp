#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

int N;
string S;
string ans;

void solve() {
    cin >> N >> S;
    ans = "";
    if (S[0] == '9') {
        // Target: 11111
        int c = 0;
        for (int i = N-1; i >= 0; i--) {
            int v = S[i] - '0';
            int t = (21 - c - v) % 10;
            c = (v + t) / 10;
            ans += to_string(t);
        }
        reverse(all(ans));
    } else {
        // Target: 9999
        rep(i, 0, N) {
            int v = S[i] - '0';
            int t = 9 - v;
            ans += to_string(t);
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