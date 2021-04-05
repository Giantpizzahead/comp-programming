#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 30;

int N;
// A[i][j] = Whether the cell (i, j) is NOT prime
bool A[MAXN][MAXN];
int G[MAXN][MAXN][MAXN][MAXN];

int currIter = 0, seen[129];

inline void genGrundy(int x1, int y1, int x2, int y2) {
    // Check if has at least one non-prime
    bool nonPrime = false;
    rep(x, x1, x2+1) {
        rep(y, y1, y2+1) {
            if (A[x][y]) {
                nonPrime = true;
                break;
            }
        }
    }
    if (!nonPrime) {
        // Cannot make any moves
        G[x1][y1][x2][y2] = 0;
        return;
    }
    // Check transitions
    rep(k, x1, x2) {
        seen[G[x1][y1][k][y2] ^ G[k+1][y1][x2][y2]] = currIter;
    }
    rep(k, y1, y2) {
        seen[G[x1][y1][x2][k] ^ G[x1][k+1][x2][y2]] = currIter;
    }
    // Fill Grundy number
    for (int i = 0;; i++) {
        if (seen[i] != currIter) {
            G[x1][y1][x2][y2] = i;
            break;
        }
    }
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        rep(j, 0, N) {
            int x; cin >> x;
            A[i][j] = !(x == 2 || x == 3 || x == 5 || x == 7);
        }
    }
    // Build Grundy numbers from bottom up
    rep(dx, 0, N) {
        rep(dy, 0, N) {
            for (int x1 = 0, x2 = dx; x2 < N; x1++, x2++) {
                for (int y1 = 0, y2 = dy; y2 < N; y1++, y2++) {
                    currIter++;
                    genGrundy(x1, y1, x2, y2);
                }
            }
        }
    }
    cout << (G[0][0][N-1][N-1] == 0 ? "Second" : "First") << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}