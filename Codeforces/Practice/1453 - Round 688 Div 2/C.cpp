#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2000;

int N;
int G[MAXN][MAXN], A[10], temp[MAXN][MAXN];
bool hasD[MAXN][10];
int minD[MAXN][10], maxD[MAXN][10];

void solveHor() {
    rep(i, 0, N) {
        rep(d, 0, 10) {
            hasD[i][d] = false;
            minD[i][d] = N;
            maxD[i][d] = -1;
        }
        rep(j, 0, N) {
            hasD[i][G[i][j]] = true;
            minD[i][G[i][j]] = min(j, minD[i][G[i][j]]);
            maxD[i][G[i][j]] = max(j, maxD[i][G[i][j]]);
        }
    }
    rep(i, 0, N) {
        rep(j, 0, N) {
            rep(d, 0, 10) {
                if (!hasD[i][d]) continue;
                if (hasD[j][d]) {
                    int base = max(N-1 - minD[i][d], maxD[i][d]);
                    A[d] = max(base * abs(j-i), A[d]);
                } else {
                    int base = maxD[i][d] - minD[i][d];
                    A[d] = max(base * abs(j-i), A[d]);
                }
            }
        }
    }
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        string S; cin >> S;
        rep(j, 0, N) {
            G[i][j] = S[j] - '0';
        }
    }
    // Horizontal
    solveHor();
    // Vertical
    rep(i, 0, N) rep(j, 0, N) temp[i][j] = G[j][N-1-i];
    rep(i, 0, N) rep(j, 0, N) G[i][j] = temp[i][j];
    solveHor();
    rep(d, 0, 10) {
        cout << A[d] << " \n"[d == 9];
        A[d] = 0;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}