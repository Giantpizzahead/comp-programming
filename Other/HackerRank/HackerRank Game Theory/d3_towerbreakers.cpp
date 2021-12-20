#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXH = 1e5+5;

int N;
int grundy[MAXH];

void solve() {
    cin >> N;
    int xorSum = 0;
    rep(i, 0, N) {
        int h; cin >> h;
        xorSum ^= grundy[h];
    }
    cout << (xorSum == 0 ? 2 : 1) << '\n';
}

int seen[MAXH];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // Find grundy numbers
    grundy[1] = 0;
    rep(h, 2, MAXH) {
        seen[0] = h;
        for (int i = 2; i*i <= h; i++) {
            if (h % i == 0) {
                // Split into i towers of height h/i
                if (i % 2 == 0) {
                    // Same as removing tower
                    seen[0] = h;
                } else {
                    // Same as keeping one tower
                    seen[grundy[h/i]] = h;
                }
                // Split into h/i towers of height i
                if (h/i % 2 == 0) {
                    // Same as removing tower
                    seen[0] = h;
                } else {
                    // Same as keeping one tower
                    seen[grundy[i]] = h;
                }
            }
        }
        // Find mex
        for (int i = 0;; i++) {
            if (seen[i] != h) {
                grundy[h] = i;
                break;
            }
        }
    }
    // rep(h, 1, 51) cout << h << ": " << grundy[h] << endl;
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}