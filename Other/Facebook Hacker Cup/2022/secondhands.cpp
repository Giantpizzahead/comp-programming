/*
<Problem link>

Solution: 
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 105;

int N, K;
int cnt[MAXN];

void solve() {
    cin >> N >> K;
    rep(i, 0, MAXN) cnt[i] = 0;
    int s;
    int a = K, b = K;
    rep(i, 0, N) {
        cin >> s;
        if (cnt[s] >= 2) {
            // Won't work
            a = -1, b = -1;
        } else if (cnt[s] == 1) {
            // Put in both
            a--, b--;
        }
        cnt[s]++;
    }
    if (a < 0 || b < 0) cout << "NO\n";
    else {
        int free = a+b;
        rep(i, 0, MAXN) if (cnt[i] == 1) free--;
        cout << (free >= 0 ? "YES" : "NO") << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}