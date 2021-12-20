#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int cx[] = {-2, -2, 1, -1}, cy[] = {1, -1, -2, -2};

const int N = 15;
int K;
int G[N][N];

void solve() {
    cin >> K;
    int ans = 0;
    rep(i, 0, K) {
        int x, y; cin >> x >> y;
        x--, y--;
        ans ^= G[x][y];
    }
    cout << (ans == 0 ? "Second" : "First") << '\n';
}

int currIter = 0, seen[5];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    rep(i, 0, 2*N+1) {
        int x = min(i, N-1), y = max(0, i+1-N);
        for (; x >= 0 && y < N; x--, y++) {
            currIter++;
            rep(d, 0, 4) {
                int nx = x + cx[d], ny = y + cy[d];
                if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                seen[G[nx][ny]] = currIter;
            }
            for (int j = 0;; j++) {
                if (seen[j] != currIter) {
                    G[x][y] = j;
                    break;
                }
            }
        }
    }
    // rep(i, 0, N) {
    //     rep(j, 0, N) {
    //         cout << G[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}