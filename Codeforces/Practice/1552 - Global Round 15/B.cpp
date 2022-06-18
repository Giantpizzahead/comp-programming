#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 5e4+5;

int N;
int R[MAXN][5];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        rep(j, 0, 5) {
            cin >> R[i][j];
        }
    }
    int best = 0;
    rep(i, 1, N) {
        int win = 0;
        rep(j, 0, 5) {
            if (R[i][j] < R[best][j]) win++;
        }
        if (win >= 3) best = i;
    }
    // Check if this one wins against all
    rep(i, 0, N) {
        if (i == best) continue;
        int win = 0;
        rep(j, 0, 5) {
            if (R[i][j] < R[best][j]) win++;
        }
        if (win >= 3) {
            // No
            cout << -1 << '\n';
            return;
        }
    }
    // Yes
    cout << best+1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}