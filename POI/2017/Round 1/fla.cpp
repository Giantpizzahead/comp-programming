/*
Check if it's possible to survive by simulating with ranges of possible player locations.
If it is, only the ending height matters when calculating the min # of taps.
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 5e5+5;

int N, X;
int x[MAXN], a[MAXN], b[MAXN];

void solve() {
    cin >> N >> X;
    rep(i, 0, N) {
        cin >> x[i] >> a[i] >> b[i];
    }
    int L = 0, R = 0, lastX = 0;
    rep(i, 0, N) {
        int deltaX = x[i] - lastX;
        int newL = max(a[i]+1, L - deltaX);
        if ((newL % 2 == 0) != (x[i] % 2 == 0)) {
            // Wrong parity for position
            newL++;
        }
        int newR = min(b[i]-1, R + deltaX);
        if ((newR % 2 == 0) != (x[i] % 2 == 0)) {
            // Wrong parity for position
            newR--;
        }
        if (newL > newR) {
            cout << "NIE\n";
            return;
        }
        // Update locations
        L = newL;
        R = newR;
        lastX = x[i];
    }
    // Minimum possible ending location
    cout << (L + x[N-1]) / 2 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}