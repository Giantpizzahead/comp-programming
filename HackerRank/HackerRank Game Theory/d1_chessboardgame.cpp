#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

bool W[15][15];
int cx[] = {-2, -2, 1, -1}, cy[] = {1, -1, -2, -2};

int X, Y;

void solve() {
    cin >> X >> Y;
    X--, Y--;
    cout << (W[X][Y] ? "First" : "Second") << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    rep(i, 0, 29) {
        int x = min(i, 14), y = max(0, i-14);
        for (; x >= 0 && y < 15; x--, y++) {
            W[x][y] = false;
            rep(d, 0, 4) {
                int nx = x + cx[d], ny = y + cy[d];
                if (nx < 0 || ny < 0 || nx >= 15 || ny >= 15) continue;
                W[x][y] |= !W[nx][ny];
            }
        }
    }
    // rep(x, 0, 14) {
    //     rep(y, 0, 14) cout << W[x][y];
    //     cout << endl;
    // }
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}