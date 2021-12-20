#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int T, N, B;
ll P;
bool placed;
vector<int> numLeft;

void placeBlock(int x) {
    assert(numLeft[x] > 0);
    placed = true;
    numLeft[x]--;
    cout << x+1 << endl;
}

void solve() {
    int D;
    numLeft.resize(N);
    fill(all(numLeft), B);
    rep(i, 0, N*B) {
        cin >> D;
        placed = false;
        rep(j, 0, N) {
            if (numLeft[j] == 0) continue;
            else if (numLeft[j] == 1) {
                if (D >= 9) {
                    placeBlock(j);
                    break;
                } else continue;
            } else if (numLeft[j] == 2) {
                if (D >= 7) {
                    placeBlock(j);
                    break;
                } else continue;
            } else {
                // Any number goes
                placeBlock(j);
                break;
            }
        }
        if (!placed) {
            // Place in first open tower
            rep(j, 0, N) if (numLeft[j] != 0) {
                placeBlock(j);
                break;
            }
        }
        assert(placed);
    }
}

int main() {
    // ios::sync_with_stdio(0);
    cin >> T >> N >> B >> P;
    rep(i, 0, T) {
        solve();
    }
    return 0;
}