/*
Solution: Math.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 1e6+5;
const int C = 1572869;

int N, K, D;
int H[MAXN];

void solve() {
    cin >> N >> K >> D;
    rep(i, 0, N) cin >> H[i];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // For HackerCup
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
